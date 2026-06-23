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

int i2c_wait(i2c_bus_ctx_t *ctx, uint16_t devAddr);

#endif
