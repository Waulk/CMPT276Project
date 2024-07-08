/***********************************************
 * Module: productrelease.cpp
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
#include "productrelease.h"
using std::string;

/***********************************************/
ProductRelease::ProductRelease()
{
    memset(productName, '\0', NAMEDATESIZE + 1); 
    memset(releaseId, '\0', IDSIZE + 1); 
    memset(date, '\0', NAMEDATESIZE + 1); 
}

/***********************************************/
ProductRelease::ProductRelease(string productName, string releaseId, string date)
{

}

/***********************************************/
ProductRelease ProductRelease::createNewProductRelease(string productName)
{

}

/***********************************************/
ProductRelease ProductRelease::getProductReleaseFromUser(string productName)
{

}

/***********************************************/
string ProductRelease::getProductName()
{
    string name(productName);
    return name;
}

/***********************************************/
string ProductRelease::getReleaseId()
{
    string id(releaseId);
    return id;
}

/***********************************************/
string ProductRelease::getDate()
{
    string date(date);
    return date;   
}

/***********************************************/
void ProductRelease::setProductName(const string &productName)
{

}

/***********************************************/
void ProductRelease::setReleaseId(const string &releaseId)
{

}

/***********************************************/
void ProductRelease::setDate(const string &date)
{

}

/***********************************************/
void ProductRelease::printProductName()
{

}

/***********************************************/
void ProductRelease::setProductNameUI()
{

}

/***********************************************/
void ProductRelease::setDateUI()
{

}

/***********************************************/
void ProductRelease::setReleaseIdUI()
{

}

/***********************************************/
bool ProductRelease::isValid()
{

}