/***********************************************
 * Module: userinterface.cpp
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-30 Edited by Jayden Brown
 *         - Changed function calls
 *         - Implemented viewCustomersRequestedChange
 *         - Removed the ability to see all customers
 *         - Opens files with a path instead of hardcoded directories
 * Ver. 1: - 2024-07-14 Original by Jayden Brown
 *         - Initial version
 ***********************************************/

/***********************************************
 * The UserInterface class handles any "Main Menu" interface
 * while allowing each header to handle their own relevant interfaces.
 * This file implements many functions which are only available within this file
 * These functions are intended to only be used internally by the UserInterface class so they are kept out of the header
 * to keep the implementation out of anybody's direct view.
***********************************************/
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "userinterface.h"
#include "changes.h"
#include "product.h"
#include "productrelease.h"
#include "report.h"
#include "reporter.h"

// Intended to easily change the path of the technovo directory
// Linux example: "/etc/"
// Windows example: "C:/Users/Jayden/Documents/Source/repos/CMPT276Project/"
const std::string TECHNOVO_PATH = "/etc/";

/***********************************************/
UserInterface::UserInterface()
/*
 * Default constructor that initializes the member variables
 *
 * Implementation Details:
 *  - Opens all required files that will be used. This is the "startup" procedure
 *  - If a file fails to open the program's execution is cancelled and it crashes
*/
{
    // Initializes files for every object
    // If an object doesn't have a file a new one will be created

    // openChangesFile handles updating the latest changeid
    if(!Changes::openChangesFile(TECHNOVO_PATH))
        throw std::runtime_error("Changes file failed to open!");
    if(!Product::openProductFile(TECHNOVO_PATH))
        throw std::runtime_error("Products file failed to open!");
    if(!ProductRelease::openProductReleaseFile(TECHNOVO_PATH))
        throw std::runtime_error("Product Releases file failed to open!");
    if(!Report::openReportFile(TECHNOVO_PATH))
        throw std::runtime_error("Reports file failed to open!");
    if(!Reporter::openReporterFile(TECHNOVO_PATH))
        throw std::runtime_error("Reporters file failed to open!");
}

/***********************************************/
void createNewProductRelease()
/*
 * Create a new product release
 *
 * Implementation Details:
 *  - Makes calls to other classes to handle their UI
 *  - Makes the calls to manually save data
*/
{
    // Get a product from the user, and if it's an empty product make a new one
    Product prod = Product::getProductFromUser(true);
    if(prod.getProductName() == "")
        prod = Product::setProductNameUI();
    
    // Get the new release
    ProductRelease newRelease;
    newRelease.setProductName(prod.getProductName());

    // If the release already exists, keep asking until you get one that doesn't
    while(true)
    {
        newRelease.setReleaseIdUI();
        if(!ProductRelease::productReleaseExists(newRelease))
        {
            break;
        }
        std::cout << "Invalid input! A release with that ID already exists!\n";
    }

    // Set the date then save
    newRelease.setDateUI();
    Product::writeToFile(prod);
    ProductRelease::writeToFile(newRelease);
}

/***********************************************/
int getUserSelectionForMenu(int min, int max)
/*
 * Gets a user selection that would fit in a menu
 *
 * Implementation Details:
 *  - Repeatedly asks the user for an answer until a valid one is given
 *  - If an empty character is entered then an exception is thrown which will return to the main menu
*/
{

    bool isResponseValid = false;
    std::string response;
    int selection = 0;
    while(!isResponseValid)
    {
        // Get the entire line of user entered data, and if it's empty throw an error
        getline(std::cin, response);
        if(response.empty())
            throw std::invalid_argument("Invalid Response by User");
        // If the selection makes sense (only one digit) convert it to an integer
        if(response.size() == 1)
            selection = response.at(0) - '0';

        // Check if the number fits within the min and max and if it does then it is valid
        isResponseValid = UserInterface::isEnteredValid(selection, min, max);
        if(!isResponseValid)
        {
            std::cout << "Invalid selection!\n";
        }
    }
    return selection;
}

