CXX=g++
CXXFLAGS=-std=c++11 -Wall
TARGET=floyd-warshall.bin

all: $(TARGET)

$(TARGET): floyd-warshall.cpp
	$(CXX) $(CXXFLAGS) floyd-warshall.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
	