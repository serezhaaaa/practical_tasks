#pragma once
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <utility>

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
        std::unique_ptr<T[]> newData(new T[size]);
        for (int i = 0; i < size; i++)
            newData[i] = other.data[i];
        data = newData.release();
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other)
            return *this;

        DynamicArray copy(other);
        std::swap(data, copy.data);
        std::swap(size, copy.size);
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other)
            return *this;

        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
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

    class Element {
        DynamicArray& array;
        int index;

    public:
        Element(DynamicArray& array, int index) : array(array), index(index) {}

        operator T() const {
            return array.get(index);
        }

        Element& operator=(T value) {
            array.set(index, value);
            return *this;
        }

        Element& operator=(const Element& other) {
            return *this = other.array.get(other.index);
        }
    };

    Element operator[](int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("индекс вне массива");
        return Element(*this, index);
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw std::out_of_range("индекс вне массива");
        return data[index];
    }

    bool operator==(const DynamicArray& other) const {
        if (size != other.size)
            return false;

        for (int i = 0; i < size; i++)
            if (!(data[i] == other.data[i]))
                return false;

        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        for (int i = 0; i < size && i < other.size; i++)
            data[i] += other.data[i];
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        for (int i = 0; i < size && i < other.size; i++)
            data[i] -= other.data[i];
        return *this;
    }

    DynamicArray& operator+=(T value) {
        for (int i = 0; i < size; i++)
            data[i] += value;
        return *this;
    }

    DynamicArray& operator-=(T value) {
        for (int i = 0; i < size; i++)
            data[i] -= value;
        return *this;
    }

    T* begin() {
        return data;
    }

    T* end() {
        if (size == 0)
            return data;
        return data + size;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        if (size == 0)
            return data;
        return data + size;
    }

    void push_back(T value) {
        checkValue(value);
        std::unique_ptr<T[]> newData(new T[size + 1]);
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        newData[size] = value;
        delete[] data;
        data = newData.release();
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
