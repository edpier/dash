CXX = g++

LIBS = -lcurl -ljsoncpp
INCLUDE = -I/usr/include/jsoncpp
CFLAGS = $(INCLUDE)

OBJECTS = URLException.o URL.o

all: main oauth

clean:
	rm -f *.o

URLException.o: URLException.cc URLException.h
	$(CXX) -c URLException.cc $(CFLAGS)
	

URL.o: URL.cc URL.h
	$(CXX) -c URL.cc $(CFLAGS)	

main.o: main.cc
	$(CXX) -c main.cc $(CFLAGS) 
	
	
oauth.o: oauth.cc
	$(CXX) -c oauth.cc $(CFLAGS)
	
main: main.o $(OBJECTS)
	$(CXX) -o main main.o $(OBJECTS) $(LIBS)
	
oauth: oauth.o $(OBJECTS)
	$(CXX) -o oauth oauth.o $(OBJECTS) $(LIBS)
