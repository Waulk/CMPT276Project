/***********************************************
 * Module: product.cpp
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-08 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * description
***********************************************/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include "product.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

/***********************************************/
Product::Product()
{
    memset(productName, '\0', PRODUCTNAMESIZE + 1);
}

/***********************************************/
Product::Product(string name)
{
    strncpy(productName, name.c_str(), PRODUCTNAMESIZE);
    
    for(int i=name.length(); i < PRODUCTNAMESIZE + 1; i++){
         productName[i] = '\0';
    }
}

/***********************************************/
string Product::getProductName()
{
    string name(productName);
    return name;
}

/***********************************************/
void Product::setProductName(const string &name)
{
    strncpy(productName, name.c_str(), PRODUCTNAMESIZE);
}

/***********************************************/
void Product::printProductName()
{
    string name(productName); 
    cout << name << endl;  

}

/***********************************************/
Product Product::getProductFromUser(bool createNew)
{
    const int PRODUCTS_PER_PAGE = 20;
    bool isEnd = false;
    bool exit = false;
    int currentPage = 0;

    while(!exit)
    {
        // seek to the beginning of the file
        seekToBeginningOfFile();

        // skip products of previous pages
        for(int i = 0; i < currentPage * PRODUCTS_PER_PAGE; ++i)
        {
            readFromFile(isEnd);
            if(isEnd)
            {
                currentPage--;
                break;
            }
        }

        if(isEnd)
        {
            std::cout << "No more products to display." << std::endl;
            currentPage--;
            //continue;
        }

        // display the products
        std::cout << "=======Product=======\n";
        std::cout << "SELECTION  PRODUCT\n";
        std::cout << "---------------------\n";

        for(int i = 0; i < PRODUCTS_PER_PAGE && !isEnd; ++i){
            Product product = readFromFile(isEnd);
            if (!isEnd){
                std::cout << i + 1 << " " << product.getProductName() << "\n";
            }
        }

        if (createNew)
        {
            std::cout << "            <-P X N->\n";
        }
        else
        {
            std::cout << "            <-P   N->\n";
        }
        
        std::cout << "Make a Selection: ";

        // get user input
        std::string input;
        std::cin >> input;

        if (input == "P" || input == "p")
        {
            if(currentPage > 0)
            {
                currentPage--;
            }
        }
        else if (input == "N" || input == "n")
        {
            if(!isEnd)
            {
                currentPage++;
            }
        }
        else if(createNew && (input == "X" || input == "x"))
        {
            exit = true;
            return Product();
        }
        else // when the user selects a number
        {
            int selection = std::stoi(input);
            if(selection > 0 && selection <= PRODUCTS_PER_PAGE)
            {
                // seek again to the beginning of the file
                seekToBeginningOfFile();

                // skip products of previous pages and selected products on the current page
                for(int i = 0; i < currentPage * PRODUCTS_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd);
                }

                return readFromFile(isEnd);
            }
        }
    }

    return Product();
}

/***********************************************/
Product Product::setProductNameUI()
{
    // Maki 
}
        // Returns: void
        /* This function displays an UI to prompt a user to enter a product name
        * Example UI:
        * =====New Product=====
        * Enter the Product Name (max 10 char.):
        */

/***********************************************/
Product Product::readFromFile(bool &isEnd)
{

}

/***********************************************/
bool Product::writeToFile(Product product)
{

}

/***********************************************/
bool Product::seekToBeginningOfFile()
{

}

bool Product::openProductFile()
{

}

bool Product::closeProductFile()
{

}

