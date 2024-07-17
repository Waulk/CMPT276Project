/***********************************************
 * Module: productrelease.cpp
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-08 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/
/***********************************************
 * productrelease.cpp
 * This file implements the member functions defined in the productrelease.h header file.
***********************************************/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <regex>
#include <cstring>
#include "productrelease.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

/***********************************************/
ProductRelease::ProductRelease()
/*
 * Default constructor that initializes member variables
 * productName, releaseId, and date to empty strings using memset.
 * 
 * Implementation Details:
 * - Uses memset to set all characters in the arrays to '\0'.
 */
{
    memset(productName, '\0', Product::PRODUCTNAMESIZE + 1); 
    memset(releaseId, '\0', IDSIZE + 1); 
    memset(date, '\0', DATESIZE + 1); 
}

/***********************************************/
ProductRelease::ProductRelease(string productName, string releaseId, string date)
/*
 * Parameterized constructor that initializes member variables
 * with provided values. It uses strncpy to copy the values 
 * into the fixed-size arrays and ensures null-termination.
 * 
 * Implementation Details:
 * - Uses strncpy to copy strings into fixed-size arrays.
 * - Ensures null termination by explicitly setting the last character.
 */
{
    strncpy(this->productName, productName.c_str(), Product::PRODUCTNAMESIZE);
    strncpy(this->releaseId, releaseId.c_str(), IDSIZE);
    strncpy(this->date, date.c_str(), DATESIZE);

    for(int i=productName.length(); i <  Product::PRODUCTNAMESIZE + 1; i++)
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
/*
 * Static function that creates a new ProductRelease object with the 
 * provided product name. It checks the validity of the product name,
 * then sets the release ID and date using user input.
 * 
 * Implementation Details:
 * - Validates product name length.
 * - Initializes a new ProductRelease object.
 * - Prompts the user to set release ID and date.
 */
{
    if(productName.empty() || productName.length() > Product::PRODUCTNAMESIZE)
    {
        throw std::invalid_argument("Invalid product name. The product name must be a valid product within the system and have a maximum of 10 characters.");
    }

    ProductRelease newRelease;
    newRelease.setProductName(productName);

    // prompt user for release ID
    newRelease.setReleaseIdUI();

    // prompt user for release date
    newRelease.setDateUI();

    return newRelease;
}

/***********************************************/
ProductRelease ProductRelease::getProductReleaseFromUser(string productName)
/*
 * Function to interactively retrieve a ProductRelease object from the user
 * by displaying paginated releases and allowing the user to select one.
 * 
 * Implementation Details:
 * - Initializes control variables for pagination and user input handling.
 * - Uses a while loop to continuously interact with the user until they exit.
 * - Seeks to the beginning of the file and skips releases from previous pages 
 *   to display the current page's releases.
 * - Displays the releases for the current page and handles user input for 
 *   pagination or selection.
 * - If the user selects a valid release number, the function seeks to the 
 *   corresponding position in the file and reads the release.
 */
{
    const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool isEnd = false;                  // Flag to indicate end of file
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPage = 0;                 // Current page number

    while(!exit)                         // Loop until user chooses to exit
    {
        // seek to the beginning of the file
        seekToBeginningOfFile();         // Reset file pointer to the beginning

        // skip releases of previous pages
        for(int i = 0; i < currentPage * RELEASES_PER_PAGE; ++i)
        {
            readFromFile(isEnd);         // Read and discard releases to skip to the current page
            if(isEnd)                    // If end of file is reached
            {
                currentPage--;           // Adjust current page number
                break;                   // Exit the loop
            }
        }

        if(isEnd)                        // If end of file was reached during skipping
        {
            std::cout << "No more releases to display." << std::endl; // Inform the user
            currentPage--;               // Adjust current page number
            continue;                    // Continue to next iteration
        }

        // display the product releases
        std::cout << "=======Product Releases=======\n";
        std::cout << "SELECTION  RELEASE ID  DATE\n";
        std::cout << "-----------------------------\n";

        for(int i = 0; i < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            ProductRelease release = readFromFile(isEnd); // Read a release from the file
            if(!isEnd)                // If end of file is not reached
            {
                std::cout << i + 1 << ") " << release.getReleaseId() << "  " << release.getDate() << "\n"; // Display release details
            }
        }

        std::cout << "            <-P   N->\n";
        std::cout << "Make a Selection: ";

        // get user input
        std::string input;
        std::cin >> input;              // Read user input

        if(input == "P" || input == "p") // If user wants to go to previous page
        {
            if(currentPage > 0)          // If not already on the first page
            {
                currentPage--;           // Go to previous page
            }
        }
        else if(input == "N" || input == "n") // If user wants to go to next page
        {
            if(!isEnd)                   // If not already at the end of the file
            {
                currentPage++;           // Go to next page
            }
        }
        else                            // If user entered a selection number
        {
            int selection = std::stoi(input); // Convert input to an integer
            if(selection > 0 && selection <= RELEASES_PER_PAGE) // If selection is valid
            {
                // seek again to the beginning of the file
                seekToBeginningOfFile();  // Reset file pointer to the beginning

                // skip releases of previous pages and selected releases on the current page
                for(int i = 0; i < currentPage * RELEASES_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd);  // Read and discard releases to skip to the selected release
                }

                return readFromFile(isEnd); // Return the selected release
            }
        }
    }

    return ProductRelease();   // Return a default ProductRelease object if no valid selection was made
}

