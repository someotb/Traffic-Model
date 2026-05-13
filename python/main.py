import os

import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DATAS_DIR = os.path.join(SCRIPT_DIR, "..", "data")
FILE_DIR = os.path.join(DATAS_DIR, "data.csv")

with open(FILE_DIR) as f:
    modelType = f.readline().strip()

df = pd.read_csv(FILE_DIR, skiprows=1, header=None, names=["time", "size"])
size = df["size"]
time = df["time"]
time_list = np.diff(time.to_numpy())

mean_packet_size = size.mean()
mean_packet_inte = time_list.mean()
mean_bitrate = size.sum() / time.max() * 8

print(f"Симуляция трафика с распределением: {modelType}")
print(f"Длительность симуляции: {time.max() / 1000} с")
print(f"Всего отправлено: {size.count()} пакетов")
print(f"Средний размер пакета: {mean_packet_size:0.4f} байт")
print(f"Средний размер интервала между пакетами: {mean_packet_inte:0.4f} мс")
print(f"Средний битрейт: {mean_bitrate:0.2f} кбит/с")

min_t, max_t = time_list.min(), time_list.max()
bins = np.arange(min_t, max_t + 2) - 0.5

plt.figure(figsize=(12, 6), label=f"Распределение {modelType}")
plt.title("Гистрограмма задержек между пакетами")
plt.hist(time_list, bins=bins)
plt.xlabel("Время(с)")
plt.ylabel("Кол-во пакетов")

plt.figure(figsize=(12, 6), label=f"Распределение {modelType}")
plt.title("Гистрограмма размера пакетов")
plt.hist(size, bins=50)
plt.xlabel("Размер пакета(байт)")
plt.ylabel("Кол-во пакетов")

plt.show()
