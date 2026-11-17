#include "../include/DynamicArray.h"
#include <cassert>
#include <new>
#include <string>
#include <utility>

void showArray(DynamicArray<int> arr, const int* originalData) {
    std::cout << "array: " << arr << std::endl;
    std::cout << "same buffer: " << (arr.begin() == originalData) << std::endl;
}

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

    DynamicArray<int> x(3);
    x[0] = 10;
    x[1] = x[0];

    const DynamicArray<int>& view = x;
    std::cout << "x[1] = " << view[1] << std::endl;

    try {
        x[3] = 1;
    }
    catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << std::endl;
    }

    try {
        x[1] = 150;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << std::endl;
    }

    DynamicArray<int> y(x);
    std::cout << "x == y: " << (x == y) << std::endl;

    DynamicArray<int> shorter(1);
    shorter[0] = 2;
    x += shorter;
    std::cout << "x += shorter: " << x << std::endl;
    std::cout << "x != y: " << (x != y) << std::endl;
    x -= shorter;
    std::cout << "x -= shorter: " << x << std::endl;

    x += 3;
    std::cout << "x += 3: " << x << std::endl;
    x -= 3;
    std::cout << "x -= 3: " << x << std::endl;

    for (auto& value : x)
        value++;
    for (const auto& value : view)
        std::cout << value << " ";
    std::cout << std::endl;

    DynamicArray<int> copy(1);
    DynamicArray<int> another(1);
    another = copy = x;
    assert(copy == x && another == x);
    copy[0] = 50;
    assert(copy != x);
    DynamicArray<int>& same = copy;
    copy = same;
    assert(copy.get(0) == 50);
    std::cout << "copy: " << copy << std::endl;

    const int* originalData = x.begin();
    std::cout << "copy in function:" << std::endl;
    showArray(x, originalData);
    assert(x.begin() == originalData);
    std::cout << "move in function:" << std::endl;
    showArray(std::move(x), originalData);
    assert(x.begin() == nullptr && x.begin() == x.end());

    const int* copiedData = copy.begin();
    another = std::move(copy);
    assert(another.begin() == copiedData);
    assert(copy.begin() == nullptr && copy.begin() == copy.end());

    DynamicArray<int>& sameMoved = another;
    another = std::move(sameMoved);
    assert(another.begin() == copiedData);
    std::cout << "after move: " << another << std::endl;

    copy.push_back(7);
    assert(copy.get(0) == 7);
    std::cout << "used again: " << copy << std::endl;

    return 0;
}