/***********************************************/
void viewCustomersRequestedChange()
/*
 * Opens a list of customers who requested a change
 *
 * Implementation Details:
 *  - Directly accesses both the Report and Reporter files and uses a "two-pointer" technique to traverse both
 *  - On a page change each file is read from the beginning again so it's is quite slow
*/
{
    // Get the change to be viewed
    Product productToView = Product::getProductFromUser();
    Changes changeToView = Changes::viewChangesFromProduct(productToView.getProductName());

    const int REPORTERS_PER_PAGE = 20;
    bool exit = false;
    int currentPage = 0;
    while(!exit)
    {
        Report::seekToBeginningOfFile();
        Reporter::seekToBeginningOfFile();
        bool isEnd = false;
        
        // Skip reports of previous pages
        for (int i = 0; i < currentPage * REPORTERS_PER_PAGE; ) {
            Report readReport = Report::readFromFile(isEnd); // Read in a report and only increment if it is for the change
            if(isEnd)
            {
                currentPage--;
                break;
            }
                
            if(readReport.getChangeId() == changeToView.getchangeId())
            {
                i++;
            }
        }
        if (isEnd) {
            std::cout << "No more reporters to display." << std::endl;
            if (currentPage > 0) {
                --currentPage;
            }
            continue;
        }
        std::cout << "======Customers======\n";
        std::cout << "EMAIL                     NAME\n";
        std::cout << "PHONE NUMBER  DEPT\n";
        std::cout << "--------------------------------------------------------\n";
        int read = 0;
        bool readNext = true;
        bool endOfReporter = false;
        // Will keep reading new reports and their corresponding reporter until either it's read REPORTERS_PER_PAGE amount OR it reads to the end of the file
        while(readNext)
        {
            if(read == REPORTERS_PER_PAGE)
            {
                break;
            }
            Report nextReport;
            bool isNextReportFound = false;
            while(!isNextReportFound)
            {
                nextReport = Report::readFromFile(isEnd);
                if(isEnd)
                {
                    readNext = false;
                    break;
                }
                if(nextReport.getChangeId() == changeToView.getchangeId())
                {
                    isNextReportFound = true;
                    read++;
                }
            }
            if(!readNext)
                break;
            // Read to find reporter with the email of the report
            Reporter::seekToBeginningOfFile();
            bool isReporterFound = false;
            Reporter foundReporter;
            while(!isReporterFound)
            {
                // endOfReporter should never be false, if it is then there is something seriously wrong (will cause a crash)
                foundReporter = Reporter::readFromFile(endOfReporter);
                if(foundReporter.getEmail() == nextReport.getEmail())
                {
                    isReporterFound = true;
                }
            }
            std::cout << std::left << std::setw(Reporter::EMAILDATASIZE) << foundReporter.getEmail() << "  ";
            std::cout << foundReporter.getCustomerName() << '\n';
            std::cout << std::left << std::setw(Reporter::PHONENUMBERSIZE) << foundReporter.getPhoneNumber() << "  ";
            // endl needs to specifically be used here to flush the buffer (due to weird formatting issues)
            std::cout << std::left << std::setw(Reporter::DEPTIDSIZE) << foundReporter.getDepartmentId() << "\n" << std::endl;
        }
        std::cout << "                       ";
        std::cout << "<-P  N->\n";
        std::cout << "Next or Previous?\n";
        std::string input;
        bool isResponseValid = false;
        char selection;

        // Loop to select either moving back a page or moving forward a page
        while(!isResponseValid)
        {
            // Get the entire line of user entered data, and if it's empty throw an error
            getline(std::cin, input);
            if(input.empty())
                throw std::invalid_argument("Invalid Response by User");
            // If the selection makes sense (only one digit) convert it to an integer
            if(input.size() == 1)
                selection = input.at(0);
            else
            {
                selection = false;
            }
            selection = tolower(selection);
            if(selection == 'n')
            {
                if(read == REPORTERS_PER_PAGE)
                {
                    isResponseValid = true;
                    currentPage++;
                }
                else
                    std::cout << "No next page!\n";
                
            }
            else if(selection == 'p')
            {
                if(currentPage > 0)
                {
                    isResponseValid = true;
                    currentPage--;
                }
                else
                {
                    std::cout << "No previous page!\n";
                }
                
            }
            if(!isResponseValid)
            {
                std::cout << "Invalid selection!\n";
            }
        }
        
    }

}

