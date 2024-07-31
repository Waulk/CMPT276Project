/***********************************************
 * Module: changes.cpp
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-30 Modified by Matthew Liu
             Added additional comments to improve readability
 * Ver. 1: - 2024-07-17 Original by Matthew Liu
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Changes class provides description of a change. The Changes class holds all the records of requested bug and feature changes in the system.
 * You must call the constructor Changes() or Changes(int changeId, string changeStatus, ... bool isBug) before using this class.
 * All data members are stored linearly unsorted in the file for ease of access.
***********************************************/
#include "changes.h"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <filesystem>

using std::cout;
using std::endl;
using std::cin;
using std::string;

static std::fstream changesFile;

// The static member lastChangeId keeps track of the last assigned change ID across all instances of the Changes class.
int Changes::lastChangeId = 0;

Changes::Changes() : changeId(lastChangeId), priority(0), isBug(false) 
{
/*
 * Default constructor that initializes the Changes values to 0 or false.
 * 
 * Implementation Details:
 * - Uses memset to fill the productName array with null characters.
 */
    std::memset(changeStatus, '\0', CHANGESTATUSSIZE + 1);
    std::memset(productName, '\0', PRODUCTNAMESIZE + 1);
    std::memset(release_Id, '\0', RELEASE_IdSIZE + 1);
    std::memset(description, '\0', DESCRIPTIONSIZE + 1);
    lastChangeId++;
}

Changes::Changes(int changeId, string changeStatus, string productName, string release_Id, 
                 int priority, string description, bool isBug) 
{
/*
 * Parameterized constructor that initializes the productName array to an empty string.
 * 
 * Implementation Details:
 * - Uses memset to fill the productName array with null characters.
 */

    bool invalid = false;
    this->changeId = changeId;
    this->priority = priority;
    this->isBug = isBug;

    //Check for invalid input with ifs.
    if(changeStatus.length() > CHANGESTATUSSIZE){
        invalid = true;
    }
    if(productName.length() > PRODUCTNAMESIZE){
        invalid = true;
    }
    if(release_Id.length() > RELEASE_IdSIZE){
        invalid = true;
    }
    if(description.length() > DESCRIPTIONSIZE){
        invalid = true;
    }

    //run a loop until all inputs are valid.
    while(invalid){
        if(changeStatus.length() > CHANGESTATUSSIZE){
            invalid = true;
            std::cout << "Please enter valid change status." << std::endl;
            cin >> changeStatus;
        }
        if(productName.length() > PRODUCTNAMESIZE){
            invalid = true;
            std::cout << "Please enter valid product name." << std::endl;
            cin >> productName;
        }

        if(release_Id.length() > RELEASE_IdSIZE){
            invalid = true;
            std::cout << "Please enter valid release_id." << std::endl;
            cin >> release_Id;
        }

        if(description.length() > DESCRIPTIONSIZE){
            invalid = true;
            std::cout << "Please enter valid description." << std::endl;
            cin >> description;
        }
        else{
            invalid = false;
        }

    }
    strncpy(this->changeStatus, changeStatus.c_str(), changeStatus.length());
    strncpy(this->productName, productName.c_str(), productName.length());
    strncpy(this->release_Id, release_Id.c_str(), release_Id.length());
    strncpy(this->description, description.c_str(), description.length());

    for(int i=changeStatus.length(); i < changeStatus.length() + 1; i++)
    {
         this->changeStatus[i] = '\0';
    }

    for(int i=productName.length(); i < productName.length() + 1; i++)
    {
         this->productName[i] = '\0';
    }

    for(int i=release_Id.length(); i < release_Id.length() + 1; i++)
    {
         this->release_Id[i] = '\0';
    }

    for(int i=description.length(); i < description.length() + 1; i++)
    {
         this->description[i] = '\0';
    }

    lastChangeId = changeId;

}

