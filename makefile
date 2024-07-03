
all: main.o
test: unitTestMain.o
	
main.o: main.cpp 
	g++ -c -Wall main.cpp

unitTestMain.o: unitTestMain.cpp product.h
	g++ -c -Wall unitTestMain.cpp

cleanWindows:	
	del -f *.o
clean:	
	rm -f *.o