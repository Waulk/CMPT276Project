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
using std::string;

class Report
{
    public:
        /***********************************************/
        Report();
        // Returns: None since this is a constructor
        /* This is a constructor of Report
        *  This constructor initializes email with nullptr

        /***********************************************/
        Report(
            string email,          // string email - a email assign the customer (in)
            string changeId,       // string changeId - the changeId of the report (in)
            string ReleasId,       // string ReleasId - the releaseId of the report (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Report
        *  This constructor initializes email, changeId, releaseId
        * ---------------------------------------------
        * Precondition: 
        * email != "" (empty string). The max length of productName is 10.
        * changeId != "" (empty string). The max length of releaseId is 7.
        * releaseId != "" (empty string). The max length of releaseId is 8. 
        * If these preconditions are not met, it will throw an exception with an error message

        /***********************************************/
        string getreport(
            const string &email,          // string email - a email assign the customer (in)
            const string &changeId,       // string changeId - the changeId of the report (in)
        );
        // Returns: string - email, changeid, releaseid and date of report
        /* This is a getter of report
        * ---------------------------------------------
        * Precondition: 
        * email != "" (empty string). The max length of productName is 10.
        * changeId != "" (empty string). The max length of releaseId is 7.
        * If these preconditions are not met, it will throw an exception with an error message

        /***********************************************/
        bool setReport(
            const string &email,          // string email - a email assign the customer (in)
            const string &changeId,       // string changeId - the changeId of the report (in)
            const string &ReleasId,       // string ReleasId - the releaseId of the report (in)
        );
        // Returns: True or False
        /* This add report to the data file
        * ---------------------------------------------
        * Precondition: 
        * email != "" (empty string). The max length of productName is 10.
        * changeId != "" (empty string). The max length of releaseId is 7.
        * releaseId != "" (empty string). The max length of releaseId is 8. 
        * If these preconditions are not met, it will throw an exception with an error message and will return False

        /***********************************************/
        

    private:
        bool checkreport(
            const string &email,          // string email - a email assign the customer (in)
            const string &changeId,       // string changeId - the changeId of the report (in)
        );
        // Returns: True or False
        /* This checks if a report is already in the data
        * ---------------------------------------------
        * Precondition: 
        * email != "" (empty string). The max length of productName is 10.
        * changeId != "" (empty string). The max length of releaseId is 7.
        * If these preconditions are not met, it will throw an exception with an error message and return False
        * 
        /***********************************************/
};

#endif