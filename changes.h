/***********************************************
 * Module: changes.h
 * 
 * Code Version History: 
 * Ver. 1: - 2024-07-01 Original by Matthew Liu
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Changes class provides description of a change.
 * You must call the constructor Changes() or Changes(int changeID, string changeStatus, ... bool isBug) before using this class.
***********************************************/

#ifndef Changes_H
#define Changes_H
#include <iostream>
using std::string;

class Changes
{
    public:
        /***********************************************/
        Changes();
        // Returns: None since this is a constructor
        /* This is a constructor of Changes
        *  This constructor initializes changeID with a nullptr

        /***********************************************/
        Changes(
            int changeID,  // int changeID - a number assigned to a change (in)
            string changeStatus, // string changeStatus - current status of the change (in)
            string productName, // string productName - 1-10 characters, name of the product (in)
            string release_id, // string release_id - current release id (in)
            int priority, // int priority - current priority level of the change (in)
            string description, // string description - a description of the bug/feature (in)
            bool isBug  // bool isBug - a boolean value that determines if the change is a bug or feature (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Changes
        *  This constructor initializes changeID, changeStatus, productName, release_id, priority, description, and isBug.
        * ---------------------------------------------
        * Precondition: 
        * changeID != "" (empty string). **********************************************The max value of changeID is 999999. ****************
        * If these preconditions are not met, it will throw an exception with an error message
       
        /***********************************************/
        int getchangeID();
        // Returns: int - changeID of the Change
        /* This is a getter of ChangeID

        /***********************************************/
        /***********************************************/
        string getchangeStatus();
        // Returns: string - changeStatus of the Change
        /* This is a getter of ChangeStatus

        /***********************************************/
        /***********************************************/
        string getProductName();
        // Returns: string - product name of the Change
        /* This is a getter of ProductName

        /***********************************************/
        /***********************************************/
        string getReleaseId();
        // Returns: string - release id of the Change
        /* This is a getter of ReleaseID

        /***********************************************/
        /***********************************************/
        int getPriority();
        // Returns: int - priority of the Change
        /* This is a getter of Priority

        /***********************************************/
        /***********************************************/
        string getDescription();
        // Returns: string - description of the Change
        /* This is a getter of description

        /***********************************************/
        /***********************************************/
        bool getIsBug();
        // Returns: bool - isBug of the Change
        /* This is a getter of isBug

        /***********************************************/

        /***********************************************/
        int setchangeID();
        // Returns: void
        /* This is a setter of ChangeID
        *  It assigns the parameter value to the changeID

        /***********************************************/
        /***********************************************/
        string setchangeStatus();
        // Returns: void
        /* This is a setter of ChangeStatus
        *  It assigns the parameter value to the ChangeStatus

        /***********************************************/
        /***********************************************/
        // Returns: void
        // Returns: string - product name of the Change
        /* This is a setter of ProductName
        *  It assigns the parameter value to the productName

        /***********************************************/
        /***********************************************/
        string setReleaseId();
        // Returns: void
        /* This is a setter of ReleaseID
        *  It assigns the parameter value to the ReleaseID

        /***********************************************/
        /***********************************************/
        int setPriority();
        // Returns: void
        /* This is a setter of Priority
        *  It assigns the parameter value to the Priority

        /***********************************************/
        /***********************************************/
        string setDescription();
        // Returns: void
        /* This is a setter of description
        *  It assigns the parameter value to the description

        /***********************************************/
        /***********************************************/
        bool setIsBug();
        // Returns: void
        /* This is a setter of isBug
        *  It assigns the parameter value to isBug

        /***********************************************/

        void setChangeID(
            const int &changeID  // string changeID - a name to assign the product (in)
        );
        // Returns: void
        /* This is a setter of changeID
         * It assigns the parameter value to the changeID
         * ---------------------------------------------
         * Precondition: changeID != "" (empty string). The max length of changeID is 999,999.
         * If this precondition is not met, it will display an error message and return the function 
         * WITHOUT assigning the parameter value to the changeID

        /***********************************************/
        string viewNewChangesUI();
        // Returns: string
        /* This function prints the UI for new changes.
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
        /***********************************************
        */
        string viewChangesFromProduct(
        // Returns: string
        /* This function prints the UI for the changes for a specific product.
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
        );

        string viewUnfinishedChanges(
        // returns: string
        /* This function prints the UI for the unfinished changes for release.
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


        );

        string viewCustomerRequestedChanges(
        // returns: string
        /* This functions prints the UI for all changes requested by a customer.
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

        );

       
    private:       
        static const int changeStatusSize = 10;
        static const int productNameSize = 10;
        static const int release_idSize = 8;
        static const int descriptionSize = 30;

        // int - ID of the change. Max/min size between 1-999,999.
        int changeID;       
        // int - priority level of the change. A number between 1 and 5.
        int priority; 

        // char[] - current status of the change. Can choose between New, Assessed, InProgress, Cancelled, and Done. Since InProgress has length 10, that is the maximum size of the char[].
        char changeStatus[changeStatusSize];

        // char[] - the name of the product associated with this change.
        char productName[productNameSize]; 

        // char[] - the release id associated with this change.
        char release_id[release_idSize]; 

        // char[] - a brief description of the bug or feature.
        char description[descriptionSize]; 

        //bool - true means the change is a bug, and false means that this change is a feature.
        bool isBug;  



};

#endif