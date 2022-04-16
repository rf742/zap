CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include/
binaries=build/zap build/test
build/zap: main.o point.o
	mkdir -p build/
	$(CXX) $(CXXFLAGS) main.o point.o -o build/zap

build/test: point.o test_main.o test_point.o
	$(CXX) $(CXXFLAGS) test_main.o test_point.o point.o -o build/test

.PHONY: clean
clean:
	rm $(binaries) *.o

.PHONY: all
all: $(binaries)
