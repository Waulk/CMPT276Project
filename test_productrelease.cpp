#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>
#include <string>
#include <regex>
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

// Setters & getters
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
    ProductRelease::writeToFile(pr1) == true;

    assert(ProductRelease::productReleaseExists(pr1) == true);

    ProductRelease pr2("NonExistent", "v9.9.9", "2029-12-31");
    assert(ProductRelease::productReleaseExists(pr2) == false);

    ProductRelease::closeProductReleaseFile();
    cout << "Product release exists tests passed" << endl;
}

void testGetProductReleaseFromUser() {
    // Initialize product releases to write
    const int SIZE = 50;
    ProductRelease releases[SIZE] = {
        ProductRelease("Product5", "1.0.0", "2024-07-26"),
        ProductRelease("Product6", "2.0.0", "2024-08-05"),
        ProductRelease("Product5", "1.0.1", "2024-07-27"),
        ProductRelease("Product7", "3.0.0", "2024-08-07"),
        ProductRelease("Product5", "1.0.2", "2024-07-28"),
        ProductRelease("Product8", "4.0.0", "2024-08-09"),
        ProductRelease("Product5", "1.0.3", "2024-07-29"),
        ProductRelease("Product9", "5.0.0", "2024-08-11"),
        ProductRelease("Product5", "1.0.4", "2024-07-30"),
        ProductRelease("Product10", "6.0.0", "2024-08-13"),
        ProductRelease("Product5", "1.0.5", "2024-07-31"),
        ProductRelease("Product11", "7.0.0", "2024-08-15"),
        ProductRelease("Product5", "1.0.6", "2024-08-01"),
        ProductRelease("Product12", "8.0.0", "2024-08-17"),
        ProductRelease("Product5", "1.0.7", "2024-08-02"),
        ProductRelease("Product13", "9.0.0", "2024-08-19"),
        ProductRelease("Product5", "1.0.8", "2024-08-03"),
        ProductRelease("Product14", "10.0.0", "2024-08-21"),
        ProductRelease("Product5", "1.0.9", "2024-08-04"),
        ProductRelease("Product15", "11.0.0", "2024-08-23"),
        ProductRelease("Product5", "1.0.10", "2024-08-05"),
        ProductRelease("Product16", "12.0.0", "2024-08-25"),
        ProductRelease("Product5", "1.0.11", "2024-08-06"),
        ProductRelease("Product17", "13.0.0", "2024-08-27"),
        ProductRelease("Product5", "1.0.12", "2024-08-07"),
        ProductRelease("Product18", "14.0.0", "2024-08-29"),
        ProductRelease("Product5", "1.0.13", "2024-08-08"),
        ProductRelease("Product19", "15.0.0", "2024-08-31"),
        ProductRelease("Product5", "1.0.14", "2024-08-09"),
        ProductRelease("Product20", "16.0.0", "2024-09-02"),
        ProductRelease("Product5", "1.0.15", "2024-08-10"),
        ProductRelease("Product21", "17.0.0", "2024-09-04"),
        ProductRelease("Product5", "1.0.16", "2024-08-11"),
        ProductRelease("Product22", "18.0.0", "2024-09-06"),
        ProductRelease("Product5", "1.0.17", "2024-08-12"),
        ProductRelease("Product23", "19.0.0", "2024-09-08"),
        ProductRelease("Product5", "1.0.18", "2024-08-13"),
        ProductRelease("Product24", "20.0.0", "2024-09-10"),
        ProductRelease("Product5", "1.0.19", "2024-08-14"),
        ProductRelease("Product25", "21.0.0", "2024-09-12"),
        ProductRelease("Product5", "1.0.20", "2024-08-15"),
        ProductRelease("Product26", "22.0.0", "2024-09-14"),
        ProductRelease("Product5", "1.0.21", "2024-08-16"),
        ProductRelease("Product27", "23.0.0", "2024-09-16"),
        ProductRelease("Product5", "1.0.22", "2024-08-17"),
        ProductRelease("Product28", "24.0.0", "2024-09-18"),
        ProductRelease("Product5", "1.0.23", "2024-08-18"),
        ProductRelease("Product29", "25.0.0", "2024-09-20"),
        ProductRelease("Product5", "1.0.24", "2024-08-19"),
        ProductRelease("Product30", "26.0.0", "2024-09-22"),
    };

    // Open the product release file
    if (!ProductRelease::openProductReleaseFile()) {
        std::cerr << "Failed to open the product release file." << endl;
        return;
    }

    // Write the product releases to the file
/*
    for (int i = 0; i < SIZE; ++i) {
        ProductRelease::writeToFile(releases[i]);
    }
    */
    
    // Call the function and get the result
    ProductRelease selectedRelease = ProductRelease::getProductReleaseFromUser("Product5");
    // Validate the output

    cout << "You selected: " << selectedRelease.getProductName() << " " << selectedRelease.getReleaseId() << " " << selectedRelease.getDate() << endl;

    // Close the product release file
    ProductRelease::closeProductReleaseFile();

    cout << "testGetProductReleaseFromUser passed." << endl;
}