int Changes::getchangeId() 
{ 
/*
 * This function returns the change id of Changes as a c++ integer.
 * 
 * Implementation Details:
 * - Returns the integer.
 */
    return this->changeId; 
}
string Changes::getchangeStatus() 
{ 
/*
 * This function returns the status of Changes as a c++ string.
 * 
 * Implementation Details:
 * - Returns the string.
 */
    string status = string(this->changeStatus);
    return status;
}
string Changes::getProductName() 
{ 
/*
 * This function returns the product name of this instance of changes as a c++ string.
 * 
 * Implementation Details:
 * - Returns the string.
 */
    string product = string(this->productName);
    return product; 
}
string Changes::getReleaseId() 
{ 
/*
 * This function returns the release id of this instance of changes as a c++ string.
 * 
 * Implementation Details:
 * - Returns the string.
 */
    string releaseID = string(this->release_Id);
    return releaseID; 
}
int Changes::getPriority() 
{ 
/*
 * This function returns the priority level of Changes as a c++ integer.
 * 
 * Implementation Details:
 * - Returns the integer.
 */
    return this->priority;
}
string Changes::getDescription() 
{ 
/*
 * This function returns the description of this instance of changes as a c++ string.
 * 
 * Implementation Details:
 * Typecasts the description of this instance of changes into a string and returns it.
 * - Returns the string.
 */
    string strDescription = string(this->description);
    return strDescription; 
}
bool Changes::getIsBug() 
{ 
/*
 * This function returns the bool value of isBug of this instance of changes as a bool value.
 * 
 * Implementation Details:
 * - Returns the bool value for isBug of this instance.
 */
    return this->isBug; 
}

void Changes::setchangeId(const int &changeId) 
{
/*
 * This function sets the changeId to the parameter passed in.
 */
    this->changeId = changeId;
}

void Changes::setchangeStatus(const string &changeStatus) 
{
/*
 * This function sets the change status name by copying the input string to the 
 * changeStatus array using strncpy. 
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input string to the productName array.
 * - Ensures the last character is null-terminated.
 */
    strncpy(this->changeStatus, changeStatus.c_str(), CHANGESTATUSSIZE - 1);
}

void Changes::setProductName(const string &productName) 
{
/*
 * This function sets the product name by copying the input string to the 
 * productName array using strncpy. 
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input string to the productName array.
 * - Ensures the last character is null-terminated.
 */
    strncpy(this->productName, productName.c_str(), PRODUCTNAMESIZE - 1);
}

void Changes::setReleaseId(const string &releaseId) 
{
/*
 * This function sets the release id by copying the input string to the 
 * releaseId array using strncpy. 
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input string to the releaseId array.
 * - Ensures the last character is null-terminated.
 */
    strncpy(this->release_Id, releaseId.c_str(), RELEASE_IdSIZE - 1);
}

void Changes::setPriority(const int &priority) 
{
/*
 * This function sets the priority level to the parameter passed in.
 */
    this->priority = priority;
}

void Changes::setDescription(const string &description) 
{
/*
 * This function sets the description by copying the input string to the 
 * description array using strncpy. 
 * 
 * Implementation Details:
 * - Uses strncpy to copy the input string to the description array.
 * - Ensures the last character is null-terminated.
 */
    strncpy(this->description, description.c_str(), DESCRIPTIONSIZE - 1);
}

void Changes::setIsBug(const bool &isBug) 
{
/*
 * This function sets the bool isBug to the inputted parameters
 * 
 * Implementation Details:
 * - set isBug = input
 */
    this->isBug = isBug;
}

void Changes::setChangeId(const int &changeId) 
{
/*
 * This function sets the change id to the inputted parameters
 * 
 * Implementation Details:
 * - set changeId = changeId
 */
    this->changeId = changeId;
}

