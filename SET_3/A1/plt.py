import math
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt

exact_area = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1

base_dir = Path(__file__).resolve().parent
data_path = base_dir / "data.csv"

# Skip the first header row in CSV
data = np.loadtxt(data_path, comments="#", skiprows=1)

N_values = data[:, 0].astype(int)
areas_1 = data[:, 1]
rel_err_1 = data[:, 2] * 100
areas_2 = data[:, 3]
rel_err_2 = data[:, 4] * 100

plt.figure(figsize=(10, 6))
plt.plot(N_values, areas_1, label="Способ 1 (широкий прямоугольник)", color="blue")
plt.plot(N_values, areas_2, label="Способ 2 (узкий прямоугольник)", color="red")
plt.axhline(y=exact_area, color="black", linestyle="--",
            label=f"Точная площадь = {exact_area:.6f}")
plt.xlabel("Количество точек N")
plt.ylabel("Площадь")
plt.title("Зависимость приближённой площади от количества точек")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(N_values, rel_err_1, label="Способ 1 (широкий)", color="blue")
plt.plot(N_values, rel_err_2, label="Способ 2 (узкий)", color="red")
plt.xlabel("Количество точек N")
plt.ylabel("Отклонение (%)")
plt.title("Зависимость относительного отклонения от количества точек")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
