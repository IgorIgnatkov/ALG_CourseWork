import numpy as np
import matplotlib.pyplot as plt
import os

def plot_asymptotic_complexity():
    n = np.linspace(2, 10000, 20000)  # Количество элементов массива, начиная с 2

    # Данные для каждого алгоритма
    complexities = {
        'Linear Search': {
            'Лучший': np.full_like(n, 2),
            'Средний': 2 * (n / 2),
            'Худший': 2 * n,
        },
        'Binary Search': {
            'Лучший': np.full_like(n, 3),
            'Средний': np.log(n),
            'Худший': 3 + 4 * np.log(n),
        },
        'Exponential Search': {
            'Лучший': np.full_like(n, 2),
            'Худший': np.log(n),
        },
        'Interpolation Search': {
            'Лучший': np.full_like(n, 1.5),
            'Средний': np.log(np.log(n)),
            'Худший': 3 * n,
        },
    }

    # Построение графиков для каждого алгоритма
    for algorithm, cases in complexities.items():
        plt.figure(figsize=(10, 6))
        for case_name, values in cases.items():
            plt.plot(n, values, label=f'{case_name}')

        plt.title(f'Асимптоты сложности {algorithm}')
        plt.xlabel('N')
        plt.ylabel('T(N)')
        plt.legend()
        plt.grid(True)
        plt.yscale('log')  # Логарифмическая шкала для лучшего отображения
        plt.xlim([2, 10000])
        plt.ylim([1, 10000])

        # Сохранение графика
        filename = os.path.join(os.getcwd(), f'{algorithm}.png')
        plt.savefig(filename)
        plt.close()  # Закрытие текущей фигуры

# Вызов функции
plot_asymptotic_complexity()
