def longest_increasing_subsequence(arr):
    n = len(arr)
    if n == 0:
        return 0  # Если массив пустой, длина LIS равна 0

    # Инициализация массива dp, где dp[i] — длина LIS, заканчивающейся на arr[i]
    dp = [1] * n

    # Заполнение dp
    for i in range(1, n):
        for j in range(i):
            if arr[i] > arr[j]:  # Если текущий элемент больше предыдущего
                dp[i] = max(dp[i], dp[j] + 1)
                print(dp[i],dp[j]+1)# Обновляем длину LIS для arr[i]

    # Максимальное значение в dp — это длина LIS
    print(dp)
    return max(dp)

# Пример использования
arr = [3,6,2,7]
result = longest_increasing_subsequence(arr)
print(f"Длина самой длинной возрастающей подпоследовательности: {result}")