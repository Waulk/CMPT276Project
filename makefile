
all: technovo
test: unitTestMain.o

technovo: main.o userinterface.o 
	g++ -o technovo main.o userinterface.o
	
main.o: main.cpp userinterface.o
	g++ -c -std=c++17 -Wall main.cpp 

userinterface.o: userinterface.cpp userinterface.h
	g++ -c -std=c++17 -Wall userinterface.cpp

unitTestMain.o: unitTestMain.cpp product.h
	g++ -c -std=c++17 -Wall unitTestMain.cpp

productrelease.o: productrelease.cpp product.h
	g++ -c -std=c++17 -Wall productrelease.cpp

product.o: product.cpp product.h
	g++ -c -std=c++17 -Wall product.cpp

cleanWindows:	
	del -f *.o
clean:	
	rm -f *.o