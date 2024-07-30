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
void Report::getReportUI() {
        const int REPORTS_PER_PAGE = 20;
        bool isEnd = false;
        bool exit = false;
        int currentPage = 0;

        while (!exit) {
            seekToBeginningOfFile();

            // Skip reports of previous pages
            for (int i = 0; i < currentPage * REPORTS_PER_PAGE; ++i) {
                bool read = true;
                readFromFile(read);
                if (!read) {
                    currentPage--;
                    break;
                }
            }

            // Display the reports
            std::cout << "=======Reports=======\n";
            std::cout << "SELECTION  REPORTS\n";
            std::cout << "---------------------\n";

            for (int i = 0; i < REPORTS_PER_PAGE; ++i) {
                bool read = true;
                Report report = readFromFile(read);
                if (!read) {
                    isEnd = true;
                    break;
                }
                std::cout << i + 1 << " " << report.email << " " << report.changeId << "\n";
                // Display other report fields as needed
            }

            std::cout << "            <-P   N->\n";
            std::cout << "Make a Selection: ";

            std::string input;
            std::cin >> input;

            if (input == "P" || input == "p") {
                if (currentPage > 0) {
                    currentPage--;
                }
            } else if (input == "N" || input == "n") {
                if (!isEnd) {
                    currentPage++;
                }
            } else {
                int selection = std::stoi(input);
                if (selection > 0 && selection <= REPORTS_PER_PAGE) {
                    seekToBeginningOfFile();
                    for (int i = 0; i < currentPage * REPORTS_PER_PAGE + selection - 1; ++i) {
                        bool read = true;
                        readFromFile(read);
                    }

                    bool read = true;
                    Report selectedReport = readFromFile(read);
                    // Handle the selected report as needed
                    std::cout << "Selected Report: " << selectedReport.email << " " << selectedReport.changeId << "\n";
                    // Display other report fields as needed
                    return;
                } else {
                    throw std::out_of_range("Invalid selection number.");
                }
            }
        }
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
bool Report::openReportFile() 
/*
 * This function will open the reports.bin file and will return false on failure
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
    file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();
    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open("C:/Users/Anmol/Desktop/CMPT 276/technovo/reports.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
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

int main() {
    // Seed for random number generation
    srand(static_cast<unsigned>(time(0)));

    std::cout<<"HEloo" <<endl;
    Report reportSystem = Report();
    reportSystem.openReportFile();
    
    
     //Close the report file
    if (!reportSystem.closeReportFile()) {
        cerr << "Failed to close report file!" << endl;
        return 1;
    }

    return 0;
}