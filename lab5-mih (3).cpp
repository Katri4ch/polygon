#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// Cocktail Sort ("Шейкерная" сортировка):
//
// Асимптотика:
// - В худшем случае: O(n^2), так как приходится сравнивать все элементы на каждой итерации.
// - В лучшем случае: O(n), если массив уже отсортирован.
//
// Память:
// - Используется O(1) дополнительной памяти.
void CocktailSort(vector<int> &data, int n){
    bool swapped = true;
    int start = 0;
    int end = n - 1;
    while (swapped) {
        swapped = false;
        // Проход слева направо
        for (int i = start; i < end; ++i) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        // Проход справа налево
        for (int i = end - 1; i >= start; --i) {
            if (data[i] > data[i + 1]) {
                swap(data[i], data[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Shell Sort (Сортировка Шелла):
//
// Асимптотика:
// - В худшем случае: O(n^2) (для определённых последовательностей разрывов).
// - В среднем случае: O(n log^2(n)), если используются оптимальные последовательности разрывов.
//
// Память:
// - Используется O(1) дополнительной памяти.
int shellSort(vector<int> &arr, int n){
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
    return 0;
}

// Comb Sort ("Расчёска"):
//
// Асимптотика:
// - В худшем случае: O(n^2), если уменьшение разрыва не эффективно.
// - В среднем случае: O(n / log(n)), так как фактор разрыва ускоряет сортировку.
//
// Память:
// - Используется O(1) дополнительной памяти.
void combSort(vector<double> &data){
    double factor = 1.247;
    long int gap = data.size() - 1;
    bool swaped = false;
    while (gap > 1 or swaped){
        swaped = false;
        for (long int i=0; i+gap<data.size(); i++){
            if (data[i] > data[i + gap]){
                swap(data[i], data[i+gap]);
                swaped = true;
            }
        }
        if (gap > 1)
            gap /= factor;
    }
    // Последний проход для завершения сортировки
    for (long int i=1; i<data.size(); i++){
        if (data[i-1] > data[i]){
            swap(data[i-1], data[i]);
        }
    }
}

// Bucket Sort (Сортировка подсчётом):
//
// Асимптотика:
// - В среднем случае: O(n), если элементы равномерно распределены по корзинам.
// - В худшем случае: O(n^2), если все элементы попадают в одну корзину.
//
// Память:
// - Используется O(n + k) дополнительной памяти, где k - количество корзин.
void BucketSort(vector<double> &data){
    long int n = data.size();
    vector <vector <double>> bucket(n, vector<double>()); // Создаём n корзин

    // Распределяем элементы по корзинам
    for (long int i=0; i<n; i++){
        long int index = n * data[i];
        bucket[index].push_back(data[i]);
    }

    // Сортируем каждую корзину (используется Comb Sort)
    for (long int i=0; i<n; i++){
        combSort(bucket[i]);
    }

    // Собираем элементы обратно в исходный массив
    long int index = 0;
    for (long int i=0; i<n; i++){
        for (int j=0; j<bucket[i].size(); j++){
            data[index] = bucket[i][j];
            index++;
        }
    }
}


// Функция для тестирования сортировок и измерения времени выполнения
void testSortingAlgorithms(const string& inputFile, const string& outputFile, const string& inputFile_bucket) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);

    ifstream fin_bucket(inputFile_bucket);

    if (!fin.is_open() || !fout.is_open()) {
        cerr << "Ошибка открытия файлов!" << endl;
        return;
    }
    vector<double> data_bucket;
    vector<int> data;
    int value;
    while (fin >> value) {
        data.push_back(value);
    }

    vector<int> dataCopy;
    fout << "Размер входных данных: " << data.size() << endl;

    // Замер времени выполнения Cocktail Sort
    dataCopy = data;
    auto start = chrono::high_resolution_clock::now();
    CocktailSort(dataCopy, dataCopy.size());
    auto end = chrono::high_resolution_clock::now();
    fout << "CocktailSort: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " микросекунд" << endl;

    // Замер времени выполнения Shell Sort
    dataCopy = data;
    start = chrono::high_resolution_clock::now();
    shellSort(dataCopy, dataCopy.size());
    end = chrono::high_resolution_clock::now();
    cout << " ok";
    fout << "ShellSort: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " микросекунд" << endl;

    // Замер времени выполнения Bucket Sort
    double val;
    while (fin_bucket >> val) {
        data_bucket.push_back(val);
    }

    start = chrono::high_resolution_clock::now();
    BucketSort(data_bucket);
    end = chrono::high_resolution_clock::now();
    fout << "BucketSort: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " микросекунд" << endl;
    fin_bucket.close();

    fout.close();
    fin.close();
}


int main(){
    testSortingAlgorithms("input.txt", "output.txt", "input_bucket.txt");
    return 0;
}
