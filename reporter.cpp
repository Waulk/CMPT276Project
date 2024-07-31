/***********************************************
 * Module: reporter.cpp
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-30 Edited by Anmol Sangha
 *         - Added funcation and updated the code
 * Ver. 1: - 2024-07-14 Original by Anmol Sangha
 *         - Initial version 
 ***********************************************/
/***********************************************
 * reporter.cpp
 * This file implements the member functions defined in the reporter.h header file
 * All data members are stored linearly unsorted in the file for ease of access.
 ************************************************/

#include "reporter.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <filesystem>
#include <vector>
using namespace std;

/***********************************************/
Reporter::Reporter() 
/*
 * Default constructor that initializes the member variables
 *
 * Implementation Details:
 * - uses memset to set all characters in the members to null
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
 * - Checks each string to insure valid input (not empty and not longer than fixed size)
 * - Uses strncpy to copy string to arrays
 * - Uses for loops to change rest of fixed size to null characters  
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

    this->email[EMAILDATASIZE] = '\0';
    this->customerName[CUSTOMERNAMESIZE] = '\0';
    this->phoneNumber[PHONENUMBERSIZE] = '\0';
    this->deparmentId[DEPTIDSIZE] = '\0';
}

/***********************************************/
string Reporter::getEmail()
/*
 * Function to get the email as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
*/
{
    return string(this->email);
}

/***********************************************/
string Reporter::getCustomerName()
/*
 * Function to get the name as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
*/
{
    return string(this->customerName);
}

/***********************************************/
string Reporter::getPhoneNumber()
/*
 * Function to get the phone number as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
*/
{
    return string(this->phoneNumber);
}

/***********************************************/
string Reporter::getDepartmentId()
/*
 * Function to get the department id as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
*/
{
    return string(this->deparmentId);
}

/***********************************************/
Reporter Reporter::checkEmail(const string &email) 
/*
 * Checks if provided email exists
 *
 * Implementation Details:
 * - Checks email is valid size (not empty and not longer than fixed size)
 * - Iterates through the file to see if the email already exists
*/
{
   if (email.empty() || email.size() > EMAILDATASIZE + 1) 
    {
        std::cerr << "Invalid email" << std::endl;
        return Reporter();
    }

    seekToBeginningOfFile();
    bool isEnd = false;
    while (!isEnd) 
    {
        Reporter reporter = readFromFile(isEnd);
        if (!isEnd && strcmp(reporter.email, email.c_str()) == 0) 
        {
            return reporter;
        }
    }
    return Reporter();
}

/***********************************************/
Reporter Reporter::reporterUI()
/*
 * This function interacts with the user to create a new reporter.
 * 
 * Implementation Details:
 * - Prompts the user for email, name, phone number, and department (if applicable).
 * - Ensures the entered email is unique before creating a new Reporter object.
 * - Writes the new reporter to the file and returns the created object.
 */
{

    std::string email, customerName, phoneNumber, departmentId;
    bool getEmail = true;
    // Loops until either an email is found that doesn't belong to a customer or the correct customer is found
    while(getEmail)
    {
        std::cout << "Enter the Customer's Email (max 24 char.):\n";
        getline(std::cin, email);
        // Return to main menu
        if(email.empty())
                throw std::invalid_argument("Invalid Response by User");
        
        Reporter foundReporter = checkEmail(email);
        if(foundReporter.getCustomerName() != "")
        {
            std::cout << "Is the Customer's name " << foundReporter.getCustomerName() << "(Y/N)?\n";
            std::string response;
            getline(std::cin, response);
            if(response == "Y" || response == "y")
            {
                return foundReporter;
            }
        }
        else
            getEmail = false;
    }
    std::cout << "Customer not found!\n";

    std::cout << "Enter the Customer's Name (max 30 char.):\n";
    getline(std::cin, customerName);
    if(customerName.empty())
            throw std::invalid_argument("Invalid Response by User");

    std::cout << "Enter the Customer's Phone Number (10-11 digits):\n";
    getline(std::cin, phoneNumber);
    if(phoneNumber.empty())
            throw std::invalid_argument("Invalid Response by User");
    
    std::cout << "Is the Customer an employee with a department (Y/N)?\n";
    std::string worksAtCompany;
    getline(std::cin, worksAtCompany);
    if(worksAtCompany.empty())
            throw std::invalid_argument("Invalid Response by User");
    if (worksAtCompany == "y" || worksAtCompany == "Y") 
    {
        std::cout << "What is the Employee's Department (max 12 char.):\n";
        getline(std::cin, departmentId);
        if(departmentId.empty())
            throw std::invalid_argument("Invalid Response by User");
    } else 
    {
        departmentId = "";
    }

    Reporter newReporter(email, customerName, phoneNumber, departmentId);
    writeToFile(newReporter);
    return newReporter;
}

/***********************************************/
bool Reporter::openReporterFile(string path) 
/*
 * This function will open the products.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 * - Create the technovo directory if it doesn't exist
 * - If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
 * - Ensures the file is opened and we're at the start
 */
{
      // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists(path+"technovo/"))
    {
        std::filesystem::create_directory(path+"technovo/");
    }
    // Attempt to open the file
    file.open(path+"/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary);

    bool valid = file.is_open();
    if(!valid)
    {
        file.open(path+"/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }
    return valid && seekToBeginningOfFile();
}

/***********************************************/
bool Reporter::seekToBeginningOfFile()
/*
 * This function simply just seeks to the beggining of the file.
 *
 * Implementation Details:
 * - Assumes the file is already opened and valid.
 * - Throws an error if the file is not open.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Reporter file was not open when it was expected to be!\n";
        throw std::runtime_error("Reporter file not open on seekToBeginningOfFile");
    }
    file.seekg(0);
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Reporter::writeToFile(Reporter reporter) 
/*
 * This function will append a Product to the file
 * 
 * Implementation Details:
 * - Assumes the file is already opened and valid.
 * - Throws an error if the file is not open.
 * - Checks for any entity integrity violations; if found, returns false.
 * - Writes the entirety of the reporter to the file.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Reporter file was not open when it was expected to be!\n";
        throw std::runtime_error("Reporter file not open on writeToFile");
    }

    seekToBeginningOfFile();
    bool read = true;
    Reporter nextToCheck = readFromFile(read);
    while(!read)
    {
        if(strcmp(nextToCheck.email, reporter.email) == 0)
        {
            return false;
        }
        nextToCheck = readFromFile(read);
    }

    file.seekg(0, std::ios::end);
    file.write(reporter.email, sizeof(char) * EMAILDATASIZE);
    file.write(reporter.customerName, sizeof(char) * CUSTOMERNAMESIZE);
    file.write(reporter.phoneNumber, sizeof(char) * PHONENUMBERSIZE);
    file.write(reporter.deparmentId, sizeof(char) * DEPTIDSIZE);
    file.close();
    return !(file.fail() || file.bad());
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
    isEnd = false;

    Reporter toReturn;
    file.read(toReturn.email, sizeof(char) * EMAILDATASIZE);
    file.read(toReturn.customerName, sizeof(char) * CUSTOMERNAMESIZE);
    file.read(toReturn.phoneNumber, sizeof(char) * PHONENUMBERSIZE);
    file.read(toReturn.deparmentId, sizeof(char) * DEPTIDSIZE);
    return toReturn;
}


/***********************************************/
bool Reporter::closeReporterFile() 
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
        std::cout << "The Reporter file was not open when it was expected to be!\n";
        throw std::runtime_error("Reporter file not open on closeReporterFile");
    }
    file.close();
    return !(file.fail() || file.bad());
}


