/***********************************************
 * Module: Report.cpp
 * 
 * Code Version History: 
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
    this->email[EMAILDATASIZE] = '\0'; // Ensure null termination
    this->changeId = changeId;

    strncpy(this->releaseId, releaseId.c_str(), IDSIZE);
    this->releaseId[IDSIZE] = '\0'; // Ensure null termination
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
    if (email.empty() || email.length() > EMAILDATASIZE + 1) 
    {
        throw std::invalid_argument("Invalid argument length");
    }

    seekToBeginningOfFile();
    string line;
    bool read = true;
    Report nextToCheck = readFromFile(read);

    // Check to see if any change in the system matches our current change
    while(read)
    {
        if(nextToCheck.email == email && nextToCheck.changeId == changeId)
            return nextToCheck;
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
bool Report::openReportFile() 
/*
 * This function will open the reports.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 */
{
    // Attempt to open the file
    file.open("/etc/technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();

    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("/etc/technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    // Make sure the file opened and we're at the start
    return valid && seekToBeginningOfFile();
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
    
    // Seek to the end of the file
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
bool Report::checkreport(const string &email, const int &changeId) 
{
    if (email.empty() || email.length() > EMAILDATASIZE - 1) {
        throw std::invalid_argument("Invalid argument length");
        return false;
    }

    return (this->email == email && this->changeId == changeId);
}

