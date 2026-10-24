#include "../include/DynamicArray.h"
#include <iostream>

int main() {
    DynamicArray a(5);
    for (int i = 0; i < 5; i++)
        a.set(i, i * 10);
    a.print();
    a.set(7, 5);    // неверный индекс
    a.set(2, 150);  // верхняя граница пробита значение
    std::cout << "a[3] = " << a.get(3) << std::endl;
    a.get(10);      // плохой индекс

    DynamicArray b(a);
    b.set(0, -50);
    a.print();  // не поменялся
    b.print();

    a.push_back(77);
    a.push_back(101);  // больше ограничения
    a.print();

    DynamicArray c(3);
    c.set(0, 1);
    c.set(1, 2);
    c.set(2, 3);
    a.add(c);
    a.print();
    a.sub(c);
    a.print();

    return 0;
}