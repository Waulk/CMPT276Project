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
using std::cout;
using std::cin;
using std::endl;

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
    strncpy(productName, productName.c_str(), NAMEDATESIZE);
    strncpy(releaseId, releaseId.c_str(), IDSIZE);
    strncpy(date, date.c_str(), NAMEDATESIZE);

    for(int i=productName.length(); i <  NAMEDATESIZE + 1; i++)
    {
        productName[i] = '\0';
        date[i] = '\0';
    }

    for(int i=releaseId.length(); i < IDSIZE + 1; i++)
    {
        releaseId[i] = '\0';
    }
}

/***********************************************/
ProductRelease ProductRelease::createNewProductRelease(string productName)
{
    if(productName.empty() || productName.length() > NAMEDATESIZE)
    {
        throw std::invalid_argument("Invalid product name. The product name must be a valid product within the system and have a maximum of 10 characters.");
    }

    ProductRelease newRelease;
    newRelease.setProductName(productName);

    // prompt user for release ID
    newRelease.setReleaseIdUI();

    // prompt user for release date
    newRelease.setDateUI()

    return newRelease;

}

/***********************************************/
ProductRelease ProductRelease::getProductReleaseFromUser(string productName)
{
    const int RELEASES_PER_PAGE = 20;
    bool isEnd = false;
    bool exit = false;
    int currentPage = 0;

    while(!exit)
    {
        // seek to the beginning of the file
        seekToBeginningOfFile();

        // skip releases of previous pages
        for(int i = 0; i < currentPage * RELEASES_PER_PAGE; ++i)
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
            std::cout << "No more releases to display." << std::endl;
            currentPage--;
            continue;
        }

        // display the product releases
        std::cout << "=======Product Releases=======\n";
        std::cout << "SELECTION  RELEASE ID  DATE\n";
        std::cout << "-----------------------------\n";

        for(int i = 0; i < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            ProductRelease release = readFromFile(isEnd);
            if(!isEnd)
            {
                std::cout << i + 1 << ") " << release.getReleaseId() << "  " << release.getDate() << "\n";
            }
        }

        std::cout << "            <-P   N->\n";
        std::cout << "Make a Selection: ";

        // get user input
        std::string input;
        std::cin >> input;

        if(input == "P" || input == "p")
        {
            if(currentPage > 0)
            {
                currentPage--;
            }
        }
        else if(input == "N" || input == "n")
        {
            if(!isEnd)
            {
                currentPage++;
            }
        }
        else
        {
            int selection = std::stoi(input);
            if(selection > 0 && selection <= RELEASES_PER_PAGE)
            {
                // seek again to the beginning of the file
                seekToBeginningOfFile();

                // skip releases of previous pages and selected releases on the current page
                for(int i = 0; i < currentPage * RELEASES_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd);
                }

                return readFromFile(isEnd);
            }
        }
    }

    return ProductRelease();

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
    strncpy(productName, productName.c_str(), NAMEDATESIZE);
}

/***********************************************/
void ProductRelease::setReleaseId(const string &releaseId)
{
    strncpy(releaseId, releaseId.c_str(), IDSIZE);
}

/***********************************************/
void ProductRelease::setDate(const string &date)
{
    strncpy(date, date.c_str(), NAMEDATESIZE);
}

/***********************************************/
void ProductRelease::printProductName()
{
    string name(productName); 
    cout << name << endl;  
}

/***********************************************/
void ProductRelease::setDateUI()
{
    std::string inputDate;
    bool valid = false;

    while(!valid)
    {
        cout << "=====New Release=====\n";
        cout << "Enter Release Date (YYYY-MM-DD): ";
        cin >> inputDate;

        // validate the date format
        const std::regex pattern("^(\\d{4})-(\\d{2})-(\\d{2})$");
        if(std::regex_match(inputDate, pattern))
        {
            setDate(inputDate);
            valid = true;
        }
        else
        {
            cout << "Invalid date format. Please try again.\n"; // Maki
        }
    }
/*  Maki
    if(!valid)
    {
        throw std::invalid_argument("Invalid date format. Please enter the date in the format YYYY-MM-DD.");
    }*/
}

/***********************************************/

void ProductRelease::setReleaseIdUI()
{
    string inputReleaseId;
    bool valid = false;

    while(!valid)
    {
        cout << "=====New Release=====\n";
        cout << "Enter Release Version (max 8 char.): ";
        cin >> inputReleaseId;

        // validate the release ID length
        if(inputReleaseId.length() > IDSIZE)
        {
            cout << "Release ID too long. Please enter a release ID with a maximum of 8 characters.\n";
        }
        else if(inputReleaseId.empty())
        {
            cout << "Release ID cannot be empty. Please enter a valid release ID.\n"; // Maki
        }
        else
        {
            setReleaseId(inputReleaseId);
            valid = true;
        }
    }
/*  Maki
    if(!valid)
    {
        throw std::invalid_argument("Invalid release ID. Please enter a valid release ID with a maximum of 8 characters.");
    }*/
}

/***********************************************/
ProductRelease ProductRelease:readFromFile(bool &isEnd)
{

}

/***********************************************/
bool ProductRelease::writeToFile(ProductRelease productRelease)
{

}

/***********************************************/
bool ProductRelease::seekToBeginningOfFile()
{

}

/***********************************************/
bool ProductRelease::openProductReleaseFile()
{

}

/***********************************************/
bool ProductRelease::closeProductReleaseFile()
{

}