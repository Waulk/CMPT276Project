#include <iostream>
#include "product.h"


// g++ -Wall -Wpedantic -std=c++17 -o testproduct testproduct.cpp product.cpp

using namespace std;

// Default Constructor - Passed
void testDefaultConstructor()
{
    Product product;
    string name = product.getProductName();
    if(name.empty())
    {
        cout << "Default constructor test passed!" << endl;
    }
    else
    {
        cout << "Default constructor test failed!" << endl;
    }
}

// Constructor - Passed
void testParameterizedConstructor()
{
    string name1 = "Canvas";
    string name2 = "My SFU";
    string name3 = "";
    const char* name4 = nullptr;

    Product product1(name1);
    Product product2(name2);
    Product product3(name3);

    Product product4(name4 ? string(name4) : "");

    string res1 = product1.getProductName();
    string res2 = product2.getProductName();
    string res3 = product3.getProductName();
    string res4 = product4.getProductName();

    bool testPassed = true;

    if (name1 != res1) {
        testPassed = false;
        cout << "Parameterized constructor test failed for name1!" << endl;
        cout << "Expected: " << name1 << " Actual: " << res1 << endl;
    }

    if (name2 != res2) {
        testPassed = false;
        cout << "Parameterized constructor test failed for name2!" << endl;
        cout << "Expected: " << name2 << " Actual: " << res2 << endl;
    }

    if (name3 != res3) {
        testPassed = false;
        cout << "Parameterized constructor test failed for name3!" << endl;
        cout << "Expected: (empty string) Actual: " << res3 << endl;
    }

    if (res4 != "") {
        testPassed = false;
        cout << "Parameterized constructor test failed for null name!" << endl;
        cout << "Expected: (empty string) Actual: " << res4 << endl;
    }

    if (testPassed) {
        cout << "Parameterized constructor test passed!" << endl;
    }
}


// Setter and Getter - Passed
void testSetAndGetProductName()
{   
    string name1 = "Canvas";
    string name2 = "My SFU";
    string name3 = "";
    const char* name4 = nullptr;

    Product product1;
    Product product2;
    Product product3;
    Product product4;

    product1.setProductName(name1);
    product2.setProductName(name2);
    product3.setProductName(name3);

    // Check if nullptr (null) can be handled
    try {
        if (name4) {
            product4.setProductName(name4);
        } else {
            product4.setProductName("");
        }
    } catch (const std::exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }

    string res1 = product1.getProductName();
    string res2 = product2.getProductName();
    string res3 = product3.getProductName();
    string res4 = product4.getProductName();

    bool testPassed = true;

    if (name1 != res1) {
        testPassed = false;
        cout << "Set and get product name test failed for name1!" << endl;
        cout << "Expected: " << name1 << " Actual: " << res1 << endl;
    }

    if (name2 != res2) {
        testPassed = false;
        cout << "Set and get product name test failed for name2!" << endl;
        cout << "Expected: " << name2 << " Actual: " << res2 << endl;
    }

    if (name3 != res3) {
        testPassed = false;
        cout << "Set and get product name test failed for name3!" << endl;
        cout << "Expected: (empty string) Actual: " << res3 << endl;
    }

    if (res4 != "") {
        testPassed = false;
        cout << "Set and get product name test failed for null name!" << endl;
        cout << "Expected: (empty string) Actual: " << res4 << endl;
    }

    if (testPassed) {
        cout << "Set and get product name test passed!" << endl;
    }
}

// Print Product Name - Passed
void testPrintProductName()
{
    string name1 = "Canvas";
    string name2 = "My SFU";
    string name3 = "";
    const char* name4 = nullptr;

    Product product1(name1);
    Product product2(name2);
    Product product3(name3);

    // Check if nullptr (null) can be handled
    Product product4(name4 ? string(name4) : "");

    cout << "Expected: " << name1 << ", Actual: ";
    product1.printProductName();

    cout << "Expected: " << name2 << ", Actual: ";
    product2.printProductName();

    cout << "Expected: (empty string), Actual: ";
    product3.printProductName();

    cout << "Expected: (empty string for null), Actual: ";
    product4.printProductName();
}


void testFileOperations()
{
    
    Product product("File");

    if(Product::openProductFile())
    {
        cout << "File opened successfully!" << endl;

        Product::writeToFile(product);

        bool isEnd = false;

        Product::seekToBeginningOfFile();
        Product readProduct = Product::readFromFile(isEnd);
        if(readProduct.getProductName() == "File")
        {
            cout << "Read from file test passed" << endl;
        }
        else
        {
            cout << "Read from file test failed. product name is " << readProduct.getProductName() << endl;
        }

        if(Product::closeProductFile())
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

/*
 =====New Product=====
Enter the Product Name (max 10 char.):
*/
void testSetProductNameUI()
{
    cout << "Please enter a product name for testing setProductNameUI:\n ";
    Product product = product.setProductNameUI();
    cout << "You entered: " << product.getProductName() << endl;
}


/*
* 
    * Example UI:
    * =======Product=======
    * SELECTION  PRODUCT     
    * ---------------------                              
    * 1)  xxxxxxxxxx
    * 2)  Sea Water
    *  ...
    * 19)  Canvas
    * 20)  ProdMan
    *             <-P X N->
    * Make a Selection:
        

*/
void testGetProductReleaseFromUser()
{
    // Initialize products to write
    const int SIZE = 45;
    Product products[SIZE] = {
        Product("Sea Water"),
        Product("Canvas"),
        Product("ProdMan"),
        Product("Notebook"),
        Product("Pen"),
        Product("Laptop"),
        Product("Mug"),
        Product("Bottle"),
        Product("Charger"),
        Product("Phone"),
        Product("Mouse"),
        Product("Keyboard"),
        Product("Monitor"),
        Product("Desk"),
        Product("Chair"),
        Product("Lamp"),
        Product("Book"),
        Product("Bag"),
        Product("Shoes"),
        Product("Hat"),
        Product("Speaker"),
        Product("Camera"),
        Product("Tripod"),
        Product("Lens"),
        Product("SD Card"),
        Product("Router"),
        Product("Modem"),
        Product("Cable"),
        Product("Remote"),
        Product("Controller"),
        Product("Printer"),
        Product("Scanner"),
        Product("Paper"),
        Product("Ink"),
        Product("Tablet"),
        Product("E-reader"),
        Product("Glasses"),
        Product("Clock"),
        Product("Watch"),
        Product("Bracelet"),
        Product("Ring"),
        Product("Necklace"),
        Product("Pillow"),
        Product("Blanket"),
        Product("Mat")
    };


    // Open the product file
    if (!Product::openProductFile())
    {
        std::cerr << "Failed to open the product file." << endl;
        return;
    }

    // Write the products to the file
    for (int i = 0; i < SIZE; ++i)
    {   
        Product::writeToFile(products[i]);

    }
    
    Product product;
    Product selectedProduct = product.getProductFromUser(true);
    cout << "You selected or created: " << selectedProduct.getProductName() << endl;

    // Close the product file
    Product::closeProductFile();
}


int main()
{
    
    testDefaultConstructor();
    testParameterizedConstructor();
    testSetAndGetProductName();
    testPrintProductName();
    testSetProductNameUI();
    testGetProductFromUser();
    testFileOperations();
    

    return 0;
}
