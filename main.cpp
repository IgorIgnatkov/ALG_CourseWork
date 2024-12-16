#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;

// Скелет функции для замеров времени поиска
void makeSearchData();
void saveResults(ofstream& file, const string& searchType, const string& caseType, int size, double time);
// Скелеты вспомогательных функций
vector<int> createArray(int size);
void showArray(vector<int> array);
// Скелеты функции теста сортировок
void testSearch(char searchNumber);
// Скелеты функций поиска
int linearSearch(vector<int>& array, int key);
int binarySearch(vector<int>& array, int key, int leftIndex, int rightIndex);
int exponentialSearch(vector<int>& array, int key);
int interpolationSearch(vector<int>& array, int key);

int main()
{
    setlocale(LC_ALL, "ru");
    char searchNumber = '4'; 
    // 1 - Линейный
    // 2 - Бинарный
    // 3 - Экспоненциальный
    // 4 - Интерполяционный
    testSearch(searchNumber);
    //makeSearchData();

    return 1;
}

vector<int> createArray(int size) {
    // Создание рандомного массива с уникальными ключами
    vector<int> array(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < size; i++) {
        array[i] = dis(gen);
    }

    // Сортируем массив
    sort(array.begin(), array.end());

    return array;
}

void showArray(vector<int> array) {
    // Функция для вывод массива в формате Индекс: Ключ
    for (int i = 0; i < array.size(); i++) {
        cout << i << ": " << array[i] << endl;
    }
}

int linearSearch(vector<int>& array, int key) {
    // Функция для нахождения индекса ключа линейным поиском
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == key) {
            return i;
        }
    }
    
    return -1;
}

int binarySearch(vector<int>& array, int key, int leftIndex, int rightIndex) {
    // Функция для нахождения индекса ключа бинарным поиском
    if (rightIndex >= leftIndex) {
        int middleIndex = round((leftIndex + rightIndex) / 2);
        if (array[middleIndex] == key) {
            return middleIndex;
        }

        if (key < array[middleIndex]) {
            return binarySearch(array, key, leftIndex, middleIndex - 1);
        }
        else {
            return binarySearch(array, key, middleIndex + 1, rightIndex);
        }
    }

    return -1;
}

int exponentialSearch(vector<int>& array, int key) {
    // Функция для нахождения индекса ключа экспоненциальным поиском
    if (array[0] == key) {
        return 0;
    }

    int i = 1;
    while (i < array.size() && array[i] <= key) {
        i *= 2;
    }

    int minimum;
    if (i < array.size()) {
        minimum = i;
    }
    else {
        minimum = array.size() - 1;
    }

    return binarySearch(array, key, i / 2, minimum);
}

int interpolationSearch(vector<int>& array, int key) {
    // Функция для нахождения индекса ключа интерполяционным поиском
    int leftIndex = 0;
    int rightIndex = array.size() - 1;

    while (array[leftIndex] < key && key < array[rightIndex]) {
        int middleIndex = leftIndex + (key - array[leftIndex]) * (rightIndex - leftIndex) / (array[rightIndex] - array[leftIndex]);
        if (array[middleIndex] < key) {
            leftIndex = middleIndex + 1;
        }
        else if (array[middleIndex] > key) {
            rightIndex = middleIndex - 1;
        }
        else {
            return middleIndex;
        }
    }

    if (array[leftIndex] == key) {
        return leftIndex;
    }
    else if (array[rightIndex] == key) {
        return rightIndex;
    }
    else {
        return -1;
    }
}

void testSearch(char searchNumber) {
    int key = 30;
    int index_key = -1;

    vector<int> arrayTest = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    showArray(arrayTest);

    if (searchNumber == '1') {
        index_key = linearSearch(arrayTest, key);
    }
    if (searchNumber == '2') {
        int leftIndex = 0;
        int rightIndex = arrayTest.size() - 1;
        index_key = binarySearch(arrayTest, key, leftIndex, rightIndex);
    }
    if (searchNumber == '3') {
        index_key = exponentialSearch(arrayTest, key);
    }
    if (searchNumber == '4') {
        index_key = interpolationSearch(arrayTest, key);
    }

    if (index_key != -1) {
        cout << "Элемент: " << key << " Индекс: " << index_key << endl;
    }
    else {
        cout << "Такого элемента нет" << endl;
    }
}

