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
***********************************************/

#include "Report.h"
#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream> 
std::fstream Report::file;

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
    memset(changeId, '\0', CHANGEIDSIZE + 1);
    memset(releaseId, '\0', IDSIZE + 1);
}

/***********************************************/
Report::Report(string email, string changeId, string releaseId) 
/*
 * Constructor that initializes member variables with values
 *
 * Implementation Details:
 * Checks each string to insure valid input (not empty and not longer than fixed size)
 * Uses strncpy to copy strings to arrays and ensures null termination
*/
{
    if (email.empty() || email.length() > EMAILDATASIZE + 1 ||
        changeId.empty() || changeId.length() > CHANGEIDSIZE + 1 ||
        releaseId.empty() || releaseId.length() > IDSIZE + 1) 
        {
        throw std::invalid_argument("Invalid argument length");
        }

    strncpy(this->email, email.c_str(), EMAILDATASIZE);
    this->email[EMAILDATASIZE] = '\0'; // Ensure null termination

    strncpy(this->changeId, changeId.c_str(), CHANGEIDSIZE);
    this->changeId[CHANGEIDSIZE] = '\0'; // Ensure null termination

    strncpy(this->releaseId, releaseId.c_str(), IDSIZE);
    this->releaseId[IDSIZE] = '\0'; // Ensure null termination
}

/***********************************************/
string Report::getreport(const string &email, const string &changeId) 
/*
 * Uses the email and changeid to find and get all the information about the report
 *
 * Implementation Details:
 * Checks each string to insure valid input (not empty and not longer than fixed size)
 * goes through the file and finds the matching email and change id 
 * reutrn the informaation or if not found returns an error message 
*/
{
    if (email.empty() || email.length() > EMAILDATASIZE + 1 ||
        changeId.empty() || changeId.length() > CHANGEIDSIZE + 1) 
    {
        throw std::invalid_argument("Invalid argument length");
    }

    reportFileStart();
    string line;
    while (getline(file, line)) {
        string storedEmail = line.substr(0, EMAILDATASIZE);
        string storedChangeId = line.substr(EMAILDATASIZE + 1, CHANGEIDSIZE);
        storedChangeId.erase(storedChangeId.find_last_not_of(" \n\r\t")+1);

        if (storedEmail == email && storedChangeId == changeId) {
            return line;
        }
    }
   
    return "Report not found"; 
}

/***********************************************/
bool Report::setReport(Report report) 
/*
 * Adds new report to the data file
 *
 * Implementation Details:
 * Makes all the information in to a string
 * adds the information, sends error message if an error ouccurs
*/ 
{
    reportFileStart();
    std::stringstream ss;
    ss << report->email << " " << report->changeId << " " << report->releaseId;
    string combinedString = ss.str();
    if (!openReportFileAndWrite(combinedString)) 
    {
        std::cerr << "Failed to write to file" << std::endl;
        return false;
    }
    return true;
}

/***********************************************/
void Report::reportFileStart() 
{
    return;
}

bool Report::openReportFile() 
{
    return true;
}

/***********************************************/
bool Report::openReportFileAndWrite(string &addToFile) 
{
    return true;
}

/***********************************************/
bool Report::closeReportFile() 
{
   return true;
}

/***********************************************/
bool Report::checkreport(const string &email, const string &changeId) 
{
    if (email.empty() || email.length() > EMAILDATASIZE - 1 ||
        changeId.empty() || changeId.length() > CHANGEIDSIZE - 1) {
        throw std::invalid_argument("Invalid argument length");
        return false;
    }

    return (this->email == email && this->changeId == changeId);
}
