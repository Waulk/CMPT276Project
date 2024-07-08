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
    memset(productName, '\0', sizeof(productName));
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

