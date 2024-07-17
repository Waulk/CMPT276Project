/***********************************************
 * Module: Reporter.h
 * 
 * Code Version History: 
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

        // Reporter UI in a stactic funcation
        /***********************************************/
        Reporter();
        // Returns: None since this is a constructor
        /* This is a constructor of Reporter
        *  This constructor initializes email with nullptr

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


        /***********************************************/
        bool checkEmail(
            const string &email     // string email - email of customer (in)
        );
        // Returns: True or Flase  
        /* This checks if email exists
        * ---------------------------------------------
        * Precondition: email != "" (empty string). The max length of email is 24.
        * If this precondition is not met, it will display an error message and the function will return False  
        

        /***********************************************/
        string getCustomerInfo(
            const string &email     // string email - email of customer (in)
        );
        // Returns: string - name and phone number of customer
        /* This is a getter of customer's information
        * ---------------------------------------------
        * Precondition: email != "" (empty string). The max length of email is 24.
        * If this precondition is not met, the function will display and return an error message  

        /***********************************************/
        bool setCustomer(
            Reporter reporter
        );
        // Returns: true or false
        /* This is a setter of customer
         * It adds the customer to the data file
         * ---------------------------------------------
         * Precondition: 
        * email != "" (empty string). The max length of email is 24.
        * customerName != "" (empty string). The max length of customerName is 30.
        * phoneNumber != "" (empty string). The max length of phoneNumber is 11.
        * The max length of deparmentId is 12. 
        * If these preconditions are not met, it will throw an exception with an error message
        
        /***********************************************/
        void reporterUI(
            bool createNew // Ture or False
        );
        // Returns: void
        /* This function dispalys an UI and shows a list of all the customers

        /***********************************************/

       bool openReporterFile();
       // Returns: true or flase
        /* This function opens the file 
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       bool writeToFile(
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
       void reporterFileStart();
       // Returns: void
        /* This function points to the top of the file
         * ---------------------------------------------
         * Precondition: The file is opened
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       bool closeReporterFile();
       // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file to get closed exists
         * If this precondition is not met, it will display an error message and throw an exception
        */
              

    private:
        // char[] - email address. Fixed length (Fixed Length: 24 chars)
        char email[EMAILDATASIZE];

        // char[] - the customers name. Fixed length (Fixed Length: 30 chars)
        char customerName[CUSTOMERNAMESIZE];

        // char[] - the phone number. Fixed length (Fixed Length: 11 chars)
        char phoneNumber[PHONENUMBERSIZE]; 

        // char[] - the department name. Fixed length (Fixed Length: 12 chars)
        char deparmentId[DEPTIDSIZE]; 

        // fstream - File to save Report objects
        static std::fstream file;

};

#endif


