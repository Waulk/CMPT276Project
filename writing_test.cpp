#include <iostream>
#include "changes.h"
#include "productRelease.h"
using std::cout;
using std::endl;

// Test function to handle edge cases, such as an empty change
void test_Edge_Cases() {
    // Create a change object with empty/zero fields
    Changes* emptyChange = new Changes(0, "", "", "", 0, "", false);
    // Write the empty change to the file
    emptyChange->writeToFile(*emptyChange);
    // Check if the empty change was successfully written to the file
    if (Changes::ChangesExists(*emptyChange)) {
        cout << "Successfully wrote empty change to the file." << endl;
    } else {
        cout << "Failed to write empty change to the file." << endl;
    }
}

// Test function to write a change object to the file and verify its existence
void write_Changes_Test() {
    // Create a change object with specific fields
    Changes* changeObject = new Changes(1, "Completed", "Tennis Rack", "1.021.5", 5, "Big Tennis Racket", true);
    // Write the change object to the file
    Changes::writeToFile(*changeObject);
    // Check if the change object was successfully written to the file
    if (Changes::ChangesExists(*changeObject)) {
        cout << "The change object is written to the file and saved successfully." << endl;
    } else {
        cout << "The change object was not written to the file or was not saved properly." << endl;
    }
}

// Test function to write a product release to the file and verify its existence
void write_Product_Release_Test() {
    // Create a product release object with specific fields
    ProductRelease* product = new ProductRelease("Tennis Rack", "1.021.5", "2022-06-05");
    // Write the product release object to the file
    ProductRelease::writeToFile(*product);
    // Check if the product release object was successfully written to the file
    if (ProductRelease::productReleaseExists(*product)) {
        cout << "The product release object is written to the file and saved successfully." << endl;
    } else {
        cout << "The product release object was not written to the file or was not saved properly." << endl;
    }
}

// Main function to run all test cases
int main() {
    // Run test for writing and verifying changes
    write_Changes_Test();
    // Run test for writing and verifying product releases
    write_Product_Release_Test();
    // Run test for edge cases
    test_Edge_Cases();
    return 0;
}