/***********************************************/
string ProductRelease::getProductName()
/*
 * Function to get the product name as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
 */
{
    string name(productName);
    return name;
}

/***********************************************/
string ProductRelease::getReleaseId()
/*
 * Function to get the release ID as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
 */
{
    string id(releaseId);
    return id;
}

/***********************************************/
string ProductRelease::getDate()
/*
 * Function to get the release date as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
 */
{
    string date(date);
    return date;   
}

/***********************************************/
void ProductRelease::setProductName(const string &productName)
/*
 * Function to set the product name. It uses strncpy to copy the 
 * provided string into the fixed-size array and ensures null-termination.
 * 
 * Implementation Details:
 * - Uses strncpy to copy the string.
 * - Ensures the last character is null-terminated.
 */
{
    strncpy(this->productName, productName.c_str(), Product::PRODUCTNAMESIZE);
}

/***********************************************/
void ProductRelease::setReleaseId(const string &releaseId)
/*
 * Function to set the release ID. It uses strncpy to copy the 
 * provided string into the fixed-size array and ensures null-termination.
 * 
 * Implementation Details:
 * - Uses strncpy to copy the string.
 * - Ensures the last character is null-terminated.
 */
{
    strncpy(this->releaseId, releaseId.c_str(), IDSIZE);
}

/***********************************************/
void ProductRelease::setDate(const string &date)
/*
 * Function to set the release date. It uses strncpy to copy the 
 * provided string into the fixed-size array and ensures null-termination.
 * 
 * Implementation Details:
 * - Uses strncpy to copy the string.
 * - Ensures the last character is null-terminated.
 */
{
    strncpy(this->date, date.c_str(), DATESIZE);
}

/***********************************************/
void ProductRelease::printProductName()
/*
 * Function to print the product name to the console.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
 * - Outputs the string to the console.
 */
{
    string name(productName); 
    cout << name << endl;  
}

/***********************************************/
void ProductRelease::setDateUI()
/*
 * Function to prompt the user for a release date and set it.
 * It validates the date format to ensure it matches YYYY-MM-DD.
 * 
 * Implementation Details:
 * - Uses a loop to repeatedly prompt the user until a valid date is entered.
 * - Validates the input date using a regex pattern.
 * - Sets the date if the input is valid.
 */
{
    std::string inputDate;  // Declare a string variable to store the user's input
    bool valid = false;     // Declare and initialize a flag to track the validity of the input

    while(!valid)  // Loop until a valid date is entered
    {
        cout << "=====New Release=====\n";  // Display a header for the input prompt
        cout << "Enter Release Date (YYYY-MM-DD): ";  // Prompt the user to enter the release date
        cin >> inputDate;  // Read the user's input

        // Validate the date format using a regular expression
        const std::regex pattern("^(\\d{4})-(\\d{2})-(\\d{2})$");  // Define a regex pattern for YYYY-MM-DD format
        if(std::regex_match(inputDate, pattern))  // Check if the input matches the regex pattern
        {
            setDate(inputDate);  // If valid, set the release date
            valid = true;  // Set the flag to true to exit the loop
        }
        else  // If the input is not valid
        {
            cout << "Invalid date format. Please try again.\n";  // Display an error message and prompt again
        }
    }
}

