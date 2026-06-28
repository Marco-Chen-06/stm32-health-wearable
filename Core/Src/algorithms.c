#include "algorithms.h"


long calculate_acc_mag(bmi270_data_t data) {
	return sqrt(pow((long)data.acc_x, 2) + pow((long)data.acc_y, 2) + pow((long)data.acc_z, 2));
}

long calculate_gyr_mag(bmi270_data_t data) {
	return sqrt(pow((long)data.gyr_x, 2) + pow((long)data.gyr_y, 2) + pow((long)data.gyr_z, 2));
}

// basic standard deviation algorithm using sqrtf
float calculate_stddev(const int32_t *data, uint32_t size) {
	if (size <= 1) {
		return 0.0f;
	}

	float sum = 0.0f;
	for (size_t i = 0; i < size; i++) {
		sum += (float)data[i];
	}
	float mean = sum/size;
	float var_sum = 0.00;
	for (size_t i = 0; i < size; i++) {
		float diff = (float)data[i] - mean;
		var_sum += diff * diff;
	}
	// sample stddev
	return sqrtf(var_sum/(size - 1));
}


//static long calculate_acc_mag(bmi270_data_t data) {
//	return sqrt(pow((long)data.acc_x, 2) + pow((long)data.acc_y, 2) + pow((long)data.acc_z, 2));
//}
