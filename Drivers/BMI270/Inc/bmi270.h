#ifndef BMI270_H
#define BMI270_H

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "i2c_bus.h"

typedef struct {
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t gyr_x;
	int16_t gyr_y;
	int16_t gyr_z;
} bmi270_data_t;

// perform initialization sequence
int bmi270_init(I2C_HandleTypeDef *hi2c);

// initialize bmi270 for normal mode
int bmi270_init_normal(I2C_HandleTypeDef *hi2c);

// initialize bmi270 for low pwoer mode, exactly as according to the datasheet
int bmi270_init_low_power(I2C_HandleTypeDef *hi2c);

// set the advanced power save mode
int bmi270_power_save_enable(I2C_HandleTypeDef *hi2c);

// get motion data
int bmi270_get_motion_data(I2C_HandleTypeDef *hi2c, bmi270_data_t *data);

// I2C transaction functions
int bmi270_write(I2C_HandleTypeDef *hi2c, uint16_t memAddr,
		const uint8_t *pData, uint16_t size);
int bmi270_read(I2C_HandleTypeDef *hi2c, uint16_t memAddr, uint8_t *pData,
		uint16_t size);
int bmi270_write_byte(I2C_HandleTypeDef *hi2c, uint16_t memAddr, uint8_t byte);
int bmi270_read_byte(I2C_HandleTypeDef *hi2c, uint16_t memAddr, uint8_t *byte);

#endif
