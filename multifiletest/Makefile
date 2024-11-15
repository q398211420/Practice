CXX = g++
CXXFLAGS = -Wall -g -std=c++17
LDFLAGS =  
SRCS = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJS = $(patsubst %.cpp, obj/%.o, $(SRCS))
TARGET = filetest

all:|obj $(TARGET) #不存在obj目录时，则创建
    
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

obj:
	mkdir -p obj
	echo "aaaaaaaaa"

.PHONY: all clean

clean:
	rm -f obj/*.o $(TARGET)
