/***********************************************
 * Module: changes.h
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-17 Edited by Matthew Liu
 *         - added additional comments
 *         - added parameters to UI methods
 *         - changed return types to Changes from string
 * Ver. 1: - 2024-07-01 Original by Matthew Liu
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Changes class provides description of a change.
 * You must call the constructor Changes() or Changes(int changeId, string changeStatus, ... bool isBug) before using this class.
***********************************************/

#ifndef Changes_H
#define Changes_H
#include <iostream>
#include <vector>
using std::string;

class Changes
{
    public:        
        // size of the change status
        static const int CHANGESTATUSSIZE = 10;
        // size of product name
        static const int PRODUCTNAMESIZE = 10;
        // size of release Id
        static const int RELEASE_IdSIZE = 8;
        // size of description size
        static const int DESCRIPTIONSIZE = 30;


        /***********************************************/        

        Changes();
        // Returns: None since this is a constructor
        /* This is a constructor of Changes
        *  This constructor initializes changeId with a nullptr

        /***********************************************/
        Changes(
            int changeId,  // int changeId - a number assigned to a change (in)
            string changeStatus, // string changeStatus - current status of the change (in)
            string productName, // string productName - 1-10 characters, name of the product (in)
            string release_Id, // string release_Id - current release Id (in)
            int priority, // int priority - current priority level of the change (in)
            string description, // string description - a description of the bug/feature (in)
            bool isBug  // bool isBug - a boolean value that determines if the change is a bug or feature (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Changes
        *  This constructor initializes changeId, changeStatus, productName, release_Id, priority, description, and isBug.
        * ---------------------------------------------
        * Precondition: 
        * changeId != "" (empty string). **********************************************The max value of changeId is 999999. ****************
        * If these preconditions are not met, it will throw an exception with an error message
       
        /***********************************************/
        int getchangeId();
        // Returns: int - changeId of the Change
        /* This is a getter of ChangeId

        /***********************************************/
        string getchangeStatus();
        // Returns: string - changeStatus of the Change
        /* This is a getter of ChangeStatus

        /***********************************************/
        string getProductName();
        // Returns: string - product name of the Change
        /* This is a getter of ProductName

        /***********************************************/
        string getReleaseId();
        // Returns: string - release Id of the Change
        /* This is a getter of ReleaseId

        /***********************************************/
        int getPriority();
        // Returns: int - priority of the Change
        /* This is a getter of Priority

        /***********************************************/
        string getDescription();
        // Returns: string - description of the Change
        /* This is a getter of description

        /***********************************************/
        bool getIsBug();
        // Returns: bool - isBug of the Change
        /* This is a getter of isBug

        /***********************************************/
        int setchangeId(
            const int &changeId
        );
        // Returns: voId
        /* This is a setter of ChangeId
        *  It assigns the parameter value to the changeId

        /***********************************************/
        void setchangeStatus(
            const string &changeStatus
        );
        // Returns: voId
        /* This is a setter of ChangeStatus
        *  It assigns the parameter value to the ChangeStatus

        /***********************************************/
        void setProductName(
            const string &productName
        );
        // Returns: voId
        // Returns: string - product name of the Change
        /* This is a setter of ProductName
        *  It assigns the parameter value to the productName

        /***********************************************/
        void setReleaseId(
            const string &releaseId
        );
        // Returns: voId
        /* This is a setter of ReleaseId
        *  It assigns the parameter value to the ReleaseId

        /***********************************************/
        void setPriority(
            const int &priority
        );
        // Returns: voId
        /* This is a setter of Priority
        *  It assigns the parameter value to the Priority
        
        /***********************************************/
        void setDescription(
            const string &description
        );
        // Returns: voId
        /* This is a setter of description
        *  It assigns the parameter value to the description

        /***********************************************/
        void setIsBug(
            const bool &isBug
        );
        // Returns: voId
        /* This is a setter of isBug
        *  It assigns the parameter value to isBug

        /***********************************************/

        void setChangeId(
            const int &changeId  // string changeId - a name to assign the product (in)
        );
        // Returns: voId
        /* This is a setter of changeId
         * It assigns the parameter value to the changeId
         * ---------------------------------------------
         * Precondition: changeId != "" (empty string). The max length of changeId is 999,999.
         * If this precondition is not met, it will display an error message and return the function 
         * WITHOUT assigning the parameter value to the changeId

        /***********************************************/

        Changes viewNewChangesUI();
        // Returns: Changes
        /* This function returns a Changes object.
        /*
        =======Changes=======
        SELECTION  STATUS      PRIORITY  DESCRIPTION                     BUG
        ---------  ------      --------  -----------                     ---                    
            1)  xxxxxxxxxx      d         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  T/F
            2)  InProgress      3         There is no sea                 T
            ...
            19)  Assessed       5         Submission crashes site         T
            20)  Done           4         App should save                 F
                                <-P X N->
        Make a Selection:
        */
        /***********************************************/

        bool isValid();
        // Returns: True if the Change is valid and was created properly, False otherwise.
        /* This method determines if a generated Change selection from the change functions such as viewChangesFromProduct or viewUnfinishedChanges is valId.
        */

        /***********************************************/

        Changes viewChangesFromProduct(const string &product);
        // Returns: Changes
        /* This function returns a Changes object.
        =======Changes=======
        SELECTION  STATUS      PRIORITY  DESCRIPTION                     BUG
        ---------  ------      --------  -----------                     ---                    
            1)  xxxxxxxxxx      d         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  T/F
            2)  InProgress      3         There is no sea                 T
            ...
            19)  Assessed       5         Submission crashes site         T
            20)  Done           4         App should save                 F
                                <-P  N->
        Make a Selection:

        */

        /***********************************************/

        Changes viewUnfinishedChanges(const string &productRelease, const string &product);
        // Returns: Changes
        /* This function returns a Changes object.
        =======Changes=======
        STATUS      PRIORITY  DESCRIPTION                     BUG
        ------      --------  -----------                     ---                    
        xxxxxxxxxx  d         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  T/F
        InProgress  3         There is no sea                 T
            ...
        Assessed    5         Submission crashes site         T
        InProgress  4         App should save                 F
                               <-P  N->
        Next or Previous?
        */

        /***********************************************/

        Changes viewCustomerRequestedChanges(const string &product);
        // Returns: Changes
        /* This function returns a Changes object.
        =======Changes=======
        SELECTION  STATUS      PRIORITY  DESCRIPTION                     BUG
        ---------  ------      --------  -----------                     ---                    
            1)  xxxxxxxxxx      d         xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  T/F
            2)  InProgress      3         There is no sea                 T
            ...
            19)  Assessed       5         Submission crashes site         T
            20)  Done           4         App should save                 F
                                <-P  N->
        Make a Selection:
        */

        /***********************************************/

        static Changes readFromFile(
            bool &isEnd    // bool &notEnd - indicates whether it has reached to the end of the file. True if it has reached the end, false otherwise (out)
        );
        // Returns: Changes - the Changes from the file
        /* This function read and return the Change from the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
        static bool writeToFile(
            Changes change     // Change to add to the file (in)
        );
        // Returns: bool - return true if writing to the file succeed, false otherwise
        /* This function write a Change to the file
         * ---------------------------------------------
         * Precondition: file is properly open
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
       static bool openChangesFile();
       // Returns: bool - return true if the file got opened successfully, false otherwise
        /* This function opens the file
         * ---------------------------------------------
         * Precondition: The file to get opened exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool closeChangesFile();
       // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file to get closed exists
         * If this precondition is not met, it will display an error message and throw an exception
        */
       static bool ChangesExists(Changes change);
       // Returns: bool - return true if the instance/object exists, false otherwise
        /* This function checks if an object exists in the file
         * ---------------------------------------------
         * Precondition: The file to get checked exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       
    private:       

        // int - Id of the change. Max/min size between 1-999,999.
        int changeId;

        // int - priority level of the change. A number between 1 and 5.
        int priority; 

        // char[] - current status of the change. Can choose between New, Assessed, InProgress, Cancelled, and Done. Since InProgress has length 10, that is the maximum size of the char[].
        char changeStatus[CHANGESTATUSSIZE];

        // char[] - the name of the product associated with this change.
        char productName[PRODUCTNAMESIZE]; 

        // char[] - the release Id associated with this change.
        char release_Id[RELEASE_IdSIZE]; 

        // char[] - a brief description of the bug or feature.
        char description[DESCRIPTIONSIZE]; 

        //bool - true means the change is a bug, and false means that this change is a feature.
        bool isBug;  

        static int lastChangeId;



};

#endif
