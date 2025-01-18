import numpy as np


def longest_increasing_subsequence(arr):
    n = len(arr)
    if n == 0:
        return 0  # Если массив пустой, длина LIS равна 0

    # Инициализация массива dp с помощью numpy
    dp = np.ones(n, dtype=int)

    # Заполнение dp
    for i in range(1, n):
        for j in range(i):
            if arr[i] > arr[j]:  # Если текущий элемент больше предыдущего
                dp[i] = max(dp[i], dp[j] + 1)

    # Возвращаем максимальное значение в dp — это длина LIS
    return np.max(dp)


# Пример использования
arr = [3, 6, 2, 7]
result = longest_increasing_subsequence(arr)
print(f"Длина самой длинной возрастающей подпоследовательности: {result}")