/***********************************************/
void customerMenu()
/*
 * Handles the customer submenu
 *
 * Implementation Details:
 *  - Prompts the user with the selection details
 *  - Uses a switch to handle the cases
*/
{
    std::cout << "======Customers======\n";
    std::cout << "\t1) View Customers Who Requested Change\n";
    std::cout << "\t2) Add Customer\n";
    std::cout << "Which item are you interested in?\n";
    int selection = getUserSelectionForMenu(1, 2);

    switch(selection)
    {
        case 1:
            viewCustomersRequestedChange();
            break;
        case 2:
            // Create a new customer
            std::cout << "=====New Customer====\n";
            Reporter::reporterUI(true);
            break;
    }
}

/***********************************************/
void createNewIssue()
/*
 * Handles creating a new issue
 *
 * Implementation Details:
 *  - Uses a pipeline of sorts to pass data between classes to get the end result of a new issue
*/
{
    std::cout << "======New Issue======\n";
    // Get a reporter
    Reporter newReporter = Reporter::reporterUI();
    // Get the product
    Product selectedProduct = Product::getProductFromUser();
    // Get the release for the product
    ProductRelease selectedRelease = ProductRelease::getProductReleaseFromUser(selectedProduct.getProductName());
    // Get the change where the issue exists
    Changes selectedChange = Changes::viewChangesFromProduct(selectedProduct.getProductName(), true);
    // Calculate the current date
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string date(30, '\0');
    std::strftime(&date[0], date.size(), "%Y-%m-%d", std::localtime(&now));
    // Generate the report and save it to disk
    Report newReport(newReporter.getEmail(), selectedChange.getchangeId(), selectedRelease.getReleaseId(), date);
    Report::writeToFile(newReport);
}

/***********************************************/
bool getTrueorFalseFromUser()
/*
 * Prompts the user until a value of 'Y' or 'N' is entered (true or false respectively)
 *
 * Implementation Details:
 *  - Can accept lowercase values
*/
{
    std::string YesNo;
    bool validResponse = false;
    bool response;
    while(!validResponse)
    {
        getline(std::cin, YesNo);
        if(YesNo.empty())
            throw std::invalid_argument("User exited");
        try
        {
            response = UserInterface::isYesOrNo(YesNo);
            validResponse = true;
        }
        catch(const std::invalid_argument& e)
        {
            // Do nothing, just catch the exception from isYesOrNo
        }
        if(!validResponse)
        {
            std::cout << "Invalid selection!\n";
        }
    }
    return response;
}

/***********************************************/
void checkNewChanges()
/*
 * Handles checking new changes
 *
 * Implementation Details:
 *  - Will do a pipeline for the data\
 *  - Hands most tasks to the other clasess
*/
{
    // View new changes, will also handle editing and will return an edited one
    Changes selectedChange = Changes::viewNewChangesUI();
    std::cout << "=====New Changes=====\n";
    std::cout << "Product:     " << selectedChange.getProductName() << '\n';
    std::cout << "Priority:    " << selectedChange.getPriority() << '\n';
    std::cout << "Description: " << selectedChange.getDescription() << '\n';
    std::cout << "Would you like to Cancel the Change (Y/N)?\n";
    bool response = getTrueorFalseFromUser();
    std::string input;
    if(response)
    {
        selectedChange.setchangeStatus("Cancelled");
        Changes::writeToFile(selectedChange);
        checkNewChanges();
        return;
    }

    // Update the priority if required
    std::cout << "Would you like to edit the Priority (Y/N)?\n";
    response = getTrueorFalseFromUser();
    if(response)
    {
        std::cout << "Enter the Priority of the change (A number from 1-5):\n";
        getline(std::cin, input);
        if(input.empty())
            throw std::invalid_argument("Invalid Response by User");
        selectedChange.setPriority(std::atoi(input.c_str()));
    }

    // Update the description if required
    std::cout << "Would you like to edit the Description (Y/N)?\n";
    response = getTrueorFalseFromUser();
    if(response)
    {
        std::cout << "Enter the new Description for the change (max 30 char.):\n";
        getline(std::cin, input);
        if(input.empty())
            throw std::invalid_argument("Invalid Response by User");
        selectedChange.setDescription(input);
    }
    
    // Get the new release version for the change
    ProductRelease selectedRelease = ProductRelease::getProductReleaseFromUser(selectedChange.getProductName());
    selectedChange.setReleaseId(selectedRelease.getReleaseId());

    // Get if it's a bug
    std::cout << "=====New Changes=====\n";
    std::cout << "Is this a bug (Y/N)?\n";
    selectedChange.setIsBug(getTrueorFalseFromUser());

    selectedChange.setchangeStatus("Assessed");

    // Save to disk
    Changes::writeToFile(selectedChange);
}

