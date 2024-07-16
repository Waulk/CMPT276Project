#include "changes.h"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

static std::fstream changesFile;

int Changes::lastChangeId = 0;

Changes::Changes() : changeId(lastChangeId), priority(0), isBug(false) 
{
/*
 * Default constructor that initializes the Changes values to 0 or false.
 * 
 * Implementation Details:
 * - Uses memset to fill the productName array with null characters.
 */
    std::memset(changeStatus, '\0', CHANGESTATUSSIZE);
    std::memset(productName, '\0', PRODUCTNAMESIZE);
    std::memset(release_Id, '\0', RELEASE_IdSIZE);
    std::memset(description, '\0', DESCRIPTIONSIZE);
    lastChangeId++;
    array.push_back(*this);
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
    this->changeId = changeId;
    this->priority = priority;
    this->isBug = isBug;
    strncpy(this->changeStatus, changeStatus.c_str(), CHANGESTATUSSIZE - 1);
    strncpy(this->productName, productName.c_str(), PRODUCTNAMESIZE - 1);
    strncpy(this->release_Id, release_Id.c_str(), RELEASE_IdSIZE - 1);
    strncpy(this->description, description.c_str(), DESCRIPTIONSIZE - 1);

    for(int i=changeStatus.length(); i < CHANGESTATUSSIZE + 1; i++)
    {
         changeStatus[i] = '\0';
    }

    for(int i=productName.length(); i < PRODUCTNAMESIZE + 1; i++)
    {
         productName[i] = '\0';
    }

    for(int i=release_Id.length(); i < RELEASE_IdSIZE + 1; i++)
    {
         release_Id[i] = '\0';
    }

    for(int i=description.length(); i < DESCRIPTIONSIZE + 1; i++)
    {
         description[i] = '\0';
    }

    lastChangeId = changeId;

    array.push_back(*this);
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

int Changes::setchangeId(const int &changeId) 
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
 * - Uses a loop to repeatedly print all new changes
 */
return *this;
}

bool Changes::isValid() 
{
/*
* Function to verify that a changeId exists in the vector of changes.
* 
* Implementation Details:
* - Checks if the changeId is within a valid range
* - Uses std::find to check if the changeId exists in the array of changes
*/
    return (changeId > 0 && changeId <= 999999 && 
            std::find(array.begin(), array.end(), changeId) != array.end());
}

Changes Changes::viewChangesFromProduct(const string &product) 
{
    // Implement the logic to display changes for a specific product and return a Changes object
    // This is a placeholder implementation
    return *this;
}

Changes Changes::viewUnfinishedChanges(const string &productRelease, const string &product) 
{
    // Implement the logic to display unfinished changes and return a Changes object
    // This is a placeholder implementation
    return *this;
}

Changes Changes::viewCustomerRequestedChanges(const string &customer) 
{
    return *this;
}

Changes Changes::editChanges(const string &product, int newPriority, string newDescription, bool isBug, string newRelease, string newChangeStatus) {
    if (strcmp(this->changeStatus, "Done") == 0 || strcmp(this->changeStatus, "Completed") == 0) {
        std::cout << "Error: Attempting to edit completed change!" << std::endl;
        return *this;
    }

    std::cout << "=====Edit Change=====" << std::endl;
    std::cout << "ChangeID:    " << this->changeId << std::endl;
    std::cout << "Priority:    " << this->priority << std::endl;
    std::cout << "Description: " << this->description << std::endl;
    std::cout << "Is :      " << (this->isBug ? "a Bug" : "a Feature") << std::endl;
    std::cout << "Release:     " << this->release_Id << std::endl;
    std::cout << "Status:      " << this->changeStatus << std::endl;

    char response;
    std::cout << "Would you like to edit the Priority (Y/N)? ";
    std::cin >> response;
    if (response == 'Y' || response == 'y') {
        int newPrio;
        std::cout << "Enter the Priority of the change (A number from 1-5):";
        std:: cin >> newPrio;
        this->setPriority(newPrio);
    }
    std::cout << "Would you like to edit the Description (Y/N)?";
    if (response == 'Y' || response == 'y') {
        string description;
        std::cout << "Enter the new Description for the change (max 30 char.)";
        std:: cin >> description;
        this->setDescription(description);
    }    
    std::cout << "Would you like to edit the Status (Y/N)?";
    if (response == 'Y' || response == 'y') {
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
        this->setchangeStatus(status);
    }
    return *this;
}

Changes Changes::readFromFile(bool &isEnd) 
{
}

bool Changes::writeToFile(Changes change) 
{
}

bool Changes::seekToBeginningOfFile() 
{
}

bool Changes::openChangesFile() 
{
}

bool Changes::closeChangesFile() 
{
}