Changes Changes::viewNewChangesUI() 
{
/*
 * Function to display new changes for the user.
 * 
 * Implementation Details:
 * - Uses a while loop to print all new changes as desired by user
 */
    const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool isEnd = false;                  // Flag to indicate end of file
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPageChanges = 0;          // Current page number
    int productSelection = 0;            // product selection
    Changes changeObj;

    while(!exit)
    {
        seekToBeginningOfFile();

        isEnd = false;

        for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE; ++i)
        {
            readFromFile(isEnd);         // Read and discard releases to skip to the current page
            if(isEnd)                    // If end of file is reached
            {
                currentPageChanges--;    // Adjust current page number
                break;                   // Exit the loop
            }
        }
        if(isEnd)
        {
            cout << "No more changes to display." << endl;
            currentPageChanges--;
            continue;
        }
        //display changes information
        std::cout << "=====New Changes=====\n";
        std::cout << "SELECTION  PRODUCT     PRIORITY  DESCRIPTION\n";        
        std::cout << "---------  -------     --------  -----------\n";
        for(int i = 0, counter = 0; counter < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            Changes change = readFromFile(isEnd); // Read a change from the file
            if(!isEnd && change.getchangeStatus() == "New")                
            // Check if end of file is not reached and the current change has the desired product release and name
            {
                std::cout << counter + 1 << "  " << change.getProductName() << 
                "  " << change.getPriority() << "  " << change.getDescription() << "  " << "\n"; // Display change details for new changes
                counter++; //increment the counter each time related change instance is found
            }
        }
        std::cout << "<-P";
        std::cout << "    N->" << endl;
        // Determine navigation options
        std::cout << "            ";
        if (currentPageChanges > 0) // Show previous page option if not on the first page
        {
            std::cout << "<-P ";
        }
        else
        {
            std::cout << "    ";
        }

        if (!isEnd) // Show next page option if not on the last page
        {
            std::cout << "N->";
        }
        else
        {
            std::cout << "   ";
        }
        std::cout << "\nMake a Selection: ";
        // get user input
        std::string input;
        std::cin >> input;              
        // Read user input

        if(input == "P" || input == "p") // If user wants to go to previous page
        {
            if(currentPageChanges > 0)          // If not already on the first page
            {
                currentPageChanges--;           // Go to previous page
            }
        }
        else if(input == "N" || input == "n") // If user wants to go to next page
        {
            if(!isEnd)                   // If not already at the end of the file
            {
                currentPageChanges++;           // Go to next page
            }
        }
        else                            // If user entered a selection number
        {
            int selection = std::stoi(input); // Convert input to an integer               
            Changes changeObj;      
            for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + selection - 1; ++i)
            {
                readFromFile(isEnd);
                if(isEnd)
                    changeObj = readFromFile(isEnd);
                    break;
            }
            std::cout << "=====New Changes=====\n";
            std::cout << "Product         " << changeObj.getProductName() << "\n" ;        
            std::cout << "Priority        " << changeObj.getPriority() << "\n";
            std::cout << "Description     " << changeObj.getDescription() << "\n";
            std::cout << "Would you like to Cancel the Change? (Y/N)?\n";   

            string response;
            cin >> response;    
            
            if(response == "Y" || response == "y")
            {
                //Return to viewNewChangesUI
                viewNewChangesUI();
            }
            else{
                cout << "Would you like to edit the Priority (Y/N)?\n";
                cin >> response;
                if(response == "Y" || response == "y")
                {
                    cout << "Enter the Priority of the change (A number from 1-5) :\n";
                    int newPriority;
                    cin >> newPriority;
                    changeObj.setPriority(newPriority);
                }
                cout << "Would you like to edit the Description? (Y/N)?\n";
                cin >> response;
                if(response == "Y" || response == "y")
                {
                    cout << "Enter the new description for the change (max 30 char.):";
                    string newDescription;
                    cin >> newDescription;
                    changeObj.setDescription(newDescription);
                }

                if(selection > 0 && selection <= RELEASES_PER_PAGE ) // If selection is valid
                {
                    // seek again to the beginning of the file
                    seekToBeginningOfFile();  // Reset file pointer to the beginning

                    // skip releases of previous pages and selected releases on the current page
                    for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + selection - 1; ++i)
                    {
                        readFromFile(isEnd);  // Read and discard releases to skip to the selected release
                    }

                    return readFromFile(isEnd); // Return the selected release
                }

            }
        }

    }    
    // Return the selected change or *this if selection is invalid
    return changeObj;
}

bool Changes::isValid() 
{
/*
* Function to verify that a change object exists.
* 
* Implementation Details:
* - Checks if the changeId is within a valid range
* - Searches through the file to confirm the instance of Changes exists.
*/
    return (changeId > 0 && changeId <= 999999 &&
    ChangesExists(*this)
    );
}

