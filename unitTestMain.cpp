#include "productrelease.h"
#include "product.h"
#include <iostream>
#include <string>
#include <cassert>

void testGetProductName() {
    // Test 1: Default constructor
    ProductRelease product1;
    assert(product1.getProductName() == "");

    // Test 2: Parameterized constructor
    ProductRelease product2("TestProduct", "12345678", "2024-07-01");
    assert(product2.getProductName() == "TestProduct");

    std::cout << "testGetProductName passed." << std::endl;
}

void testSetProductName() {
    ProductRelease product;
    
    // Test 1: Set valid product name
    product.setProductName("NewName");
    assert(product.getProductName() == "NewName");

    // Test 2: Set invalid product name (empty string)
    product.setProductName("");
    assert(product.getProductName() == "NewName"); // Should not change

    // Test 3: Set invalid product name (exceeds max length)
    product.setProductName("ThisNameIsTooLong");
    assert(product.getProductName() == "NewName"); // Should not change

    std::cout << "testSetProductName passed." << std::endl;
}

void testIsValid() {
    // Test 1: Default constructor
    Product product1;
    assert(!product1.isValid());

    // Test 2: Parameterized constructor with valid name
    Product product2("ValidName");
    assert(product2.isValid());

    // Test 3: Parameterized constructor with invalid name (empty string)
    try {
        Product product3("");
    } catch (...) {
        std::cout << "Caught expected exception for empty string in constructor." << std::endl;
    }

    // Test 4: Parameterized constructor with invalid name (exceeds max length)
    try {
        Product product4("NameIsTooLong");
    } catch (...) {
        std::cout << "Caught expected exception for name exceeding max length in constructor." << std::endl;
    }

    std::cout << "testIsValid passed." << std::endl;
}

void testPrintProductName() {
    // Test 1: Default constructor
    Product product1;
    std::cout << "Expected output: \nActual output: ";
    product1.printProductName();

    // Test 2: Parameterized constructor
    Product product2("TestProduct");
    std::cout << "Expected output: TestProduct\nActual output: ";
    product2.printProductName();

    // Test 3: After setting a valid name
    product2.setProductName("NewName");
    std::cout << "Expected output: NewName\nActual output: ";
    product2.printProductName();

    std::cout << "testPrintProductName passed." << std::endl;
}

int main() {
    testGetProductName();
    testSetProductName();
    testIsValid();
    testPrintProductName();
    std::cout << "All tests passed." << std::endl;
    return 0;
}