void makeSearchData() {
    ofstream outFile("results.csv");
    if (!outFile.is_open()) {
        cout << "Ошибка открытия файла для записи данных" << endl;
    }

    for (int i = 1; i < 5; i++) {
        if (i == 1) { // Линейный поиск
            for (int j = 1; j < 4; j++) { // Три случая
                for (int size = 1000; size <= 10000; size += 1000) { // Разные размеры массива
                    vector<int> array = createArray(size);
                    int key;
                    string caseType;
                    if (j == 1) {
                        key = array[0]; // Лучший случай 
                        caseType = "Лучший";
                    }
                    else if (j == 2) {
                        key = array[size / 2]; // Средний случай
                        caseType = "Средний";
                    }
                    else {
                        key = -1; // Худший случай
                        caseType = "Худший";
                    }
                    auto start = chrono::high_resolution_clock::now();
                    int index_key = linearSearch(array, key);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    string searchType = "Линейный поиск";
                    saveResults(outFile, searchType, caseType, size, duration.count());
                }
            }
        }
        if (i == 2) { // Бинарный поиск
            for (int j = 1; j < 4; j++) { // Три случая
                for (int size = 1000; size <= 10000; size += 1000) { // Разные размеры массива
                    vector<int> array = createArray(size);
                    int key;
                    string caseType;
                    int leftIndex = 0;
                    int rightIndex = size - 1;
                    if (j == 1) {
                        key = round((leftIndex + rightIndex) / 2); // Лучший случай 
                        caseType = "Лучший";
                    }
                    else if (j == 2) {
                        key = array[size / 4]; // Средний случай
                        caseType = "Средний";
                    }
                    else {
                        key = -1; // Худший случай
                        caseType = "Худший";
                    }
                    auto start = chrono::high_resolution_clock::now();
                    int index_key = binarySearch(array, key, leftIndex, rightIndex);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    string searchType = "Бинарный поиск";
                    saveResults(outFile, searchType, caseType, size, duration.count());
                }
            }
        }
        if (i == 3) { // Экспоненциальный поиск
            for (int j = 1; j < 4; j++) { // Три случая
                for (int size = 1000; size <= 10000; size += 1000) { // Разные размеры массива
                    vector<int> array = createArray(size);
                    int key;
                    string caseType;
                    if (j == 1) {
                        key = array[0]; // Лучший случай 
                        caseType = "Лучший";
                    }
                    else if (j == 2) {
                        key = array[size / 2]; // Средний случай
                        caseType = "Средний";
                    }
                    else {
                        key = -1; // Худший случай
                        caseType = "Худший";
                    }
                    auto start = chrono::high_resolution_clock::now();
                    int index_key = exponentialSearch(array, key);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    string searchType = "Экспоненциальный поиск";
                    saveResults(outFile, searchType, caseType, size, duration.count());
                }
            }
        }
        if (i == 4) { // Интерполяционный поиск
            for (int j = 1; j < 4; j++) { // Три случая
                for (int size = 1000; size <= 10000; size += 1000) { // Разные размеры массива
                    vector<int> array = createArray(size);
                    int key;
                    string caseType;
                    int leftIndex = 0;
                    int rightIndex = size - 1;
                    if (j == 1) {
                        key = array[size / 2]; // Лучший случай 
                        caseType = "Лучший";
                    }
                    else if (j == 2) {
                        key = array[size / 4]; // Средний случай
                        caseType = "Средний";
                    }
                    else {
                        key = array[size - 1]; // Худший случай
                        caseType = "Худший";
                    }
                    auto start = chrono::high_resolution_clock::now();
                    int index_key = interpolationSearch(array, key);
                    auto end = chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    string searchType = "Интерполяционный поиск";
                    saveResults(outFile, searchType, caseType, size, duration.count());
                }
            }
        }
    }
}

void saveResults(ofstream& file, const string& searchType, const string& caseType, int size, double time) {
    file << searchType << "," << caseType << "," << size << "," << fixed << setprecision(10) << time << endl;
}
