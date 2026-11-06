all: main

main: src/main.cpp include/DynamicArray.h
	g++ -std=c++17 -Wall -Wextra src/main.cpp -o main

clean:
	rm -f main
