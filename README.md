# stm32-health-wearable

Health monitoring system for MAX30102 (pulse oximeter), BMI270 (IMU), and AD8232 (ECG) sensors using FreeRTOS.

Data is continuously sampled from all sensors and printed in CSV format over UART. 

../tools/data_plot.py handles the plotting of this CSV data.


