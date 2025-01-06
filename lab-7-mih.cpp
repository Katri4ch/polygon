class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // Переменная для подсчета общего количества элементов во всех группах
        int totalElements = 0;

        // Подсчет общего количества элементов
        for (auto& group : nums)
            totalElements += group.size(); // O(K), где K - общее количество элементов во всех группах

        // Вектор для хранения всех элементов с информацией о принадлежности группе
        vector<pair<int, int>> sortedElements(totalElements);

        int numGroups = nums.size(); // Количество групп

        // Заполняем вектор sortedElements
        for (int i = 0, index = 0; i < numGroups; ++i) {
            for (int value : nums[i]) {
                sortedElements[index++] = {value, i}; // O(K), где K - общее количество элементов
            }
        }

        // Сортировка элементов
        sort(sortedElements.begin(), sortedElements.end()); // O(K log K)

        int startWindow = 0; // Начало скользящего окна

        // Хэш-таблица для подсчета количества элементов каждой группы в текущем окне
        unordered_map<int, int> groupCount; // O(G), где G - количество групп

        // Вектор для хранения текущего наименьшего диапазона
        vector<int> range = {-1000000, 1000000}; // Постоянное пространство

        // Обход всех элементов через конец окна
        for (int endWindow = 0; endWindow < totalElements; ++endWindow) {
            int currentValue = sortedElements[endWindow].first; // Текущий элемент
            int currentGroup = sortedElements[endWindow].second; // Группа текущего элемента

            ++groupCount[currentGroup]; // Увеличиваем счетчик для текущей группы

            // Проверяем, содержатся ли все группы в текущем окне
            while (groupCount.size() == numGroups) { // Максимум O(K) итераций
                int windowStartValue = sortedElements[startWindow].first; // Начальный элемент окна
                int windowStartGroup = sortedElements[startWindow].second; // Группа начального элемента

                int currentRange = currentValue - windowStartValue; // Длина текущего диапазона
                int bestRange = range[1] - range[0]; // Длина лучшего диапазона

                // Обновляем лучший диапазон, если нашли меньший
                if (currentRange < bestRange || (currentRange == bestRange &&
                                                 windowStartValue < range[0])) {
                    range[0] = windowStartValue;
                    range[1] = currentValue;
                }

                // Уменьшаем счетчик для группы начального элемента окна
                if (--groupCount[windowStartGroup] == 0) {
                    groupCount.erase(windowStartGroup); // Удаляем группу из окна, если больше элементов нет
                }

                ++startWindow; // Сдвигаем начало окна
            }
        }

        return range;
    }
};
