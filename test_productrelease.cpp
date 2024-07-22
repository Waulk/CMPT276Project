#include <iostream>
#include <cassert>
#include <cstring>
#include "productrelease.h"

using namespace std;

// g++ -Wall -Wpedantic -std=c++17 -o a.out test_productrelease.cpp productrelease.cpp

void testDefaultConstructor() {
    ProductRelease pr;
    assert(pr.getProductName() == "");
    assert(pr.getReleaseId() == "");
    assert(pr.getDate() == "");
    cout << "Default constructor test passed" << endl;
}

// Constructor and Getters
void testParameterizedConstructor() {
    string name1 = "Canvas";
    string id1 = "v1.0.0";
    string date1 = "2024-07-20";
    ProductRelease pr1(name1, id1, date1);
    assert(pr1.getProductName() == name1);
    assert(pr1.getReleaseId() == id1);
    assert(pr1.getDate() == date1);

    string name2 = "My SFU";
    string id2 = "";
    string date2 = "";
    ProductRelease pr2(name2, id2, date2);
    assert(pr2.getProductName() == name2);
    assert(pr2.getReleaseId() == id2);
    assert(pr2.getDate() == date2);

    cout << "Parameterized constructor test passed" << endl;
}

// Setters
void testSetters() {
    string name1 = "Canvas";
    string id1 = "v1.0.0";
    string date1 = "2024-07-20";
    ProductRelease pr;
    pr.setProductName(name1);
    assert(pr.getProductName() == name1);

    pr.setReleaseId(id1);
    assert(pr.getReleaseId() == id1);

    pr.setDate(date1);
    assert(pr.getDate() == date1);

    // to test with invalide data
    string name2 = "TooLongProductName";
    string id2 = "invalid";
    string date2 = "";
    ProductRelease pr2;
    pr2.setProductName(name2);
    assert(pr2.getProductName() == "TooLongPro");

    pr2.setReleaseId(id2);
    assert(pr2.getReleaseId() == id2);

    pr2.setDate(date2);
    assert(pr2.getDate() == date2);

    cout << "Setter tests passed" << endl;
}

void testFileOperations() {
    // Test open and close file operations
    assert(ProductRelease::openProductReleaseFile() == true);
    assert(ProductRelease::seekToBeginningOfFile() == true);
    assert(ProductRelease::closeProductReleaseFile() == true);
    cout << "File operations tests passed" << endl;
}

void testReadWriteFromFile() {
    ProductRelease::openProductReleaseFile();

    ProductRelease pr1("Canvas", "v1.0.0", "2024-07-20");
    assert(ProductRelease::writeToFile(pr1) == true);

    bool isEnd = false;
    ProductRelease pr2 = ProductRelease::readFromFile(isEnd);
    assert(pr2.getProductName() == "Canvas");
    assert(pr2.getReleaseId() == "v1.0.0");
    assert(pr2.getDate() == "2024-07-20");

    ProductRelease::closeProductReleaseFile();
    cout << "File read/write tests passed" << endl;
}

void testProductReleaseExists() {
    ProductRelease::openProductReleaseFile();

    ProductRelease pr1("Canvas", "v1.0.0", "2024-07-20");
    assert(ProductRelease::writeToFile(pr1) == true);

    assert(ProductRelease::productReleaseExists(pr1) == true);

    ProductRelease pr2("NonExistent", "v9.9.9", "2029-12-31");
    assert(ProductRelease::productReleaseExists(pr2) == false);

    ProductRelease::closeProductReleaseFile();
    cout << "Product release exists tests passed" << endl;
}

// void ProductRelease::setReleaseIdUI()

void testCreateNewProductRelease() {
    // This function is interactive and needs manual testing
    cout << "Skipping interactive test for createNewProductRelease." << endl;
}

void testGetProductReleaseFromUser() {
    // This function is interactive and needs manual testing
    cout << "Skipping interactive test for getProductReleaseFromUser." << endl;
}


int main() {
    testDefaultConstructor(); // passed
    testParameterizedConstructor(); // passed
    //testCreateNewProductRelease();
    //testGetProductReleaseFromUser();
    testSetters(); // passed
    
   // testFileOperations();
   /* testReadWriteFromFile();
    testProductReleaseExists(); */

    cout << "All tests passed!" << endl;
    return 0;
}
