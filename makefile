zap: main.cpp
	mkdir -p build/
	g++ main.cpp -Wall -o build/zap  -I./include/ --std=c++17
