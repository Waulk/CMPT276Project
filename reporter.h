/***********************************************
 * Module: Reporter.h
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-17 by Anmol Sangha 
 *         - Edited function prototypes 
 *         - Increased array sizes by 1 for null terminator
 * Ver. 1: - 2024-06-30 by Anmol Sangha 
 *         - Initial version 
 ***********************************************/

/***********************************************
 * You must call the constructor Reporter() or Reporter(char *email, char *customerName, char *phoneNumber) before you can use this class.
***********************************************/

#ifndef Reporter_H
#define Reporter_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
using std::string;

class Reporter
{
    public:
        // size of email address
        static const int EMAILDATASIZE = 24;
        // size of customers name 
        static const int CUSTOMERNAMESIZE = 30;
        // size of phone number
        static const int PHONENUMBERSIZE = 11;
        // size of department id
        static const int DEPTIDSIZE = 12;

        /***********************************************/
        Reporter();
        // Returns: None since this is a constructor
        /* This is a constructor of Reporter
        *  This constructor initializes email with nullptr
        */

        /***********************************************/
        Reporter(
            string email,           // string email - a email associated with the customer (in)
            string customerName,     // string customerName - name of the customer (in)
            string phoneNumber,       // string phoneNumber - a phone number associated with the customer (in)
            string deparmentId = ""   // string deparmentId - the name of the deparment the customer works for (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Reporter
        *  This constructor initializes email, customerName, phoneNumber and departmentId
        * ---------------------------------------------
        * Precondition: 
        * email != "" (empty string). The max length of email is 24.
        * customerName != "" (empty string). The max length of customerName is 30.
        * phoneNumber != "" (empty string). The max length of phoneNumber is 11.
        * The max length of deparmentId is 12. 
        * If these preconditions are not met, it will throw an exception with an error message
        */

        /***********************************************/
        string getEmail();
        // Returns: string - email of the Reporter
        /* This is a getter of email
        */

       /***********************************************/
        string getCustomerName();
        // Returns: string - name of the Reporter
        /* This is a getter of customerName
        */

       /***********************************************/
        string getPhoneNumber();
        // Returns: string - phone number of the Reporter
        /* This is a getter of phoneNumber
        */

       /***********************************************/
        string getDepartmentId();
        // Returns: string - department of the Reporter
        /* This is a getter of departmentId
        */
        
        /***********************************************/
        static Reporter reporterUI();
        // Returns: void
        /* This function displays an UI and shows a list of all the customers*/


        /***********************************************/
        static bool seekToBeginningOfFile();
        // Returns: bool - return true if reached to the beginning of file successfully, false otherwise
        /* This function rewinds to the beginning of the file 
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

        /***********************************************/
        static bool openReporterFile(
            string path     // path for the new technovo/reporters.bin file
       );
        // Returns: true or flase
        /* This function opens the file 
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool writeToFile(
        Reporter reporter      // Reporter reporter - the the info that need to be added to end of file (out)
       );
       // Returns: bool - return true if the file opened and had the string successfully add to it, false otherwise
        /* This function open and write in the file
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

        /***********************************************/
        static Reporter readFromFile(
            bool &isEnd    // bool &notEnd - indicates whether it has reached to the end of the file. True if it has reached the end, false otherwise (out)
        );
        // Returns: Reporter - the reporter from the file
        /* This function read and return the Product from the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

        /***********************************************/
        static bool closeReporterFile();
        // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file to get closed exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

    private:

        /***********************************************/
        static Reporter checkEmail(
            const string &email     // string email - email of customer (in)
        );
        // Returns: The found Reporter, or an empty reporter 
        /* This checks if email exists
        * ---------------------------------------------
        * Precondition: email != "" (empty string). The max length of email is 24.
        * If this precondition is not met, it will display an error message and the function will return False  
        */
       /***********************************************/

        // char[] - email address. Fixed length (Fixed Length: 24 chars)
        char email[EMAILDATASIZE + 1];

        // char[] - the customers name. Fixed length (Fixed Length: 30 chars)
        char customerName[CUSTOMERNAMESIZE + 1];

        // char[] - the phone number. Fixed length (Fixed Length: 11 chars)
        char phoneNumber[PHONENUMBERSIZE + 1]; 

        // char[] - the department name. Fixed length (Fixed Length: 12 chars)
        char deparmentId[DEPTIDSIZE + 1]; 

        // fstream - File to save Report objects
        inline static std::fstream file;

};

#endif