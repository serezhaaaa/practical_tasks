#include "../include/DynamicArray.h"
#include <iostream>
#include <new>
#include <stdexcept>

int main() {
    DynamicArray a(5);
    for (int i = 0; i < 5; i++)
        a.set(i, i * 10);
    a.print();

    try {
        a.set(7, 5);
    }
    catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    try {
        a.set(2, 150);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "a[3] = " << a.get(3) << std::endl;

    try {
        a.get(10);
    }
    catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    try {
        DynamicArray bad(-1);
    }
    catch (const std::bad_alloc& e) {
        std::cout << "bad_alloc: " << e.what() << std::endl;
    }

    DynamicArray b(a);
    b.set(0, -50);
    a.print();
    b.print();

    a.push_back(77);

    try {
        a.push_back(101);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    a.print();

    DynamicArray c(6);
    for (int i = 0; i < 6; i++)
        c.set(i, i + 1);
    a.add(c);
    a.print();
    a.sub(c);
    a.print();

    DynamicArray d(3);
    try {
        a.add(d);
    }
    catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    return 0;
}
