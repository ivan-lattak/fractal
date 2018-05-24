CC = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++14
LIBS = -lmpfr -lgmp
HEADERS = parser.h except.h
OBJ = fractal.o parser.o

default: fractal

%.o: %.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

fractal: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm *.o

.PHONY: default clean
