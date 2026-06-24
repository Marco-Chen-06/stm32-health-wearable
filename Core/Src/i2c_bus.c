#include "i2c_bus.h"

static i2c_bus_ctx_t bmi270_ctx;
static i2c_bus_ctx_t max30102_ctx;

int i2c_bus_init(I2C_HandleTypeDef *bmi270_hi2c, I2C_HandleTypeDef *max30102_hi2c) {
	bmi270_ctx.hi2c = bmi270_hi2c;
	max30102_ctx.hi2c = max30102_hi2c;

	bmi270_ctx.sem = xSemaphoreCreateBinary();
	max30102_ctx.sem = xSemaphoreCreateBinary();

	bmi270_ctx.err = 0;
	max30102_ctx.err = 0;

	if (!bmi270_ctx.sem || !max30102_ctx.sem) {
		return -1;
	}
	return 0;
}

i2c_bus_ctx_t *i2c_get_ctx(I2C_HandleTypeDef *hi2c) {
	if (hi2c == bmi270_ctx.hi2c) {
		return &bmi270_ctx;
	}
	if (hi2c == max30102_ctx.hi2c) {
		return &max30102_ctx;
	}
	return NULL;
}

// @param devAddr: pass in the unshifted devAddr
int i2c_wait(i2c_bus_ctx_t *ctx, uint16_t devAddr) {
	if (xSemaphoreTake(ctx->sem, pdMS_TO_TICKS(I2C_INT_TIMEOUT_MS)) != pdTRUE) {
		HAL_I2C_Master_Abort_IT(ctx->hi2c, devAddr << 1);
		return -1;
	}
	if (ctx->err != 0) {
		return -1;
	}
	return 0;
}

// @param devAddr: pass in the unshifted devAddr
int i2c_bus_mem_write(I2C_HandleTypeDef *hi2c, uint8_t devAddr, uint8_t memAddr, const uint8_t *pData, uint16_t size) {
	i2c_bus_ctx_t *ctx;
	ctx = i2c_get_ctx(hi2c);
	if (!ctx) {
		printf("I2C aborted during i2c_bus_mem_write because ctx is NULL. MemAddr: %02X. DevAddr: %02X. Errcode: %ld \r\n", memAddr, devAddr, ctx->err);
		return -1;
	}
	ctx->err = 0;
	xSemaphoreTake(ctx->sem, 0);
	HAL_I2C_Mem_Write_IT(ctx->hi2c, devAddr << 1, memAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t*) pData, size);
	if (i2c_wait(ctx, devAddr) == -1) {
		printf("I2C aborted during i2c_bus_mem_write. MemAddr: %02X. DevAddr: %02X. Errcode: %ld \r\n", memAddr, devAddr, ctx->err);
		return -1;
	}
	return 0;
}

// @param devAddr: pass in the unshifted devAddr
int i2c_bus_mem_read(I2C_HandleTypeDef *hi2c, uint8_t devAddr, uint8_t memAddr, uint8_t *pData, uint16_t size) {
	i2c_bus_ctx_t *ctx;
	ctx = i2c_get_ctx(hi2c);
	if (!ctx) {
		printf("I2C aborted during i2c_bus_mem_read because ctx is NULL. MemAddr: %02X. DevAddr: %02X. Errcode: %ld \r\n", memAddr, devAddr, ctx->err);
		return -1;
	}
	ctx->err = 0;
	xSemaphoreTake(ctx->sem, 0);
	HAL_I2C_Mem_Read_IT(ctx->hi2c, devAddr << 1, memAddr, I2C_MEMADD_SIZE_8BIT, pData, size);
	if (i2c_wait(ctx, devAddr) == -1) {
		printf("I2C aborted during i2c_bus_mem_read. MemAddr: %02X. DevAddr: %02X. Errcode: %ld \r\n", memAddr, devAddr, ctx->err);
		return -1;
	}
	return 0;
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	i2c_bus_ctx_t *ctx;
	ctx = i2c_get_ctx(hi2c);
	// if there's no i2c context then something went wrong
	if (!ctx) {
		return;
	}
	BaseType_t woken = pdFALSE;
	xSemaphoreGiveFromISR(ctx->sem, &woken);
	portYIELD_FROM_ISR(woken);
}

//
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	i2c_bus_ctx_t *ctx;
	ctx = i2c_get_ctx(hi2c);
	// if there's no i2c context then something went wrong
	if (!ctx) {
		return;
	}
	BaseType_t woken = pdFALSE;
	xSemaphoreGiveFromISR(ctx->sem, &woken);
	portYIELD_FROM_ISR(woken);
}

// HAL callback for transfer errors
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
	i2c_bus_ctx_t *ctx;
	ctx = i2c_get_ctx(hi2c);
	// if there's no i2c context somehow then something went really wrong
	if (!ctx) {
		return;
	}
	ctx->err = HAL_I2C_GetError(hi2c);
	BaseType_t woken = pdFALSE;
	xSemaphoreGiveFromISR(ctx->sem, &woken);
	portYIELD_FROM_ISR(woken);
}

// HAL callback for HAL_I2C_Master_Abort_IT()
void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef *hi2c) {
}

//
//
//	uint32_t start = HAL_GetTick();
//	while (!i2c_done) {
//		if ((HAL_GetTick() - start > I2C_INT_TIMEOUT_MS) || i2c_err != 0) {
//			HAL_I2C_Master_Abort_IT(hi2c, (MAX30102_I2C_DEFAULT_ADDR << 1));
//			return -1;
//		}
//	}
//	return 0;
