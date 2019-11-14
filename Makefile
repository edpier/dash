CXX = g++

LIBS = -lcurl -ljsoncpp
INCLUDE = -I/usr/include/jsoncpp
CFLAGS = $(INCLUDE -std=c++11)

OBJECTS = URLException.o URL.o

all: main oauth stream download

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
	
stream.o: stream.cc
	$(CXX) -c stream.cc $(CFLAGS)
	
main: main.o $(OBJECTS)
	$(CXX) -o main main.o $(OBJECTS) $(LIBS)
	
oauth: oauth.o $(OBJECTS)
	$(CXX) -o oauth oauth.o $(OBJECTS) $(LIBS)
	
stream: stream.o $(OBJECTS)
	$(CXX) -o stream stream.o $(OBJECTS) $(LIBS)
	
		
			
download.o: download.cc
	$(CXX) -c download.cc $(CFLAGS)
		
download: download.o $(OBJECTS)
	$(CXX) -o download download.o $(OBJECTS) $(LIBS)
