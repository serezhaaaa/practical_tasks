#include "../include/DynamicArray.h"
#include <new>
#include <string>

int main() {
    DynamicArray<int> a(5);
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
        DynamicArray<int> bad(-1);
    }
    catch (const std::bad_alloc& e) {
        std::cout << "bad_alloc: " << e.what() << std::endl;
    }

    DynamicArray<int> b(a);
    b.set(0, -50);
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    DynamicArray<int> c(5);
    for (int i = 0; i < 5; i++)
        c.set(i, i + 1);
    std::cout << "distance(a, c) = " << a.distance(c) << std::endl;

    DynamicArray<int> d(3);
    try {
        a.distance(d);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    DynamicArray<std::string> s(2);
    s.set(0, "hello");
    s.set(1, "world");
    std::cout << "s: " << s << std::endl;

    DynamicArray<std::string> t(2);
    try {
        s.distance(t);
    }
    catch (const std::bad_typeid& e) {
        std::cout << "bad_typeid: " << e.what() << std::endl;
    }

    return 0;
}
