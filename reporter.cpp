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
bool Reporter::checkEmail(const string &email) 
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
        return false;
    }

    seekToBeginningOfFile();
    bool isEnd = false;
    while (!isEnd) 
    {
        Reporter reporter = readFromFile(isEnd);
        if (!isEnd && strcmp(reporter.email, email.c_str()) == 0) 
        {
            return true;
        }
    }
    return false;
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
    std::cout << "Enter email: ";
    std::cin >> email;

    while (this->checkEmail(email)) 
    {
        std::cout << "Entered existing email\nEnter another email: ";
        std::cin >> email;
    }

    std::cout << "Enter name: ";
    std::cin >> customerName;
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;
    std::cout << "Do they work at the company? (yes/no): ";
    std::string worksAtCompany;
    std::cin >> worksAtCompany;
    if (worksAtCompany == "yes" || worksAtCompany == "Yes") 
    {
        std::cout << "Enter department: ";
        std::cin >> departmentId;
    } else 
    {
        departmentId = "";
    }

    Reporter newReporter(email, customerName, phoneNumber, departmentId);
    if (writeToFile(newReporter)) 
    {
        std::cout << "Reporter added successfully." << std::endl;
        return newReporter;
    } else 
    {
        std::cout << "Error occurred while adding Reporter." << std::endl;
        return Reporter(); 
    }
    
}

/***********************************************/
bool Reporter::openReporterFile() 
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
    if(!std::filesystem::exists("C:/Users/Anmol/Desktop/CMPT 276/technovo/"))
    {
        std::filesystem::create_directory("C:/Users/Anmol/Desktop/CMPT 276/technovo/");
    }
    
    file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();
    if(!valid)
    {
        file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
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