Changes Changes::viewChangesFromProduct(const string &product) 
    {

    const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool isEnd = false;                  // Flag to indicate end of file
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPageProducts = 0;         // Current page num for products
    int currentPageChanges = 0;          // Current page number
    int productSelection = 0;            // product selection
    Changes changeObj;
    while(!exit)
    {
        seekToBeginningOfFile();

        for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + productSelection - 1; ++i)
        {
            readFromFile(isEnd);         // Read and discard releases to skip to the current page
            if(isEnd)                    // If end of file is reached
            {
                currentPageChanges--;    // Adjust current page number
                break;                   // Exit the loop
            }
        }
        if(isEnd)
        {
            cout << "No more products to display." << endl;
            currentPageProducts--;
            continue;
        }
        //display changes information
        std::cout << "=======Changes=======\n";
        std::cout << "SELECTION  STATUS      PRIORITY  DESCRIPTION                     BUG\n";        
        std::cout << "---------  ------      --------  -----------                     ---  \n";
        for(int i = 0; i < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            Changes change = readFromFile(isEnd); // Read a change from the file
            if(!isEnd)                // If end of file is not reached
            {
                std::cout << i + 1 << ") " << change.getchangeStatus() << "  " << change.getPriority() << "  " <<
                change.getDescription() << "  " << change.getIsBug() << "\n"; // Display change details
            }
        }
        // Determine navigation options
        std::cout << "            ";
        if (currentPageChanges > 0) // Show previous page option if not on the first page
        {
            std::cout << "<-P ";
        }
        else
        {
            std::cout << "    ";
        }

        if (!isEnd) // Show next page option if not on the last page
        {
            std::cout << "N->";
        }
        else
        {
            std::cout << "   ";
        }
        std::cout << "\nMake a Selection: ";
        // get user input
        std::string input;
        std::cin >> input;              
        // Read user input

        if(input == "P" || input == "p") // If user wants to go to previous page
        {
            if(currentPageProducts > 0)          // If not already on the first page
            {
                currentPageProducts--;           // Go to previous page
            }
        }
        else if(input == "N" || input == "n") // If user wants to go to next page
        {
            if(!isEnd)                   // If not already at the end of the file
            {
                currentPageProducts++;           // Go to next page
            }
        }
        else                            // If user entered a selection number
        {
            int selection = std::stoi(input); // Convert input to an integer               
                  
            for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + selection - 1; ++i)
            {
                readFromFile(isEnd);
                if(isEnd)
                    changeObj = readFromFile(isEnd);
                    break;
            }

  
            if (strcmp(changeObj.changeStatus, "Done") == 0 || strcmp(changeObj.changeStatus, "Completed") == 0) {
                std::cout << "Error: Attempting to edit completed change!" << std::endl;
                return changeObj;
            }


            std::cout << "=====Edit Change=====" << std::endl;
            std::cout << "ChangeID:    " << changeObj.changeId << std::endl;
            std::cout << "Priority:    " << changeObj.priority << std::endl;
            std::cout << "Description: " << changeObj.description << std::endl;
            std::cout << "Is :      " << (changeObj.isBug ? "a Bug" : "a Feature") << std::endl;
            std::cout << "Release:     " << changeObj.release_Id << std::endl;
            std::cout << "Status:      " << changeObj.changeStatus << std::endl;

            char response;
            std::cout << "Would you like to edit the Priority (Y/N)? ";
            std::cin >> response;
            if (response == 'Y' || response == 'y') 
            {
                int newPrio;
                std::cout << "Enter the Priority of the change (A number from 1-5):";
                std:: cin >> newPrio;
                changeObj.setPriority(newPrio);
            }
            std::cout << "Would you like to edit the Description (Y/N)?";
            std::cin >> response;
            if (response == 'Y' || response == 'y') 
            {
                string description;
                std::cout << "Enter the new Description for the change (max 30 char.)";
                std:: cin >> description;
                changeObj.setDescription(description);
            }    
            std::cout << "Would you like to edit the Status (Y/N)?";
            std::cin >> response;
            if (response == 'Y' || response == 'y') 
            {
                int statusOption;
                string status;
                std::cout << "====Select Status====" << std::endl;
                std::cout << "1) InProgress" << std::endl;
                std::cout << "2) Cancelled" << std::endl;
                std::cout << "3) Done" << std::endl;
                std::cout << "Please Select a Status:" << std::endl;
                std:: cin >> statusOption;
                switch (statusOption) {
                    case 1:
                        status = "InProgress";
                        break;
                    case 2:
                        status = "Cancelled";
                        break;
                    case 3:
                        status = "Done";
                        break;
                    default:
                        std::cout << "Invalid selection" << std::endl;
                }
                changeObj.setchangeStatus(status);  
            }
            if(selection > 0 && selection <= RELEASES_PER_PAGE ) // If selection is valid
            {
                // seek again to the beginning of the file
                seekToBeginningOfFile();  // Reset file pointer to the beginning

                // skip releases of previous pages and selected releases on the current page
                for(int i = 0; i < currentPageProducts * RELEASES_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd);  // Read and discard releases to skip to the selected release
                }

                return readFromFile(isEnd); // Return the selected release
            }
        }

    }
    // Return the selected change or *this if selection is invalid
    return changeObj;

}

