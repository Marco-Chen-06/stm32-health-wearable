#include "i2c_bus.h"

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
}
