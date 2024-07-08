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

/***********************************************/
Product::Product()
{
    memset(productName, '\0', PRODUCTNAMESIZE + 1);
}

/***********************************************/
Product::Product(string name)
{
    if (name.empty() || name.length() > PRODUCTNAMESIZE) {
        throw std::invalid_argument("Product name must be non-empty and at most 10 characters long.");
    }

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

}

/***********************************************/
bool Product::isValid()
{

}

/***********************************************/
Product Product::getProductFromUser(bool createNew)
{

}

