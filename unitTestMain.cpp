// unitTestMain.cpp

#include "product.h"
#include <iostream>

void testGetProductName() {
    Product p;
    std::string name = p.getProductName();
    std::cout << "GetProductName test completed.\n";
}

void testSetProductName() {
    Product p;
    p.setProductName("TestProduct");
    std::cout << "SetProductName test completed.\n";
}

int main() {
    
    testGetProductName();
    testSetProductName();

    std::cout << "All tests completed.\n";
    return 0;
}
