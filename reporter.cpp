/***********************************************
 * Module: reporter.cpp
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-14 Original by Anmol Sangha
 *         - Initial version 
 ***********************************************/
/***********************************************
 * reporter.cpp
 * This file implements the member functions defined in the reporter.h header file
 * ***********************************************/

#include "reporter.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;
std::fstream Reporter::file;

/***********************************************/
Reporter::Reporter() 
/*
 * Default constructor that initializes the member variables
 *
 * Implementation Details:
 * uses memset to set all characters in the members to null
*/
{
    memset(email, 0, EMAILDATASIZE + 1);
    memset(customerName, 0, CUSTOMERNAMESIZE + 1);
    memset(phoneNumber, 0, PHONENUMBERSIZE + 1);
    memset(deparmentId, 0, DEPTIDSIZE + 1);
}

/***********************************************/
Reporter::Reporter(string email, string customerName, string phoneNumber, string deparmentId) 
/*
 * Constructor that initializes member variables with values
 *
 * Implementation Details:
 * Checks each string to insure valid input (not empty and not longer than fixed size)
 * Uses strncpy to copy string to arrays
 * Uses for loops to change rest of fixed size to null characters  
*/
{
    if (email.empty() || email.size() > EMAILDATASIZE + 1 ||
        customerName.empty() || customerName.size() > CUSTOMERNAMESIZE + 1 ||
        phoneNumber.empty() || phoneNumber.size() > PHONENUMBERSIZE + 1 ||
        (!deparmentId.empty() && deparmentId.size() > DEPTIDSIZE + 1 )) 
    {
        throw std::invalid_argument("Invalid input size");
    }
    strncpy(this->email, email.c_str(), EMAILDATASIZE);
    strncpy(this->customerName, customerName.c_str(), CUSTOMERNAMESIZE);
    strncpy(this->phoneNumber, phoneNumber.c_str(), PHONENUMBERSIZE);
    strncpy(this->deparmentId, deparmentId.c_str(), DEPTIDSIZE);

    this->email[EMAILDATASIZE + 1] = '\0';
    this->customerName[CUSTOMERNAMESIZE + 1] = '\0';
    this->phoneNumber[PHONENUMBERSIZE + 1] = '\0';
    this->deparmentId[DEPTIDSIZE + 1] = '\0';
}

/***********************************************/
bool Reporter::checkEmail(const string &email) 
/*
 * Checks if provided email exists
 *
 * Implementation Details:
 * Checks email is valid size (not empty and not longer than fixed size)
*/
{
    if (email.empty() || email.size() > EMAILDATASIZE + 1) 
    {
        std::cerr << "Invalid email" << std::endl;
        return false;
    }



    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        string fileEmail;
        iss >> fileEmail;

        if (fileEmail == email) 
        {
            return false;
        }
    }
    return true;
}

/***********************************************/
string Reporter::getCustomerInfo(const string &email) 
/*
 * Gets all the information about the customer
 *
 * Implementation Details:
 * Checks if email exists
*/
{
    if (!checkEmail(email)) 
    {
        return "Customer does not exist";
    }

    

    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        string fileEmail;
        iss >> fileEmail;

        if (fileEmail == email) 
        {
            string customerInfo;
            getline(iss, customerInfo);
            return customerInfo;
        }
    }
    return "Error: Customer information not found";
}

/***********************************************/
bool Reporter::setCustomer(Reporter reporter)
/*
 * Adds the customers information to the reporter file
 *
 * Implentation Details:
 * 
*/ 
{
    if (!writeToFile(reporter)) 
    {
        std::cerr << "Failed to write to file" << std::endl;
        return false;
    }
    return true;
    
}

