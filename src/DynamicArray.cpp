#include "../include/DynamicArray.h"
#include <iostream>
#include <stdexcept>

static bool validValue(int value) {
    return value >= -100 && value <= 100;
}

static void checkValue(int value) {
    if (!validValue(value))
        throw std::invalid_argument("значение не в границах -100..100");
}

static void checkIndex(int index, int size) {
    if (index < 0 || index >= size)
        throw std::out_of_range("индекс вне массива");
}

DynamicArray::DynamicArray(int n) {
    size = n;
    data = new int[n]();
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++)
        data[i] = other.data[i];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() {
    for (int i = 0; i < size; i++)
        std::cout << data[i] << " ";
    std::cout << std::endl;
}

void DynamicArray::set(int index, int value) {
    checkIndex(index, size);
    checkValue(value);
    data[index] = value;
}

int DynamicArray::get(int index) {
    checkIndex(index, size);
    return data[index];
}

void DynamicArray::push_back(int value) {
    checkValue(value);
    int* newData = new int[size + 1];
    for (int i = 0; i < size; i++)
        newData[i] = data[i];
    newData[size] = value;
    delete[] data;
    data = newData;
    size++;
}

void DynamicArray::add(DynamicArray& other) {
    if (other.size < size)
        throw std::out_of_range("второй массив меньше первого");
    for (int i = 0; i < size; i++)
        data[i] += other.data[i];
}

void DynamicArray::sub(DynamicArray& other) {
    if (other.size < size)
        throw std::out_of_range("второй массив меньше первого");
    for (int i = 0; i < size; i++)
        data[i] -= other.data[i];
}
