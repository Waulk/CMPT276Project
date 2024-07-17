/***********************************************
 * Module: Report.h
 * 
 * Code Version History: 
 * Ver. 1: - 2024-06-30 Original by Anmol Sangha
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Report class provides the name of the product.
 * You must call the constructor Report() or Report(string email, string changeId, releaseId) before you can use this class.
***********************************************/

#ifndef Report_H
#define Report_H
#include <iostream>
#include <ctime>
#include <fstream>
using std::string;

class Report
{
    public:
        // size of email address
        static const int EMAILDATASIZE = 24;
        // size of releaseId
        static const int IDSIZE = 8;

        /***********************************************/
        Report();
        // Returns: None since this is a constructor
        /* This is a constructor of Report
         *  This constructor initializes email with nullptr
        */

        /***********************************************/
        Report(
            string email,          // string email - a email assign the customer (in)
            int changeId,          // int changeId - the changeId of the report (in)
            string ReleasId        // string ReleasId - the releaseId of the report (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Report
         *  This constructor initializes email, changeId, releaseId
         * ---------------------------------------------
         * Precondition: 
         * email != "" (empty string). The max length of productName is 24.
         * releaseId != "" (empty string). The max length of releaseId is 8. 
         * If these preconditions are not met, it will throw an exception with an error message
        */

        /***********************************************/
        Report getReport(
            const string &email,          // string email - a email assign the customer (in)
            const int &changeId           // int changeId - the changeId of the report (in)
        );
        // Returns: string - email, changeid, releaseid and date of report
        /* This is a getter of report
         * ---------------------------------------------
         * Precondition: 
         * email != "" (empty string). The max length of productName is 10.
         * changeId != "" (empty string). The max length of releaseId is 7.
         * If these preconditions are not met, it will throw an exception with an error message
        */

        /***********************************************/
        static bool openReportFile();
       // Returns: True or False
        /* This function opens the file
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool writeToFile(
        Report report      // Report report - the the info that need to be added to end of file (out)
       );
       // Returns: bool - return true if the file opened and had the string successfully add to it, false otherwise
        /* This function open and write in the file
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool seekToBeginningOfFile();
        // Returns: bool - return true if reached to the beginning of file successfully, false otherwise
        /* This function rewinds to the beginning of the file 
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
        static Report readFromFile(
            bool &isEnd    // bool &notEnd - indicates whether it has reached to the end of the file. True if it has reached the end, false otherwise (out)
        );
        // Returns: Report - the report from the file
        /* This function read and return the Product from the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

        /***********************************************/
        bool checkreport(
            const string &email,          // string email - a email assign the customer (in)
            const int &changeId           // int changeId - the changeId of the report (in)
        );
        // Returns: True or False
        /* This checks if a report is already in the data
         * ---------------------------------------------
         * Precondition: 
         * email != "" (empty string). The max length of productName is 10.
         * If these preconditions are not met, it will throw an exception with an error message and return False
        */
      
        /***********************************************/
        static bool closeReportFile();
       // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file to get closed exists
         * If this precondition is not met, it will display an error message and throw an exception
        */
        /***********************************************/
    private:
       

        // char[] - email address. Fixed length (Fixed Length: 24 chars)
        char email[EMAILDATASIZE];

        // char[] - the ID of the release version. Fixed length (Fixed Length: 8 chars)
        char releaseId[IDSIZE];

        // int - the change Id. Fixed length (Max Value: 999,999)
        int changeId; 

        // fstream - File to save Report objects
        static std::fstream file;
};

#endif