/***********************************************/
void Reporter::reporterUI(bool createNew)
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
    const int REPORTERS_PER_PAGE = 20;
    bool isEnd = false;
    bool exit = false;
    int currentPage = 0;

    while(!exit)
    {
        // Skip products of previous pages
        // This loop ensures that reporters on earlier pages are not displayed again.
        // It stops either when the required number of reporters have been skipped or 
        // when the end of the file is reached.
        for(int i = 0; i < currentPage * REPORTERS_PER_PAGE; ++i)
        {
            readFromFile(isEnd); // Read and discard a product to skip it
            if(isEnd) // If end of file is reached, stop skipping
            {
                currentPage--; // Adjust current page as there are fewer reporters than expected
                break;  // Exit the loop as we have reached the end of file
            }
        }

        if(isEnd) // Check if end of file was reached during skipping
        {
            std::cout << "No more reporters to display." << std::endl; // Inform the user
            currentPage--; // Adjust current page as there are no more products
            //continue;
        }

        // Display the products
        std::cout << "=======Reporter=======\n";
        std::cout << "SELECTION  REPORTERS\n";
        std::cout << "---------------------\n";
        
        // This loop reads and displays reporters for the current page.
        // It stops either when REPORTERS_PER_PAGE products are displayed 
        // or when the end of the file is reached.
        for(int i = 0; i < REPORTERS_PER_PAGE && !isEnd; ++i){
            Reporter reporter = readFromFile(isEnd); // Read a reporter from the file
            if (!isEnd){ // Check if end of file was not reached
                std::cout << i + 1 << " " << reporter.email <<" " <<reporter.customerName<<" " <<reporter.phoneNumber<<" " <<reporter.deparmentId<<"\n"; // Display reporter with its selection number
            }
        }

        // Display navigation options based on whether creating new reporter is allowed
        if (createNew)
        {
            std::cout << "            <-P X N->\n"; // Allow navigating previous/next page or creating new product
        }
        else
        {
            std::cout << "            <-P   N->\n"; // Allow navigating previous/next page only
        }
        
        std::cout << "Make a Selection: ";

        // Get user input
        std::string input;
        std::cin >> input; // Read user input

        if (input == "P" || input == "p") // If user wants to go to the previous page
        {
            if(currentPage > 0) // Ensure it's not the first page
            {
                currentPage--; // Move to the previous page
            }
        }
        else if (input == "N" || input == "n") // If user wants to go to the next page
        {
            if(!isEnd) // Ensure it's not the end of the file
            {
                currentPage++; // Move to the next page
            }
        }
        else if(createNew && (input == "X" || input == "x")) // If user wants to create a new reporter
        {
            exit = true; // Set exit flag to true
            return; // Return a new reporter
        }
        else // When the user selects a number
        {
            int selection = std::stoi(input); // Convert input to an integer
            if(selection > 0 && selection <= REPORTERS_PER_PAGE) // Ensure the selection is within the displayed range
            {
                // Skip reporters of previous pages and selected reporter on the current page
                for(int i = 0; i < currentPage * REPORTERS_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd); // Read and discard reporters to skip to the selected reporter
                }

                return;
            }
            else
            {
                throw std::out_of_range("Invalid selection number."); // Throw exception if the selection is out of range
            }
        }
    }

    return; 
}

/***********************************************/
bool Reporter::openReporterFile() 
{
    return true;
}

/***********************************************/
void reporterFileStart()
{
    return;
}

/***********************************************/
bool Reporter::writeToFile(Reporter reporter) 
{
    std::cout << reporter.email << std::endl;
    return true;
}
/***********************************************/

Reporter Reporter::readFromFile(bool &isEnd)
/*
 * This function reads the next file from the internal file member.
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid
 * - This moves the file "position" to the next element, so a subsequent call to readFromFile will return the next element in the file
 */
{
    if(file.peek() == EOF)
    {
        isEnd = true;
        return Reporter();
    }

    // Read the next file if it's not EOF, this will move the seek
    Reporter toReturn;
    file.read(toReturn.email, sizeof(char) * EMAILDATASIZE);
    file.read(toReturn.customerName, sizeof(char) * CUSTOMERNAMESIZE);
    file.read(toReturn.phoneNumber, sizeof(char) * PHONENUMBERSIZE);
    file.read(toReturn.deparmentId, sizeof(char) * DEPTIDSIZE);
    return toReturn;
}


/***********************************************/
bool Reporter::closeReporterFile() 
{
    return true;
}

