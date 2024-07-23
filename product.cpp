/***********************************************
 * Module: product.cpp
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-08 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * product.cpp
 * This file implements the member functions defined in the product.h header file.
 * All data members are stored linearly unsorted in the file for ease of access.
***********************************************/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <iomanip>  
#include "product.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

/***********************************************/
Product::Product()
/*
 * Default constructor that initializes the productName array to an empty string.
 * 
 * Implementation Details:
 * - Uses memset to fill the productName array with null characters.
 */
{
    memset(productName, '\0', PRODUCTNAMESIZE + 1);
}

/***********************************************/
Product::Product(string name)
/* 
 * This parameterized constructor initializes the productName array with 
 * the given name. It copies the input name to the productName array using 
 * strncpy. If the input name is shorter than PRODUCTNAMESIZE, the rest 
 * of the array is filled with null characters to ensure it is properly 
 * null-terminated.
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input name to the productName array.
 * - Ensures null termination by filling remaining elements with null characters.
 */
{
    strncpy(productName, name.c_str(), PRODUCTNAMESIZE);
    
    // Fill remaining array elements with null characters if name length is less than PRODUCTNAMESIZE
    for(int i=name.length(); i < PRODUCTNAMESIZE + 1; i++){
         productName[i] = '\0';
    }
}

/***********************************************/
string Product::getProductName()
/*
 * This function creates a string object from the productName array and 
 * returns it. This ensures that the product name is returned as a standard 
 * C++ string, making it easier to work with in other parts of the code.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size productName array.
 * - Returns the constructed string.
 */
{
    string name(productName);
    return name;
}

/***********************************************/
void Product::setProductName(const string &name)
/*
 * This function sets the product name by copying the input string to the 
 * productName array using strncpy. This ensures that the productName array 
 * is properly null-terminated and does not exceed PRODUCTNAMESIZE.
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input string to the productName array.
 * - Ensures the last character is null-terminated.
 */
{
    strncpy(productName, name.c_str(), PRODUCTNAMESIZE);
}

/***********************************************/
void Product::printProductName()
/*
 * This function prints the product name to the console. It first converts 
 * the productName array to a string object, then uses cout to display it.
 * 
 * Implementation Details:
 * - Constructs a string from the productName array.
 * - Outputs the string to the console using cout.
 */
{
    string name(productName); 
    cout << name << endl;  

}

