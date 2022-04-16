CXX = g++
CXXFLAGS = -Wall -std=c++17

build/zap: main.cpp
	mkdir -p build/
	$(CXX) $(CXXFLAGS) main.cpp -o build/zap  -I./include/
