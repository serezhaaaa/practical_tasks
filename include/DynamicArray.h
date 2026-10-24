#pragma once

class DynamicArray {
private:
    int* data;
    int size;

public:
    DynamicArray(int size);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    void print();
    void set(int index, int value);
    int get(int index);
    void push_back(int value);
    void add(DynamicArray& other);
    void sub(DynamicArray& other);
};