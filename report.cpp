/***********************************************
 * Module: Report.cpp
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-30 Updated by Anmol Sangha
 *         - Updated function prototypes
 *         - Converted changeId to use an int instead of an array
 * Ver. 1: - 2024-06-30 Original by Anmol Sangha
 *         - Initial version 
 ***********************************************/

/***********************************************
 * report.cpp
 * This file implements the member functions defined in the product.h header file.
 * All data members are stored linearly unsorted in the file for ease of access.
***********************************************/

#include "report.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream> 
#include <filesystem>
using namespace std;

/***********************************************/
Report::Report() 
/*
 * Default constructor that initializes the member variables
 *
 * Implementation Details:
 * uses memset to set all characters in the members to null
*/
{
    memset(email, '\0', EMAILDATASIZE + 1);
    changeId = 0;
    memset(releaseId, '\0', IDSIZE + 1);
}

/***********************************************/
Report::Report(string email, int changeId, string releaseId) 
/*
 * Constructor that initializes member variables with values
 *
 * Implementation Details:
 * Checks each string to insure valid input (not empty and not longer than fixed size)
 * Uses strncpy to copy strings to arrays and ensures null termination
*/
{
    if (email.empty() || email.length() > EMAILDATASIZE + 1 ||
        releaseId.empty() || releaseId.length() > IDSIZE + 1) 
        {
        throw std::invalid_argument("Invalid argument length");
        }

    strncpy(this->email, email.c_str(), EMAILDATASIZE);
    this->email[EMAILDATASIZE] = '\0'; 
    this->changeId = changeId;

    strncpy(this->releaseId, releaseId.c_str(), IDSIZE);
    this->releaseId[IDSIZE] = '\0'; 
}

/***********************************************/
Report Report::getReport(const string &email, const int &changeId) 
/*
 * Uses the email and changeid to find and get all the information about the report
 *
 * Implementation Details:
 * Checks each string to insure valid input (not empty and not longer than fixed size)
 * goes through the file and finds the matching email and change id 
 * reutrn the information or if not found returns an error message 
*/
{
    if (!checkReport(email, changeId)) {
        throw std::runtime_error("Report not found");
    }

    seekToBeginningOfFile();
    bool read = true;
    Report nextToCheck = readFromFile(read);

    while (read) {
        if (nextToCheck.email == email && nextToCheck.changeId == changeId) {
            return nextToCheck;
        }
        nextToCheck = readFromFile(read);
    }

    return Report(); 
}

/***********************************************/
Report Report::readFromFile(bool &isEnd)
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
        return Report();
    }
    isEnd = false;

    // Read the next file if it's not EOF, this will move the seek
    Report toReturn;
    file.read(toReturn.email, sizeof(char) * EMAILDATASIZE);
    file.read((char*)&toReturn.changeId, sizeof(int));
    file.read(toReturn.releaseId, sizeof(char) * IDSIZE);
    return toReturn;
}

/***********************************************/
bool Report::seekToBeginningOfFile()
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
        std::cout << "The Report file was not open when it was expected to be!\n";
        throw std::runtime_error("Report file not open on seekToBeginningOfFile");
    }
    file.seekg(0);
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Report::openReportFile(string path) 
/*
 * This function will open the reports.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file is opened with read and write capabilities, in binary mode.
 * - Creates the technovo directory if it doesn't exist.
 * - If the file fails to open, tries again with the trunc flag (creates a new file if none exists).
 * - Ensures the file is opened and we're at the start.
 */
{
    // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists(path+"technovo/"))
    {
        std::filesystem::create_directory(path+"technovo/");
    }

    // Attempt to open the file
    file.open(path+"technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();
    if(!valid)
    {
        file.open(path+"technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    return valid && seekToBeginningOfFile();
}

/***********************************************/
string Report::getEmail()
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
string Report::getReleaseId()
/*
 * Function to get the releaseId as a string.
 * 
 * Implementation Details:
 * - Constructs a string from the fixed-size character array.
*/
{
    return string(this->releaseId);
}

/***********************************************/
int Report::getChangeId()
/*
 * Function to get the changeId;
*/
{
    return this->changeId;
}

/***********************************************/
bool Report::writeToFile(Report report)
/*
 * This function will append a Report to the file
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This function will NOT check for any entity integrity violations
 */ 
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Report file was not open when it was expected to be!\n";
        throw std::runtime_error("Report file not open on writeToFile");
    }
    
    file.seekg(0, std::ios::end);
    file.write(report.email, sizeof(char) * EMAILDATASIZE);
    file.write((char*)&report.changeId, sizeof(int));
    file.write(report.releaseId, sizeof(char) * IDSIZE);
    
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Report::closeReportFile() 
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
        std::cout << "The Reports file was not open when it was expected to be!\n";
        throw std::runtime_error("Reports file not open on closeReportFile");
    }
    file.close();
    return !(file.fail() || file.bad());
}

/***********************************************/
bool Report::checkReport(const string &email, const int &changeId) 
{
    if (email.empty() || email.length() > EMAILDATASIZE + 1) {
        throw std::invalid_argument("Invalid argument length");
    }
   seekToBeginningOfFile();
    bool read = true;
    Report nextToCheck = readFromFile(read);

    while (read) {
        if (nextToCheck.email == email && nextToCheck.changeId == changeId) {
            return true;
        }
        nextToCheck = readFromFile(read);
    }
    return false;
}

