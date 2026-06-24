#ifndef I2C_BUS_H
#define I2C_BUS_H

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define I2C_INT_TIMEOUT_MS 100

typedef struct {
	I2C_HandleTypeDef *hi2c;
	SemaphoreHandle_t sem;
	volatile uint32_t err;
} i2c_bus_ctx_t;

int i2c_bus_init(I2C_HandleTypeDef *bmi270_hi2c, I2C_HandleTypeDef *max30102_hi2c);

i2c_bus_ctx_t *i2c_get_ctx(I2C_HandleTypeDef *hi2c);

int i2c_wait(i2c_bus_ctx_t *ctx, uint16_t devAddr);

int i2c_bus_mem_write(I2C_HandleTypeDef *hi2c, uint8_t devAddr, uint8_t memAddr, const uint8_t *pData, uint16_t size);

int i2c_bus_mem_read(I2C_HandleTypeDef *hi2c, uint8_t devAddr, uint8_t memAddr, uint8_t *pData, uint16_t size);


#endif
