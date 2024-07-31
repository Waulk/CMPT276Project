/***********************************************
 * Module: testchanges.cpp
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-30 Original by Matthew Liu
 *         - Initial version 
 ***********************************************/

/***********************************************
 * This file contains test functions for the Changes class.
 * It includes tests for constructors, getters, setters, and file operations.
***********************************************/

// g++ -Wall -Wpedantic -std=c++17 -o testchanges testchanges.cpp changes.cpp

#include <iostream>
#include "changes.h"

using namespace std;

// Default Constructor
void testDefaultConstructor()
{
    Changes change;
    if(change.getchangeId() == 0 && change.getchangeStatus().empty() && change.getProductName().empty() &&
       change.getReleaseId().empty() && change.getPriority() == 0 && change.getDescription().empty() && !change.getIsBug())
    {
        cout << "Default constructor test passed!" << endl;
    }
    else
    {
        cout << "Default constructor test failed!" << endl;
    }
}

// Parameterized Constructor
void testParameterizedConstructor()
{
    int changeId = 1;
    string changeStatus = "New";
    string productName = "Test";
    string releaseId = "R1";
    int priority = 3;
    string description = "Test description";
    bool isBug = true;

    Changes change(changeId, changeStatus, productName, releaseId, priority, description, isBug);

    bool testPassed = true;

    if (change.getchangeId() != changeId) {
        testPassed = false;
        cout << "Parameterized constructor test failed for changeId!" << endl;
    }

    if (change.getchangeStatus() != changeStatus) {
        testPassed = false;
        cout << "Parameterized constructor test failed for changeStatus!" << endl;
    }

    if (change.getProductName() != productName) {
        testPassed = false;
        cout << "Parameterized constructor test failed for productName!" << endl;
    }

    if (change.getReleaseId() != releaseId) {
        testPassed = false;
        cout << "Parameterized constructor test failed for releaseId!" << endl;
    }

    if (change.getPriority() != priority) {
        testPassed = false;
        cout << "Parameterized constructor test failed for priority!" << endl;
    }

    if (change.getDescription() != description) {
        testPassed = false;
        cout << "Parameterized constructor test failed for description!" << endl;
    }

    if (change.getIsBug() != isBug) {
        testPassed = false;
        cout << "Parameterized constructor test failed for isBug!" << endl;
    }

    if (testPassed) {
        cout << "Parameterized constructor test passed!" << endl;
    }
}

// Setters and Getters
void testSettersAndGetters()
{
    Changes change;

    change.setchangeId(2);
    change.setchangeStatus("InProg");
    change.setProductName("Test");
    change.setReleaseId("R2");
    change.setPriority(4);
    change.setDescription("Updated description");
    change.setIsBug(false);

    bool testPassed = true;

    if (change.getchangeId() != 2) {
        testPassed = false;
        cout << "Setter/Getter test failed for changeId!" << endl;
    }

    if (change.getchangeStatus() != "InProg") {
        cout << change.getchangeStatus() << endl;
        testPassed = false;
        cout << "Setter/Getter test failed for changeStatus!" << endl;
    }

    if (change.getProductName() != "Test") {
        cout << change.getProductName() << endl;
        testPassed = false;
        cout << "Setter/Getter test failed for productName!" << endl;
    }

    if (change.getReleaseId() != "R2") {
        testPassed = false;
        cout << "Setter/Getter test failed for releaseId!" << endl;
    }

    if (change.getPriority() != 4) {
        testPassed = false;
        cout << "Setter/Getter test failed for priority!" << endl;
    }

    if (change.getDescription() != "Updated description") {
        testPassed = false;
        cout << "Setter/Getter test failed for description!" << endl;
    }

    if (change.getIsBug() != false) {
        testPassed = false;
        cout << "Setter/Getter test failed for isBug!" << endl;
    }

    if (testPassed) {
        cout << "Setters and Getters test passed!" << endl;
    }
}