Changes Changes::viewUnfinishedChanges(const string &productRelease, const string &product) 
{
    // Implement the logic to display unfinished changes and return a Changes object
    // This is a placeholder implementation
    const int RELEASES_PER_PAGE = 20;    // Number of releases displayed per page
    bool isEnd = false;                  // Flag to indicate end of file
    bool exit = false;                   // Flag to indicate user wants to exit
    int currentPageChanges = 0;          // Current page number
    int productSelection = 0;            // product selection
    Changes changeObj;
    
    while(!exit)
    {
        seekToBeginningOfFile();

        for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE; ++i)
        {
            readFromFile(isEnd);         // Read and discard releases to skip to the current page
            if(isEnd)                    // If end of file is reached
            {
                currentPageChanges--;    // Adjust current page number
                break;                   // Exit the loop
            }
        }
        if(isEnd)
        {
            cout << "No more products to display." << endl;
            currentPageChanges--;
            continue;
        }
        //display changes information
        std::cout << "=======Changes=======\n";
        std::cout << "STATUS      PRIORITY  DESCRIPTION                     BUG\n";        
        std::cout << "------      --------  -----------                     ---\n";
        for(int i = 0, counter = 0; counter < RELEASES_PER_PAGE && !isEnd; ++i)
        {
            Changes change = readFromFile(isEnd); // Read a change from the file
            if(!isEnd && change.getReleaseId() == productRelease && change.getProductName() == product)                
            // Check if end of file is not reached and the current change has the desired product release and name
            {
                std::cout << counter + 1 << "  " << change.getchangeStatus() << 
                "  " << change.getPriority() << "  " << change.getDescription() << "  " <<
                change.getIsBug() << "  " << "\n"; // Display change details for specific release id
                counter++; //increment the counter each time related change instance is found
            }
        }
        // Determine navigation options
        std::cout << "            ";
        if (currentPageChanges > 0) // Show previous page option if not on the first page
        {
            std::cout << "<-P ";
        }
        else
        {
            std::cout << "    ";
        }

        if (!isEnd) // Show next page option if not on the last page
        {
            std::cout << "N->";
        }
        else
        {
            std::cout << "   ";
        }
        std::cout << "\nMake a Selection: ";
        // get user input
        std::string input;
        std::cin >> input;              
        // Read user input

        if(input == "P" || input == "p") // If user wants to go to previous page
        {
            if(currentPageChanges > 0)          // If not already on the first page
            {
                currentPageChanges--;           // Go to previous page
            }
        }
        else if(input == "N" || input == "n") // If user wants to go to next page
        {
            if(!isEnd)                   // If not already at the end of the file
            {
                currentPageChanges++;           // Go to next page
            }
        }
        else                            // If user entered a selection number
        {
            int selection = std::stoi(input); // Convert input to an integer               
            Changes changeObj;      
            for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + selection - 1; ++i)
            {
                readFromFile(isEnd);
                if(isEnd)
                    changeObj = readFromFile(isEnd);
                    break;
            }
            if(selection > 0 && selection <= RELEASES_PER_PAGE ) // If selection is valid
            {
                // seek again to the beginning of the file
                seekToBeginningOfFile();  // Reset file pointer to the beginning

                // skip releases of previous pages and selected releases on the current page
                for(int i = 0; i < currentPageChanges * RELEASES_PER_PAGE + selection - 1; ++i)
                {
                    readFromFile(isEnd);  // Read and discard releases to skip to the selected release
                }

                return readFromFile(isEnd); // Return the selected release
            }

        }

    }    
    // Return the selected change or *this if selection is invalid
    return changeObj;
}

Changes Changes::readFromFile(bool &isEnd)
/*
 * This function reads the next file from the internal file member.
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This moves the file "position" to the next element, so a subsequent call to readFromFile will return the next element in the file
 */ 
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Changes file was not open when it was expected to be!\n";
        throw std::runtime_error("Changes file not open on readFromFile");
    }
    Changes toReturn;

    if(file.peek() == EOF)
    {
        isEnd = true;
        return toReturn;
    }
    isEnd = false;
    
    // Read all members from disk in the EXACT same order as they were written
    file.read((char*)&toReturn.changeId, sizeof(int));
    file.read(toReturn.changeStatus, sizeof(char) * CHANGESTATUSSIZE);
    file.read(toReturn.productName, sizeof(char) * PRODUCTNAMESIZE);
    file.read(toReturn.release_Id, sizeof(char) * RELEASE_IdSIZE);
    file.read((char*)&toReturn.priority, sizeof(int));
    file.read(toReturn.description, sizeof(char) * DESCRIPTIONSIZE);
    file.read((char*)&toReturn.isBug, sizeof(bool));

    return toReturn;
}

