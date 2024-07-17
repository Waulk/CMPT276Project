
all: technovo
test: writing_test

technovo: main.o userinterface.o 
	g++ -o technovo main.o userinterface.o
	
main.o: main.cpp userinterface.o
	g++ -c -std=c++17 -Wall main.cpp 

writing_test: writing_test.o product.o productrelease.o report.o reporter.o changes.o
	g++ -o writing_test -std=c++17 product.o productrelease.o report.o reporter.o changes.o writing_test.o
functional_test: functional_test.o product.o productrelease.o report.o reporter.o changes.o
	g++ -o functional_test -std=c++17 functional_test.o product.o productrelease.o report.o reporter.o changes.o
functional_test.o: functional_test.cpp reporter.h
	g++ -c -std=c++17 -Wall functional_test.cpp

writing_test.o: writing_test.cpp product.h productrelease.h report.h reporter.h changes.h
	g++ -c -std=c++17 -Wall writing_test.cpp

changes.o: changes.cpp changes.h
	g++ -c -std=c++17 -Wall changes.cpp

userinterface.o: userinterface.cpp userinterface.h
	g++ -c -std=c++17 -Wall userinterface.cpp


unitTestMain.o: unitTestMain.cpp product.h
	g++ -c -std=c++17 -Wall unitTestMain.cpp

productrelease.o: productrelease.cpp product.h
	g++ -c -std=c++17 -Wall productrelease.cpp

product.o: product.cpp product.h
	g++ -c -std=c++17 -Wall product.cpp

report.o: report.cpp report.h
	g++ -c -std=c++17 -Wall report.cpp
reporter.o: reporter.cpp reporter.h
	g++ -c -std=c++17 -Wall reporter.cpp

cleanWindows:	
	del -f *.o
	del technovo.exe
clean:	
	rm -f *.o