CXX=g++
CXXFLAGS = -Wall -Wextra -pedantic

TARGET=triangle

SRC=main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) -lX11 -lGL -lGLX

clean:
	rm -f $(TARGET)

.PHONY: all clean