/***********************************************/
void ProductRelease::setReleaseIdUI()
/*
 * Function to prompt the user for a release ID and set it.
 * It validates the length to ensure it does not exceed 8 characters.
 * 
 * Implementation Details:
 * - Uses a loop to repeatedly prompt the user until a valid release ID is entered.
 */ 
{
    string inputReleaseId;  // Declare a string variable to store the user's input
    bool valid = false;     // Declare and initialize a flag to track the validity of the input

    while(!valid)  // Loop until a valid release ID is entered
    {
        cout << "=====New Release=====\n";  // Display a header for the input prompt
        cout << "Enter Release Version (max 8 char.): ";  // Prompt the user to enter the release ID
        cin >> inputReleaseId;  // Read the user's input

        // Validate the release ID length
        if(inputReleaseId.length() > IDSIZE)  // Check if the length of the input exceeds the maximum allowed length
        {
            cout << "Release ID too long. Please enter a release ID with a maximum of 8 characters.\n";  // Display an error message if the input is too long
        }
        else if(inputReleaseId.empty())  // Check if the input is empty
        {
            cout << "Release ID cannot be empty. Please enter a valid release ID.\n";  // Display an error message if the input is empty
        }
        else  // If the input is valid
        {
            setReleaseId(inputReleaseId);  // Set the release ID using the input
            valid = true;  // Set the flag to true to exit the loop
        }
    }
}

/***********************************************/
ProductRelease ProductRelease::readFromFile(bool &isEnd)
/*
 * This function reads the next file from the internal file member.
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not the case then an error is thrown and a message is displayed.
 * - This moves the file "position" to the next element, so a subsequent call to readFromFile will return the next element in the file
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The ProductRelease file was not open when it was expected to be!\n";
        throw std::runtime_error("ProductRelease file not open on readFromFile");
    }

    if(file.peek() == EOF)
    {
        isEnd = true;
        return ProductRelease();
    }

    ProductRelease toReturn;
    file.read(toReturn.productName, sizeof(char) * Product::PRODUCTNAMESIZE);
    file.read(toReturn.releaseId, sizeof(char) * IDSIZE);
    file.read(toReturn.date, sizeof(char) * DATESIZE);
    return toReturn;
}

/***********************************************/
bool ProductRelease::writeToFile(ProductRelease productRelease)
/*
 * This function will append a ProductRelease to the file
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not the case then an error is thrown and a message is displayed.
 * - This function will not check for any entity integrity violations and will add the instance to the end of the file
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The ProductRelease file was not open when it was expected to be!\n";
        throw std::runtime_error("ProductRelease file not open on writeToFile");
    }
    file.seekg(0, std::ios::end);
    file.write(productRelease.productName, sizeof(char) * Product::PRODUCTNAMESIZE);
    file.write(productRelease.releaseId, sizeof(char) * IDSIZE);
    file.write(productRelease.date, sizeof(char) * DATESIZE);
    
    return !(file.fail() || file.bad());
}

/***********************************************/
bool ProductRelease::seekToBeginningOfFile()
/*
 * This function simply just seeks to the beggining of the file.
 *
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not the case then an error is thrown and a message is displayed.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The ProductRelease file was not open when it was expected to be!\n";
        throw std::runtime_error("ProductRelease file not open on seekToBeginningOfFile");
    }
    file.seekg(0);
    return !(file.fail() || file.bad());
}

/***********************************************/
bool ProductRelease::openProductReleaseFile()
/*
 * This function will open the productreleases.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 */
{
    // Attempt to open the file
    file.open("/etc/technovo/productreleases.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();

    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("/etc/technovo/productreleases.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    // Make sure the file opened and we're at the start
    return valid && seekToBeginningOfFile();
}

/***********************************************/
bool ProductRelease::closeProductReleaseFile()
/*
 * Closes the file and verifies it closed properly
 *
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not the case then an error is thrown and a message is displayed.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The ProductRelease file was not open when it was expected to be!\n";
        throw std::runtime_error("ProductRelease file not open on closeProductReleaseFile");
    }
    file.close();
    return !(file.fail() || file.bad());
}

/***********************************************/
bool ProductRelease::productReleaseExists(ProductRelease input)
/*
 * Checks if a productRelease already exists within the system
 *
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not the case then an error is thrown and a message is displayed.
 * - Loops through the file linearly and checks every single instance
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The ProductRelease file was not open when it was expected to be!\n";
        throw std::runtime_error("ProductRelease file not open on productReleaseExists");
    }
    seekToBeginningOfFile();
    bool nextValid = true;
    ProductRelease nextRead = readFromFile(nextValid);
    while(nextValid)
    {
        if(nextRead.getProductName() == input.getProductName() && nextRead.getReleaseId() == input.getReleaseId())
            return true;
    }
    return false;
}