/*
 * algorithms.h
 * header file for algorithms to be used in main.c
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "main.h"
#include "bmi270.h"
#include "math.h"

#define BMI270_COUNTS_PER_G 4096 // for +-8g, this is 32768/8, or, the acc_mag at rest (1g)
#define WEIGHTLESS_THRESHOLD ((BMI270_COUNTS_PER_G * 8) / 10) // 0.8g = 3276
#define IMPACT_THRESHOLD ((BMI270_COUNTS_PER_G * 14) / 10)
#define STABILITY_THRESHOLD_ACC (BMI270_COUNTS_PER_G / 10)
#define STABILITY_THRESHOLD_GYR 10 // degrees per second
// number of samples to collect for stability checking
#define NUM_STABILITY_SAMPLES 200
// number of stability samples to check
#define NUM_SAMPLES_TO_CHECK 50


typedef enum {
	IDLE,
	FREEFALL,
	STABCHECK1,
	STABCHECK2,
	FALL_OCCURED,
} fall_state_t;

enum {
	EXIT_NORMAL = 0,
	EXIT_UNKNOWN,
	NORMAL_OPERATION = 0x7F
};

long calculate_acc_mag(bmi270_data_t data);

long calculate_gyr_mag(bmi270_data_t data);

float calculate_stddev(const int32_t *data, uint32_t size);

#endif