/***********************************************/
Product Product::getProductFromUser(bool createNew)
/*
 * This function interacts with the user to display a list of products and 
 * allows the user to select one. It handles pagination to display products 
 * in chunks of 20 per page. If createNew is true, the user has the option 
 * to create a new product.
 * 
 * Implementation Details:
 * - Initializes control variables for pagination and user input handling.
 * - Uses a while loop to continuously interact with the user until they exit.
 * - Seeks to the beginning of the file and skips products from previous pages 
 *   to display the current page's products.
 * - Displays the products for the current page and handles user input for 
 *   pagination or selection.
 * - If the user selects a valid product number, the function seeks to the 
 *   corresponding position in the file and reads the product.
 */
{
    const int PRODUCTS_PER_PAGE = 20;
    bool isEnd = false;
    bool exit = false;
    int currentPage = 0;

    while (!exit)
    {
        // seek to the beginning of the file
        seekToBeginningOfFile();

        // Reset isEnd flag at the start of each iteration
        isEnd = false;

        // Skip products of previous pages
        // This loop ensures that products on earlier pages are not displayed again.
        // It stops either when the required number of products have been skipped or 
        // when the end of the file is reached.
        for (int i = 0; i < currentPage * PRODUCTS_PER_PAGE; ++i)
        {
            readFromFile(isEnd); // Read and discard a product to skip it
            if (isEnd) // If end of file is reached, stop skipping
            {
                currentPage--; // Adjust current page as there are fewer products than expected
                break;  // Exit the loop as we have reached the end of file
            }
        }

        // Display the products
        std::cout << "=======Product=======\n";
        std::cout << "SELECTION  PRODUCT\n";
        std::cout << "---------------------\n";

        int displayIndex = currentPage * PRODUCTS_PER_PAGE + 1; // Initialize the display index for the current page
        int displayedProducts = 0; // Counter to track the number of displayed products

        for (int i = 0; i < PRODUCTS_PER_PAGE && !isEnd; ++i) {
        Product product = readFromFile(isEnd); // Read a product from the file
        if (!isEnd) { // Check if end of file was not reached
            cout << std::left << std::setw(10) << (std::to_string(displayIndex) + ")") << product.getProductName() << "\n"; // Display product with its selection number
            displayIndex++; // Increment the display index
            displayedProducts++; // Increment the counter for displayed products
        }
    }

        // Determine navigation options
        std::cout << "            ";
        if (currentPage > 0) // Show previous page option if not on the first page
        {
            std::cout << "<-P ";
        }
        else
        {
            std::cout << "    ";
        }

        if (createNew)
        {
            std::cout << "X ";
        }
        else
        {
            std::cout << "  ";
        }

        if (!isEnd) // Show next page option if not on the last page
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

        try {
            if (input.empty())
            {
                throw std::invalid_argument("Invalid input. Please enter a valid selection.");
            }

            if (input == "P" || input == "p") // If user wants to go to the previous page
            {
                if (currentPage > 0) // Ensure it's not the first page
                {
                    currentPage--; // Move to the previous page
                }
                else
                {
                    std::cout << "There is no previous page\n";
                }
            }
            else if (input == "N" || input == "n") // If user wants to go to the next page
            {
                if (!isEnd) // Ensure it's not the end of the file
                {
                    currentPage++; // Move to the next page
                }
                else
                {
                    std::cout << "There is no next page\n";
                }
            }
            else if (createNew && (input == "X" || input == "x")) // If user wants to create a new product
            {
                exit = true; // Set exit flag to true
                return Product(); // Return a new product
            }
            else if (isNumber(input)) // Check if the input is a number
            {
                int selection = std::stoi(input); // Convert input to an integer
                int absoluteSelectionIndex = selection - 1; // Calculate the absolute selection index

                // Ensure the selection is within the displayed range
                if (selection > 0 && absoluteSelectionIndex < (currentPage + 1) * PRODUCTS_PER_PAGE)
                {
                    // Seek again to the beginning of the file
                    seekToBeginningOfFile();

                    // Skip to the selected product
                    for (int i = 0; i < absoluteSelectionIndex; ++i)
                    {
                        readFromFile(isEnd); // Read and discard products to skip to the selected product
                    }

                    return readFromFile(isEnd); // Return the selected product
                }
                else
                {
                    std::cout << "Invalid selection number. Please try again.\n";
                }
            }
            else
            {
                std::cout << "Invalid input. Please enter a valid number.\n";
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << "\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "Invalid input. The number is out of range. Please try again.\n";
        }
    }

    return Product(); // Return a new product if the loop exits without a valid selection
}


/***********************************************/
Product Product::setProductNameUI()
/*
 * This function interacts with the user to set a product name for a new 
 * Product object. It ensures that the input name meets the specified 
 * length constraints (not empty and not longer than PRODUCTNAMESIZE).
 * 
 * Implementation Details:
 * - Initializes a Product object and a string for user input.
 * - Uses a while loop to continuously prompt the user until a valid name is entered.
 * - Checks the input name for length constraints and sets the product name if valid.
 */
{
    Product newProduct;
    string inputName;
    bool isValid = false;

    cout << "=====New Product=====" << endl;

    // The while loop continuously prompts the user to enter a product name until a valid name is provided. 
    // The loop ensures that the product name is not empty and does not exceed the maximum allowed length 
    while(!isValid)
    {
        cout << "Enter the Product Name (max 10 char.): ";
        std::getline(std::cin, inputName);

        // Check if the input name is empty
        if (inputName.empty())
        {
            cout << "Error: Product name cannot be empty. Please try again." << endl;
        }
        // Check if the input name exceeds the maximum length
        else if (inputName.length() > PRODUCTNAMESIZE)
        {
            cout << "Error: Product name cannot be longer than 10 characters. Please try again." << endl;
        }
         // If the input name is valid, set the product name and mark it as valid
        else
        {
            newProduct.setProductName(inputName);
            isValid = true;
        }
    }

    return newProduct;
}

/***********************************************/
Product Product::readFromFile(bool &isEnd)
/*
 * This function reads the next file from the internal file member.
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This moves the file "position" to the next element, so a subsequent call to readFromFile will return the next element in the file
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Product file was not open when it was expected to be!\n";
        throw std::runtime_error("Product file not open on readFromFile");
    }

    if(file.peek() == EOF)
    {
        isEnd = true;
        return Product();
    }
    isEnd = false;

    // Read the next file if it's not EOF, this will move the seek
    Product toReturn;
    file.read(toReturn.productName, sizeof(char) * PRODUCTNAMESIZE);
    return toReturn;
}

/***********************************************/
bool Product::writeToFile(Product product)
/*
 * This function will append a Product to the file
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This function will check for any entity integrity violations, if there is one it will ignore the new entry.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Product file was not open when it was expected to be!\n";
        throw std::runtime_error("Product file not open on writeToFile");
    }
    
    seekToBeginningOfFile();
    bool read = true;
    Product nextToCheck = readFromFile(read);
    while(!read)
    {
        if(nextToCheck.getProductName() == product.getProductName())
        {
            return true;
        }
        nextToCheck = readFromFile(read);
    }
    file.seekg(0, std::ios::end);
    file.write(product.productName, sizeof(char) * PRODUCTNAMESIZE);
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Product::seekToBeginningOfFile()
/*
 * This function simply just seeks to the beggining of the file.
 *
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Product file was not open when it was expected to be!\n";
        throw std::runtime_error("Product file not open on seekToBeginningOfFile");
    }
    file.seekg(0);
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Product::openProductFile()
/*
 * This function will open the products.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 */
{
    // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists("/home/mha213/Desktop/CMPT276Project/technovo/"))
        std::filesystem::create_directory("/home/mha213/Desktop/CMPT276Project/technovo/");
    // Attempt to open the file
    file.open("/home/mha213/Desktop/CMPT276Project/technovo/products.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();

    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("/home/mha213/Desktop/CMPT276Project/technovo/products.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    // Make sure the file opened and we're at the start
    return valid && seekToBeginningOfFile();
}

/***********************************************/
bool Product::closeProductFile()
/*
 * Closes the file and verifies it closed properly
 *
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Product file was not open when it was expected to be!\n";
        throw std::runtime_error("Product file not open on closeProductFile");
    }
    file.close();
    return !(file.fail() || file.bad());
}


// Helper function to check if a string is a number
bool Product::isNumber(const std::string& s) {
    for (char const &ch : s) {
        if (std::isdigit(ch) == 0) {
            return false;
        }
    }
    return true;
}