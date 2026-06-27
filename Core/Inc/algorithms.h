/*
 * algorithms.h
 * header file for algorithms to be used in main.c
 */

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "main.h"
#include "bmi270.h"
#include "math.h"

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

#endif
