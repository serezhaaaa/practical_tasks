#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;

    void checkValue([[maybe_unused]] T value) {
        if constexpr (std::is_integral_v<T>) {
            if (value > 100 || value < -100)
                throw std::invalid_argument("значение не в границах -100..100");
        }
    }

public:
    DynamicArray(int n) {
        size = n;
        data = new T[n]();
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void print() {
        for (int i = 0; i < size; i++)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        for (int i = 0; i < arr.size; i++)
            os << arr.data[i] << " ";
        return os;
    }

    void set(int index, T value) {
        if (index < 0 || index >= size)
            throw std::out_of_range("номер вне массива");
        checkValue(value);
        data[index] = value;
    }

    T get(int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("индекс вне массива");
        return data[index];
    }

    void push_back(T value) {
        checkValue(value);
        T* newData = new T[size + 1];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        newData[size] = value;
        delete[] data;
        data = newData;
        size++;
    }

    void add(DynamicArray& other) {
        if (other.size < size)
            throw std::out_of_range("второй массив меньше первого");
        for (int i = 0; i < size; i++)
            data[i] += other.data[i];
    }

    void sub(DynamicArray& other) {
        if (other.size < size)
            throw std::out_of_range("второй массив меньше первого");
        for (int i = 0; i < size; i++)
            data[i] -= other.data[i];
    }

    double distance(DynamicArray& other) {
        if constexpr (std::is_arithmetic_v<T>) {
            if (size != other.size)
                throw std::invalid_argument("размеры массивов не совпадают");
            double sum = 0;
            for (int i = 0; i < size; i++) {
                double diff = data[i] - other.data[i];
                sum += diff * diff;
            }
            return std::sqrt(sum);
        }
        else {
            throw std::bad_typeid();
        }
    }
};
