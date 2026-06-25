# data_plot.py
# real-time serial plotter for ad8232, max30102, and bmi270 samples

# expects the following data packet format:
# "ad8232,adc_data\r\n"
# "bmi270,acc_x,acc_y,acc_z,gyr_x,gyr_y,gyr_z,acc_mag\r\n"
# "max30102,ir_data\r\n"

import serial
from collections import deque
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

import numpy as np
from scipy.signal import find_peaks

SOURCES = {
    "max30102": {"num_channels": 1, "ax": 0, "labels": ["ir_data"]},
    "ad8232": {"num_channels": 1, "ax": 1, "labels": ["ecg_adc_data"]},
    "bmi270": {"num_channels": 7, "ax": 2, "labels": ["acc_x", "acc_y", "acc_z", "gyr_x", "gyr_y", "gyr_z", "acc_mag"]}
}

PORT = "/dev/ttyACM0"
BAUDRATE = 115200
WINDOW_WIDTH = 500

ser = serial.Serial(PORT, BAUDRATE, timeout=1)
ser.reset_input_buffer()

buffers = {}
for name, cfg in SOURCES.items():
    buffers[name] = [deque([0]*WINDOW_WIDTH, maxlen=WINDOW_WIDTH) for _ in range(cfg["num_channels"])]

def update(frame):
    while ser.in_waiting:
        raw_data = ser.readline()
        try:
            parts = raw_data.decode("ascii").strip().split(",")
            source = parts[0]
            if source not in SOURCES:
                continue
            values = [int(p) for p in parts[1:]] 
            if len(values) != SOURCES[source]["num_channels"]:
                continue
        except (UnicodeDecodeError, ValueError):
            continue
        for i, v in enumerate(values):
            buffers[source][i].append(v)
    return []

fig, ax = plt.subplots(3, 1, sharex=True)

#
# need labels and legend stuff here
#

lines = {}
x = range(WINDOW_WIDTH)
for source, cfg in SOURCES.items():
    a = ax[cfg["ax"]]
    lines[source] = []
    for ch in range(cfg["num_channels"]):
        line, = a.plot(x, buffers[source][ch], label=cfg["labels"][ch])
        lines[source].append(line)
    a.legend(loc="upper right")
    a.set_title(source)


def update_plot(frame):
    update(frame)
    # loop over each channel of each source
    for source in buffers:
        for ch, dq in enumerate(buffers[source]):
            lines[source][ch].set_ydata(dq)
    for source, cfg in SOURCES.items():
        a = ax[cfg["ax"]]
        a.relim()
        a.autoscale_view(scalex=False)
    return [ln for s in lines for ln in lines[s]]
        


try:
    anim = FuncAnimation(fig, update_plot, interval = 50, cache_frame_data = False)
    plt.show()

except KeyboardInterrupt:
    print("keyboard interrupt detected")

finally:
    if ser.is_open:
        ser.close()
        print("serial port closed")

