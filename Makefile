CXX = g++

LIBS = -lcurl

OBJECTS = URLException.o URL.o

all: main

clean:
	rm -f *.o

URLException.o: URLException.cc URLException.h
	$(CXX) -c URLException.cc
	

URL.o: URL.cc URL.h
	$(CXX) -c URL.cc	

main.o: main.cc
	$(CXX) -c main.cc 
	
main: main.o $(OBJECTS)
	$(CXX) -o main main.o $(OBJECTS) $(LIBS)
