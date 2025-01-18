import numpy as np

def longest_increasing_subsequence(arr):
    n = len(arr)
    if n == 0:
        return 0  # Если массив пустой, длина LIS равна 0

    # Создаем массив размером n x n, заполняем True, если arr[j] < arr[i]
    compare_matrix = np.less.outer(arr, arr)  # True, если arr[j] < arr[i]

    # Преобразуем булеву матрицу в числовую
    dp_matrix = compare_matrix.astype(int)  # 1, если arr[j] < arr[i], иначе 0

    # Подсчитываем длины LIS для всех элементов
    dp = np.ones(n, dtype=int) + np.max(dp_matrix * dp[:, None], axis=0)

    return int(np.max(dp))

# Пример использования
arr = [3, 6, 2, 7]
result = longest_increasing_subsequence(arr)
print(f"Длина самой длинной возрастающей подпоследовательности: {result}")
