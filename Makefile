CXX = g++
CXXFLAGS = -std=c++1z
BIN = fibonacciHeap

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

all: $(obj)
	$(CXX) -o $(BIN) $^

clean:
	rm -f $(obj) $(BIN)