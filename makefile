all: main

main: main.o DynamicArray.o
	g++ -std=c++17 -Wall -Wextra main.o DynamicArray.o -o main

main.o: src/main.cpp
	g++ -std=c++17 -Wall -Wextra -c src/main.cpp

DynamicArray.o: src/DynamicArray.cpp
	g++ -std=c++17 -Wall -Wextra -c src/DynamicArray.cpp

clean:
	rm -f *.o main