bool Changes::writeToFile(Changes change)
/*
 * This function will append a Change to the file
 * 
 * Implementation Details:
 * - It's assumed the file is already opened and valid.
 * - If this is not true, then an error is thrown and displayed to the user.
 * - This function will check for any entity integrity violations, if there is one it will overwrite the entry.
 */
{
    if(!file.is_open())
    {
        std::cout << "An error has occured!\n";
        std::cout << "The Changes file was not open when it was expected to be!\n";
        throw std::runtime_error("Changes file not open on writeToFile");
    }
    seekToBeginningOfFile();
    bool invalid = true;
    Changes nextToCheck = readFromFile(invalid);

    // Check to see if any change in the system matches our current change
    while(!invalid)
    {
        if(nextToCheck.getchangeId() == change.getchangeId())
        {
            // Move back in the file to make sure it's working on the same entry
            // Change ID
            file.seekg(-sizeof(int), std::fstream::cur);
            // Change Status
            file.seekg(-sizeof(char) * CHANGESTATUSSIZE, std::fstream::cur);
            // Product Name
            file.seekg(-sizeof(char) * PRODUCTNAMESIZE, std::fstream::cur);
            // Release ID
            file.seekg(-sizeof(char) * RELEASE_IdSIZE, std::fstream::cur);
            // Priority
            file.seekg(-sizeof(int), std::fstream::cur);
            // Description
            file.seekg(-sizeof(char) * DESCRIPTIONSIZE, std::fstream::cur);
            // Bug
            file.seekg(-sizeof(bool), std::fstream::cur);
            break;
        }
        nextToCheck = readFromFile(invalid);
    }

    // Seek to the end of the file if we're not overwriting an entry
    if(invalid == true)
        file.seekg(0, std::ios::end);

    // Write all elements of the Change to disk
    file.write((char*)&change.changeId, sizeof(int));
    file.write(change.changeStatus, sizeof(char) * CHANGESTATUSSIZE);
    file.write(change.productName, sizeof(char) * PRODUCTNAMESIZE);
    file.write(change.release_Id, sizeof(char) * RELEASE_IdSIZE);
    file.write((char*)&change.priority, sizeof(int));
    file.write(change.description, sizeof(char) * DESCRIPTIONSIZE);
    file.write((char*)&change.isBug, sizeof(bool));

    return !(file.fail() || file.bad());
}

bool Changes::seekToBeginningOfFile() 
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
        std::cout << "The Changes file was not open when it was expected to be!\n";
        throw std::runtime_error("Changes file not open on seekToBeginningOfFile");
    }
    file.seekg(0);
    return !(file.fail() || file.bad());
}

bool Changes::openChangesFile(std::string path) 
/*
 * This function will open the changes.bin file and will return false on failure
 * 
 * Implementation Details:
 * - The file will be opened with reading & writing capabilities, as well in binary mode
 */
{
    // Create the technovo directory if it doesn't exist
    if(!std::filesystem::exists(path+"technovo/"))
        std::filesystem::create_directory(path+"technovo/");
    // Attempt to open the file
    file.open(path+"technovo/changes.bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    bool valid = file.is_open();


    // If the file fails to open, try again with the trunc flag (will create a new file if there isn't one)
    if(!valid)
    {
        file.open(path+"technovo/changes.bin", std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
        valid = file.is_open();
    }

    // Make sure the file opened and we're at the start
    return valid && seekToBeginningOfFile();
}


bool Changes::closeChangesFile()
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
        std::cout << "The Changes file was not open when it was expected to be!\n";
        throw std::runtime_error("Changes file not open on closeChangesFile");
    }

    file.close();
    return !(file.fail() || file.bad());
}

bool Changes::ChangesExists(Changes input)
/*
 * Checks if a change already exists within the system
 *
 * Implementation Details: 
 * - It's assumed the file is already opened and valid
 * - Loops through the file linearly and checks every single instance
 */
{
    seekToBeginningOfFile();
    bool invalid = true;
    Changes nextRead = readFromFile(invalid);
    while(!invalid)
    {
        if(nextRead.getchangeId() == input.getchangeId())
            return true;
        nextRead = readFromFile(invalid);
    }
    return false;
}
