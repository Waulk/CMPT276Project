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

    this->email[EMAILDATASIZE] = '\0';
    this->customerName[CUSTOMERNAMESIZE] = '\0';
    this->phoneNumber[PHONENUMBERSIZE] = '\0';
    this->deparmentId[DEPTIDSIZE] = '\0';
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
std::string Reporter::getEmail()
// Simple getter that returns the email as a string
{
    return std::string(this->email);
}

/***********************************************/
void Reporter::reporterUI(bool createNew)
/*
 * This function interacts with the user to display a list of reporters and 
 * allows the user to navigate through pages. If createNew is true, the user 
 * has the option to create a new reporter.
 * 
 * Implementation Details:
 * - Initializes control variables for pagination and user input handling.
 * - Uses a while loop to continuously interact with the user until they exit.
 * - Seeks to the beginning of the file and skips reporters from previous pages 
 *   to display the current page's reporters.
 * - Displays the reporters for the current page and handles user input for 
 *   pagination or creation.
 */
{
    const int REPORTERS_PER_PAGE = 20;
    bool exit = false;
    int currentPage = 0;

    while (!exit) {
        seekToBeginningOfFile();
        bool isEnd = false;

        // Skip reporters of previous pages
        for (int i = 0; i < currentPage * REPORTERS_PER_PAGE && !isEnd; ++i) {
            readFromFile(isEnd); // Read and discard a reporter to skip it
        }

        if (isEnd) {
            std::cout << "No more reporters to display." << std::endl;
            if (currentPage > 0) {
                --currentPage;
            }
            continue;
        }

        // Display the reporters
        std::cout << "======= Reporter =======\n";
        std::cout << "SELECTION  REPORTERS\n";
        std::cout << "---------------------\n";

        for (int i = 0; i < REPORTERS_PER_PAGE && !isEnd; ++i) {
            Reporter reporter = readFromFile(isEnd); // Read a reporter from the file
            if (!isEnd) { // Check if end of file was not reached
                std::cout << (i + 1) << " " << reporter.email << " " 
                          << reporter.customerName << " " 
                          << reporter.phoneNumber << " " 
                          << reporter.deparmentId << "\n"; // Display reporter with its selection number
            }
        }

        // Display navigation options based on whether creating new reporter is allowed
        if (createNew) {
            std::cout << "            <-P X N->\n"; // Allow navigating previous/next page or creating new reporter
        } else {
            std::cout << "            <-P   N->\n"; // Allow navigating previous/next page only
        }
        
        std::cout << "Make a Selection: ";

        // Get user input
        std::string input;
        std::cin >> input; // Read user input

        if (input == "P" || input == "p") { // If user wants to go to the previous page
            if (currentPage > 0) { // Ensure it's not the first page
                --currentPage; // Move to the previous page
            }
        } else if (input == "N" || input == "n") { // If user wants to go to the next page
            if (!isEnd) { // Ensure it's not the end of the file
                ++currentPage; // Move to the next page
            }
        } else if (createNew && (input == "X" || input == "x")) { // If user wants to create a new reporter
            exit = true; // Set exit flag to true
        } else {
            std::cerr << "Invalid selection. Please try again." << std::endl;
        }
    }
}

/***********************************************/
bool Reporter::openReporterFile() 
/*
 * This function will open the products.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 */
{
      // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists("C:/Users/Anmol/Desktop/CMPT 276/technovo/"))
    {
        std::filesystem::create_directory("C:/Users/Anmol/Desktop/CMPT 276/technovo/");
    }
    // Attempt to open the file
    file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();
    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reporters.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    // Make sure the file opened and we're at the start
    return valid && seekToBeginningOfFile();
}

/***********************************************/
bool Reporter::seekToBeginningOfFile()
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
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This function will check for any entity integrity violations, if there is one it will return false.
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
    // Check if the reporter already exists in the file
    // If they do return false
    while(!read)
    {
        if(strcmp(nextToCheck.email, reporter.email) == 0)
        {
            return false;
        }
        nextToCheck = readFromFile(read);
    }

    // Write the entirety of the reporter to the file
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


void Reporter::addNewReporter(const std::string& email, const std::string& customerName, 
                        const std::string& phoneNumber, const std::string& deparmentId) {
   Reporter newReporter;
        strncpy(newReporter.email, email.c_str(), sizeof(newReporter.email) - 1);
        newReporter.email[sizeof(newReporter.email) - 1] = '\0';
        
        strncpy(newReporter.customerName, customerName.c_str(), sizeof(newReporter.customerName) - 1);
        newReporter.customerName[sizeof(newReporter.customerName) - 1] = '\0';
        
        strncpy(newReporter.phoneNumber, phoneNumber.c_str(), sizeof(newReporter.phoneNumber) - 1);
        newReporter.phoneNumber[sizeof(newReporter.phoneNumber) - 1] = '\0';
        
        strncpy(newReporter.deparmentId, deparmentId.c_str(), sizeof(newReporter.deparmentId) - 1);
        newReporter.deparmentId[sizeof(newReporter.deparmentId) - 1] = '\0';

        writeToFile(newReporter);
    }
std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[rand() % characters.length()];
    }
    return randomString;
}
int main(){
    srand(static_cast<unsigned>(time(0))); // Seed for random number generator

    Reporter rr;
    rr.openReporterFile();

    // Generate 55 random reporters
    for (int i = 0; i < 55; ++i) {
        std::string email = "user" + std::to_string(i) + "@" + generateRandomString(5) + ".com";
        std::string customerName = "Name" + std::to_string(i);
        std::string phoneNumber = "555-" + std::to_string(rand() % 9000 + 1000) + "-" + std::to_string(rand() % 9000 + 1000);
        std::string deparmentId = (rand() % 2 == 0) ? "Dept" + std::to_string(rand() % 10 + 1) : ""; // Randomly assign department or leave it empty

        rr.addNewReporter(email, customerName, phoneNumber, deparmentId);
    }

    rr.reporterUI(true); // Pass true to allow creating new reporters
    rr.closeReporterFile();
    return 0;
}

