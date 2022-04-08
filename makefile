zap: main.cpp
	mkdir -p build/
	g++ main.cpp -Ofast -o build/zap  -I./include/ --std=c++17