// File Operations
void testFileOperations()
{
    Changes change(3, "New", "FileTestProduct", "R3", 2, "File operation test", true);

    if(Changes::openChangesFile())
    {
        cout << "File opened successfully!" << endl;

        Changes::writeToFile(change);

        bool isEnd = false;

        Changes::seekToBeginningOfFile();
        Changes readChange = Changes::readFromFile(isEnd);
        if(readChange.getchangeId() == 3 && readChange.getProductName() == "FileTestProduct")
        {
            cout << "Read from file test passed" << endl;
        }
        else
        {
            cout << "Read from file test failed. Change details: " 
                 << readChange.getchangeId() << ", " << readChange.getProductName() << endl;
        }

        if(Changes::closeChangesFile())
        {
            cout << "File closed successfully" << endl;
        }
        else
        {
            cout << "File close failed" << endl;
        }
    }
    else
    {
        cout << "File open failed" << endl;
    }
}

void testWriteChanges()
{
    bool testPassed = false;
    // Initialize changes to write
    const int SIZE = 20;
    Changes changes[SIZE] = {
        Changes(1, "New", "Canvas", "1.19.0", 3, "Add dark mode feature", false),
        Changes(2, "InProgress", "ProdMan", "1.20.1", 2, "Fix login bug", true),
        Changes(3, "Done", "Sea Water", "1.23.5", 1, "Optimize database queries", false),
        Changes(4, "New", "Notebook", "1.22.2", 4, "Implement user notifications", false),
        Changes(5, "Cancelled", "Pen", "1.01.0", 5, "Add voice recognition", false),
        Changes(6, "InProgress", "Laptop", "1.42.1", 3, "Update UI design", false),
        Changes(7, "New", "Mug", "1.41.0", 2, "Fix memory leak", true),
        Changes(8, "Done", "Bottle", "2.32.3", 1, "Add export to PDF feature", false),
        Changes(9, "InProgress", "Charger", "3.32.0", 4, "Implement two-factor auth", false),
        Changes(10, "New", "Phone", "1.25.2", 3, "Add support for new API", false),
        Changes(11, "Cancelled", "Mouse", "1.43.5", 5, "Redesign homepage", false),
        Changes(12, "InProgress", "Keyboard", "1.22.7", 2, "Fix cross-browser issues", true),
        Changes(13, "Done", "Monitor", "4.24.0", 1, "Implement caching system", false),
        Changes(14, "New", "Desk", "1.12.1", 4, "Add multi-language support", false),
        Changes(15, "InProgress", "Chair", "3.11.33", 3, "Optimize image loading", false),
        Changes(16, "Cancelled", "Lamp", "1.43.5", 5, "Redesign homepage", false),
        Changes(17, "InProgress", "Book", "1.22.7", 2, "Fix cross-browser issues", true),
        Changes(18, "Done", "Bag", "4.24.0", 1, "Implement caching system", false),
        Changes(19, "New", "Shoes", "1.12.1", 4, "Add multi-language support", false),
        Changes(20, "InProgress", "Hat", "3.11.33", 3, "Optimize image loading", false)
    };

    // Open the changes file
    if (!Changes::openChangesFile())
    {
        std::cerr << "Failed to open the changes file." << std::endl;
        return;
    }

    // Write the changes to the file
    for (int i = 0; i < SIZE; ++i)
    {   
        Changes::writeToFile(changes[i]);
    }

    // Changes change;
    // change.setProductName("test");
    // Changes selectedChange = change.viewNewChangesUI();
    // selectedChange.viewNewChangesUI();
    // std::cout << "You selected or created change: " << selectedChange.getDescription() << std::endl;

    // Create a Changes object to use viewNewChangesUI
    Changes change;
    
    std::cout << "Testing viewNewChangesUI and editing priority:" << std::endl;
    
    // Use viewNewChangesUI to select a change
    Changes selectedChange = change.viewNewChangesUI();
    
    // Display the selected change
    std::cout << "Selected change: " << selectedChange.getDescription() << std::endl;

    // Close the changes file
    Changes::closeChangesFile();

    if (testPassed) {
        std::cout << "testWriteChanges passed!" << std::endl;
    } else {
        std::cout << "testWriteChanges failed." << std::endl;
    }
}

// Main function to run all tests
int main()
{
    testDefaultConstructor();
    testParameterizedConstructor();
    testSettersAndGetters();
    // testFileOperations();
    testWriteChanges();

    return 0;
}
