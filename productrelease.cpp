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
 * All data members are stored linearly unsorted in the file for ease of access.
***********************************************/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <regex>
#include <cstring>
#include <filesystem>
#include <iomanip>  
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
ProductRelease ProductRelease::getProductReleaseFromUser(string productName) {
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
    const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPage = 0;                 // Current page number
    std::vector<ProductRelease> productReleases; // Vector to store matching releases

    while (!exit)                        // Loop until user chooses to exit
    {
        bool isEnd = false;              // Flag to indicate end of file
        int displayedReleases = 0;       // Count of displayed releases

        seekToBeginningOfFile();         // Reset file pointer to the beginning

        // Collect all matching product releases
        productReleases.clear();
        while (!isEnd) {
            ProductRelease release = readFromFile(isEnd); // Read a release from the file
            if (!isEnd && release.getProductName() == productName) {
                productReleases.push_back(release); // Add matching release to vector
            }
        }

        // Calculate the starting index for the current page
        int startIndex = currentPage * RELEASES_PER_PAGE;
        int endIndex = std::min(startIndex + RELEASES_PER_PAGE, static_cast<int>(productReleases.size()));

        if (startIndex >= productReleases.size()) {
            std::cout << "No more releases to display.\n";
            exit = true;
            break;
        }

        // Display the product releases for the current page
        std::cout << "======= Product Releases for " << productName << " =======\n";
        std::cout << std::left << std::setw(10) << "SELECTION" << std::setw(15) << "RELEASE" << std::setw(15) << "DATE" << "\n";
        std::cout << "-------------------------------------------\n";

        for (int i = startIndex; i < endIndex; ++i) {
            ProductRelease release = productReleases[i];
            std::cout << std::left << std::setw(10) << (i + 1) << std::setw(15) << release.getReleaseId() << std::setw(15) << release.getDate() << "\n"; // Display release details
            displayedReleases++;
        }

        // Display navigation options
        std::cout << "            ";
        if (currentPage > 0)             // Show previous page option if not on the first page
        {
            std::cout << "<-P   ";
        }
        else
        {
            std::cout << "    ";
        }

        if (endIndex < productReleases.size())   // Show next page option if not at the end of file
        {
            std::cout << "N->";
        }
        else
        {
            std::cout << "   ";
        }
        std::cout << "\nMake a Selection: ";

        // Get user input
        std::string input;
        std::cin.clear(); // Clear any error flags
        std::cin.sync();  // Synchronize the input buffer
        std::getline(std::cin, input); // Read user input

        if (input.empty()) {
            std::cout << "Invalid input. Please enter a valid selection.\n";
            continue; // Redisplay the current page
        }

        if (input == "P" || input == "p") // If user wants to go to the previous page
        {
            if (currentPage > 0) // Ensure it's not the first page
            {
                currentPage--; // Move to the previous page
            }
            else
            {
                std::cout << "There is no previous page.\n";
            }
        }
        else if (input == "N" || input == "n") // If user wants to go to the next page
        {
            if (endIndex < productReleases.size()) // Ensure it's not the end of the file
            {
                currentPage++; // Move to the next page
            }
            else
            {
                std::cout << "There is no next page.\n";
            }
        }
        else if (isNumber(input)) // Check if the input is a number
        {
            try {
                int selection = std::stoi(input); // Convert input to an integer
                if (selection > 0 && selection <= productReleases.size()) // Ensure the selection is within the displayed range
                {
                    return productReleases[selection - 1]; // Return the selected release
                }
                else
                {
                    std::cout << "Invalid selection number. Please try again.\n";
                }
            }
            catch (const std::invalid_argument& e)
            {
                std::cout << "Invalid selection number. Please try again.\n";
            }
            catch (const std::out_of_range& e)
            {
                std::cout << "Invalid input. The number is out of range. Please try again.\n";
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
    }

    return ProductRelease(); // Return a default ProductRelease object if no valid selection was made
}


bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
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
    string date(this->date);
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
    isEnd = false;

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
    // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists("/home/mha213/Desktop/CMPT276Project/technovo/")) // /etc/technovo/
        std::filesystem::create_directory("/home/mha213/Desktop/CMPT276Project/technovo/"); // /etc/technovo/
    // Attempt to open the file
    file.open("/home/mha213/Desktop/CMPT276Project/technovo/productreleases.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();

    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("/home/mha213/Desktop/CMPT276Project/technovo/productreleases.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
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
    bool nextInvalid = true;
    ProductRelease nextRead = readFromFile(nextInvalid);
    while(!nextInvalid)
    {
        if(nextRead.getProductName() == input.getProductName() && nextRead.getReleaseId() == input.getReleaseId())
            return true;
        nextRead = readFromFile(nextInvalid);
    }
    return false;
}

/*
Original file path:
bool ProductRelease::openProductReleaseFile()

{
    // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists("/etc/technovo/"))
        std::filesystem::create_directory("/etc/technovo/");
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


*/


// Helper function to check if a string is a number
bool ProductRelease::isNumber(const std::string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) {
            return false;
        }
    }
    return true;
}



/*

ProductRelease ProductRelease::getProductReleaseFromUser(std::string productName)

{
        const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPage = 0;                 // Current page number

    while (!exit)                        // Loop until user chooses to exit
    {
        bool isEnd = false;              // Flag to indicate end of file
        int skippedReleases = 0;         // Count of skipped releases
        int displayedReleases = 0;       // Count of displayed releases

        seekToBeginningOfFile();         // Reset file pointer to the beginning

        // Skip releases of previous pages
        for (int i = 0; i < currentPage * RELEASES_PER_PAGE; ++i)
        {
            ProductRelease release = readFromFile(isEnd); // Read a release from the file
            if (isEnd) // If end of file is reached, stop skipping
            {
                currentPage--; // Adjust current page as there are fewer products than expected
                break;  // Exit the loop as we have reached the end of file
            }
        }

        // Display the product releases
        std::cout << "======= Product Releases for " << productName << " =======\n";
        std::cout << std::left << std::setw(10) << "SELECTION" << std::setw(15) << "RELEASE" << std::setw(15) << "DATE" << "\n";
        std::cout << "-------------------------------------------\n";

        displayedReleases = 0;

        for (int i = 0; i < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            ProductRelease release = readFromFile(isEnd); // Read a release from the file
            if (!isEnd && release.getProductName() == productName) // Check if end of file was not reached and product matches
            {
                std::cout << std::left << std::setw(10) << (currentPage * RELEASES_PER_PAGE + i + 1) << std::setw(15) << release.getReleaseId() << std::setw(15) << release.getDate() << "\n"; // Display release details
                displayedReleases++;      // Increment the displayed release count
            }
        }

        // Display navigation options
        std::cout << "            ";
        if (currentPage > 0)             // Show previous page option if not on the first page
        {
            std::cout << "<-P   ";
        }
        else
        {
            std::cout << "    ";
        }

        if (!isEnd && displayedReleases == RELEASES_PER_PAGE)   // Show next page option if not at the end of file
        {
            std::cout << "N->";
        }
        else
        {
            std::cout << "   ";
        }
        std::cout << "\nMake a Selection: ";

        // Get user input
        std::string input;
        std::cin.clear(); // Clear any error flags
        std::cin.sync();  // Synchronize the input buffer
        std::getline(std::cin, input); // Read user input

        if (input.empty())
        {
            std::cout << "Invalid input. Please enter a valid selection.\n";
            continue; // Redisplay the current page
        }

        if (input == "P" || input == "p") // If user wants to go to the previous page
        {
            if (currentPage > 0) // Ensure it's not the first page
            {
                currentPage--; // Move to the previous page
            }
            else
            {
                std::cout << "There is no previous page.\n";
            }
        }
        else if (input == "N" || input == "n") // If user wants to go to the next page
        {
            if (displayedReleases == RELEASES_PER_PAGE && !isEnd) // Ensure it's not the end of the file
            {
                currentPage++; // Move to the next page
            }
            else
            {
                std::cout << "There is no next page.\n";
            }
        }
        else if (isNumber(input)) // Check if the input is a number
        {
            try {
                int selection = std::stoi(input); // Convert input to an integer
                if (selection > 0 && selection <= (currentPage * RELEASES_PER_PAGE + displayedReleases)) // Ensure the selection is within the displayed range
                {
                    // Seek again to the beginning of the file
                    seekToBeginningOfFile();

                    // Skip releases of previous pages and selected releases on the current page
                    for (int i = 0; i < selection - 1; ++i)
                    {
                        readFromFile(isEnd); // Read and discard releases to skip to the selected release
                    }

                    return readFromFile(isEnd); // Return the selected release
                }
                else
                {
                    std::cout << "Invalid selection number. Please try again.\n";
                }
            }
            catch (const std::invalid_argument& e)
            {
                std::cout << "Invalid selection number. Please try again.\n";
            }
            catch (const std::out_of_range& e)
            {
                std::cout << "Invalid input. The number is out of range. Please try again.\n";
            }
        }
        else
        {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
    }

    return ProductRelease(); // Return a default ProductRelease object if no valid selection was made
}


*/