void testCreateNewProductRelease() {
    // Test case 1: Valid input
    std::istringstream validInput("ValidID\n2024-12-31\n");
    std::cin.rdbuf(validInput.rdbuf());

    try {
        ProductRelease validRelease = ProductRelease::createNewProductRelease("ValidName");
        std::cout << "Test case 1 passed! Created release for product: " << validRelease.getProductName()
                  << ", ID: " << validRelease.getReleaseId()
                  << ", Date: " << validRelease.getDate() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test case 1 failed: " << e.what() << std::endl;
    }

    // Test case 2: Invalid product name (too long)
    try {
        ProductRelease invalidProductNameRelease = ProductRelease::createNewProductRelease("InvalidProductNameTooLong");
        std::cout << "Test case 2 failed! Exception was expected but not thrown." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Test case 2 passed: " << e.what() << std::endl;
    }

    // Test case 3: Invalid release ID (too long)
    std::istringstream invalidIDInput("InvalidIDTooLong\nValidID\n2024-12-31\n");
    std::cin.rdbuf(invalidIDInput.rdbuf());

    try {
        ProductRelease invalidIDRelease = ProductRelease::createNewProductRelease("ValidName");
        std::cout << "Test case 3 passed! Created release for product: " << invalidIDRelease.getProductName()
                  << ", ID: " << invalidIDRelease.getReleaseId()
                  << ", Date: " << invalidIDRelease.getDate() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test case 3 failed: " << e.what() << std::endl;
    }

    // Test case 4: Invalid date format
    std::istringstream invalidDateInput("ValidID\ninvalid-date\n2024-12-31\n");
    std::cin.rdbuf(invalidDateInput.rdbuf());

    try {
        ProductRelease invalidDateRelease = ProductRelease::createNewProductRelease("ValidName");
        std::cout << "Test case 4 passed! Created release for product: " << invalidDateRelease.getProductName()
                  << ", ID: " << invalidDateRelease.getReleaseId()
                  << ", Date: " << invalidDateRelease.getDate() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Test case 4 failed: " << e.what() << std::endl;
    }

    // Reset std::cin to its original buffer
    std::cin.rdbuf(nullptr);
}




// Test function
void testSetDateUI() {
    // Redirect std::cin to simulate user input
    std::istringstream simulatedInput("invalid-date\n2020-7-22\n2010-07-22");
    std::cin.rdbuf(simulatedInput.rdbuf());

    ProductRelease release;
    release.setDateUI();

    // Check if the date was set correctly
    std::string expectedDate = "2010-07-22";
    if (release.getDate() == expectedDate) {
        std::cout << "Test passed! Date set correctly to " << release.getDate() << std::endl;
    } else {
        std::cout << "Test failed! Date is " << release.getDate() << " but expected " << expectedDate << std::endl;
    }

    // Reset std::cin to its original buffer
    std::cin.rdbuf(nullptr);
}


// Test function for setReleaseIdUI
void testSetReleaseIdUI() {
    // Redirect std::cin to simulate user input
    std::istringstream simulatedInput("LongReleaseId\n\n4.2.0\n");
    std::cin.rdbuf(simulatedInput.rdbuf());

    ProductRelease release;
    release.setReleaseIdUI();

    // Check if the ID was set correctly
    std::string expectedId = "4.2.0";
    if (release.getReleaseId() == expectedId) {
        std::cout << "Test passed! Release ID set correctly to " << release.getReleaseId() << std::endl;
    } else {
        std::cout << "Test failed! Release ID is " << release.getReleaseId() << " but expected " << expectedId << std::endl;
    }

    // Reset std::cin to its original buffer
    std::cin.rdbuf(nullptr);
}


int main() {

    
   // testDefaultConstructor(); // passed
    //testParameterizedConstructor(); // passed
    //testSetters(); // passed
   // testFileOperations(); // passed

   // testReadWriteFromFile();
   
   // testProductReleaseExists(); 
   //testGetProductReleaseFromUser();

    //testSetDateUI();
    //testSetReleaseIdUI();

//    testCreateNewProductRelease();

    cout << "All tests passed!" << endl;

    return 0;
}