/***********************************************/
void viewChangesForProduct()
/*
 * View all changes for a product
 *
 * Implementation Details:
 *  - Uses a pipeline for data
*/
{
    // Get the product and then view all changes for the product
    Product productToView = Product::getProductFromUser();
    Changes changeToEdit = Changes::viewChangesFromProduct(productToView.getProductName()); 
    if(changeToEdit.getchangeStatus() == "Done" || changeToEdit.getchangeStatus() == "Cancelled")
    {
        std::cout << "Error: Attempting to edit completed change!\n";
        return;
    }
    std::cout << "=====Edit Change=====\n";
    std::cout << "ChangeID:    " << changeToEdit.getchangeId() << '\n';
    std::cout << "Priority:    " << changeToEdit.getPriority() << '\n';
    std::cout << "Description: " << changeToEdit.getDescription() << '\n';
    std::cout << "Is Bug:      " << (changeToEdit.getIsBug() ? "True" : "False") << '\n';
    std::cout << "Release:     " << changeToEdit.getReleaseId() << '\n';
    std::cout << "Status:      " << changeToEdit.getchangeStatus() << '\n';

    // Edit priority
    std::cout << "Would you like to edit the Priority (Y/N)?\n";
    bool response = getTrueorFalseFromUser();
    std::string input;
    if(response)
    {
        std::cout << "Enter the Priority of the change (A number from 1-5):\n";
        getline(std::cin, input);
        if(input.empty())
            throw std::invalid_argument("Invalid Response by User");
        changeToEdit.setPriority(std::atoi(input.c_str()));
    }

    // Update the description if required
    std::cout << "Would you like to edit the Description (Y/N)?\n";
    response = getTrueorFalseFromUser();
    if(response)
    {
        std::cout << "Enter the new Description for the change (max 30 char.):\n";
        getline(std::cin, input);
        if(input.empty())
            throw std::invalid_argument("Invalid Response by User");
        changeToEdit.setDescription(input);
    }

    // Update status
    std::cout << "Would you like to edit the Status (Y/N)?\n";
    response = getTrueorFalseFromUser();
    if(response)
    {
        std::cout << "====Select Status====\n";
        std::cout << "\t1) InProgress\n";
        std::cout << "\t2) Cancelled\n";
        std::cout << "\t3) Done\n";
        std::cout << "Please Select a Status:\n";
        int option = getUserSelectionForMenu(1, 3);
        switch(option)
        {
            case 1:
                changeToEdit.setchangeStatus("InProgress");
                break;
            case 2:
                changeToEdit.setchangeStatus("Cancelled");
                break;
            case 3:
                changeToEdit.setchangeStatus("Done");
        }

    }

    // Update the change's release
    std::cout << "Would you like to edit the Change Product Release (Y/N)?\n";
    response = getTrueorFalseFromUser();
    if(response)
    {
        changeToEdit.setReleaseId(ProductRelease::getProductReleaseFromUser(productToView.getProductName()).getReleaseId());
    }
    Changes::writeToFile(changeToEdit);
}

