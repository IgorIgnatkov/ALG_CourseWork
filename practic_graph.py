import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def load_data(file_path):
    return pd.read_csv(file_path, sep=",", header=None,
                       names=['search_type', 'case', 'array_size', 'execution_time'])

def plot_searching_times(data):
    search_algorithms = data['search_type'].unique()

    for algorithm in search_algorithms:
        algorithm_data = data[data['search_type'] == algorithm]
        plot_algorithm_data(algorithm_data, algorithm)

def plot_algorithm_data(algorithm_data, algorithm):
    best_case_data = algorithm_data[algorithm_data['case'] == 'Лучший']
    average_case_data = algorithm_data[algorithm_data['case'] == 'Средний']
    worst_case_data = algorithm_data[algorithm_data['case'] == 'Худший']

    plt.figure(figsize=(10, 6))

    # Регрессия для каждого типа данных
    for data_subset, label in zip(
            [best_case_data, average_case_data, worst_case_data],
            ['Лучший', 'Средний', 'Худший']
    ):
        if not data_subset.empty:
            x = data_subset['array_size']
            y = data_subset['execution_time']

            # Полиномиальная регрессия (степень 2)
            if algorithm == 'Линейный поиск' and label in ['Средний', 'Худший']:
                degree = 1  # Линейная регрессия для линейного поиска
            elif algorithm == 'Интерполяционный поиск' and label == 'Средний':
                degree = 1  # Линейная регрессия для среднего случая интерполяционного поиска
            else:
                degree = 2  # Полиномиальная регрессия степени 2 для остальных случаев

            coefficients = np.polyfit(x, y, degree)
            polynomial = np.poly1d(coefficients)

            # Построение графика
            plt.plot(x, y, label=label)

            # Добавление линии регрессии
            x_fit = np.linspace(x.min(), x.max(), 100)
            y_fit = polynomial(x_fit)
            plt.plot(x_fit, y_fit, linestyle='--', label=f'{label} - регрессия')

            # Сохранение регрессионной функции
            with open(f'{algorithm}_regression.txt', 'a') as f:
                f.write(f'{label} регрессия: {polynomial}\n')

    plt.title(f'{algorithm} - график')
    plt.xlabel('N (Размер массива)')
    plt.ylabel('t (сек)')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{algorithm}.png')
    plt.show()

def main():
    data = load_data('graph.csv')
    plot_searching_times(data)

if __name__ == "__main__":
    main()
