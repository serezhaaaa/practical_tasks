#include "../include/DynamicArray.h"
#include <iostream>

static bool validValue(int value) {
    return value >= -100 && value <= 100;
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
    if (index < 0 || index >= size) {
        std::cout << "номер вне массива" << std::endl;
        return;
    }
    if (!validValue(value)) {
        std::cout << "значение не в границах -100..100" << std::endl;
        return;
    }
    data[index] = value;
}

int DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        std::cout << "индекс вне массива" << std::endl;
        return 0;
    }
    return data[index];
}

void DynamicArray::push_back(int value) {
    if (!validValue(value)) {
        std::cout << "значение не в границах -100..100" << std::endl;
        return;
    }
    int* newData = new int[size + 1];
    for (int i = 0; i < size; i++)
        newData[i] = data[i];
    newData[size] = value;
    delete[] data;
    data = newData;
    size++;
}

void DynamicArray::add(DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        if (i < other.size)
            data[i] += other.data[i];
    }
}

void DynamicArray::sub(DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        if (i < other.size)
            data[i] -= other.data[i];
    }
}