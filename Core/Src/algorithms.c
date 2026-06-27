#include "algorithms.h"


long calculate_acc_mag(bmi270_data_t data) {
	return sqrt(pow((long)data.acc_x, 2) + pow((long)data.acc_y, 2) + pow((long)data.acc_z, 2));
}

//static long calculate_acc_mag(bmi270_data_t data) {
//	return sqrt(pow((long)data.acc_x, 2) + pow((long)data.acc_y, 2) + pow((long)data.acc_z, 2));
//}