/***********************************************/
void viewUnfinishedChangesForRelease()
/*
 * View all unfinished changes for a release
 *
 * Implementation Details:
 *  - Uses a pipeline for data
*/
{
    // Get the product
    Product productToView = Product::getProductFromUser();
    // Get the release from the product
    ProductRelease releaseToView = ProductRelease::getProductReleaseFromUser(productToView.getProductName());
    // View unfinished changes
    Changes::viewUnfinishedChanges(releaseToView.getReleaseId(), productToView.getProductName());
}

/***********************************************/
void changesMenu()
/*
 * Handles the submenu for changes
 *
 * Implementation Details:
 *  - Prompts the user for a selection
 *  - Uses a switch case to handle states
 *  - Calls sub functions to deal with each state
*/
{
    std::cout << "=======Changes=======\n";
    std::cout << "\t1) View New Changes\n";
    std::cout << "\t2) View Changes from Product\n";
    std::cout << "\t3) View Unfinished Changes for Release\n";
    std::cout << "Which item are you interested in?\n";
    int selection = getUserSelectionForMenu(1, 3);

    switch(selection)
    {
        case 1:
            // View all new changes in a list
            checkNewChanges();
            break;
        case 2:
            // View all changes for a product in a list
            viewChangesForProduct();
            break;
        case 3:
            // View all unfinished changes for a release in a list
            viewUnfinishedChangesForRelease();
            break;
    }

}

/***********************************************/
bool UserInterface::isEnteredValid(int entered, int min, int max)
/*
 * Verifies if an entered number is between two others
*/
{
    return entered <= max && entered >= min;
}

/***********************************************/
bool UserInterface::isYesOrNo(const std::string& entered)
/*
 * Checks if a string is either 'Y' or 'N'
 *
 * Implementation Details:
 *  - Accepts lowercase values
 *  - Throws an error if it is neither 'Y' or 'N'
 *  - Returns true for 'Y' and false for 'N'
*/
{
    if(entered.size() != 1)
        throw std::invalid_argument("Entered value is neither a Y or an N.");
    // Get the lowercase of the character
    char value = tolower(entered[0]);
    // Make sure it's either 'Y' or 'N'
    if(value != 'y' && value != 'n')
        throw std::invalid_argument("Entered value is neither a Y or an N.");

    return value == 'y';
}

/***********************************************/
void UserInterface::runMainMenu()
/*
 * Handles the main menu
 *
 * Implementation Details:
 *  - Will run on a loop until told to exit by setting m_bRunMenu to false
 *  - Uses a switch statement to handle the state given by a character entered
 *  - On shutdown it will handle closing all references to files for a clean shutdown
*/
{
    while(m_bRunMenu)
    {

        std::cout << "======Main Menu======\n";
        std::cout << "\t1) Add Issue\n";
        std::cout << "\t2) Changes\n";
        std::cout << "\t3) Customers\n";
        std::cout << "\t4) Add Product Release\n";
        std::cout << "\t5) Exit\n";
        std::cout << "Enter the selection (1-5):\n";
        
        std::cin.clear(); // Clear any error flags
        std::cin.sync();  // Synchronize the input buffer

        // Use a try and catch to handle exiting from any "interior" calls by throwing an exception
        try
        {
            int selection = getUserSelectionForMenu(1, 5);
            switch(selection)
            {
                case 1:
                    createNewIssue();
                    break;
                case 2:
                    changesMenu();
                    break;
                case 3:
                    customerMenu();
                    break;
                case 4:
                    createNewProductRelease();
                    break;
                case 5:
                    this->m_bRunMenu = false;
                    break;
            }
        }
        catch(const std::runtime_error& e)
        {
            std::cout << "Error: " << e.what() << '\n';
            break;
        }
        catch(...)
        {
            
        } 
    }

    // Run shutdown procedure
    Changes::closeChangesFile();
    Product::closeProductFile();
    ProductRelease::closeProductReleaseFile();
    Report::closeReportFile();
    Reporter::closeReporterFile();
}

