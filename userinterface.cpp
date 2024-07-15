/***********************************************
 * Module: userinterface.cpp
 * 
 * Ver. 1: - 2024-07-14 Original by Jayden Brown
 *         - Initial version
 ***********************************************/

/***********************************************
 * The UserInterface class handles any "Main Menu" interface
 * while allowing each header to handle their own relevant interfaces
***********************************************/
#include <iostream>
#include "userinterface.h"
#include "changes.h"
#include "product.h"
#include "productrelease.h"
#include "report.h"
#include "reporter.h"

/***********************************************/
UserInterface::UserInterface()
{
    // Initializes files for every object
    // If an object doesn't have a file a new one will be created
    //Changes::openProductFile();
    Product::openProductFile();
    ProductRelease::openProductReleaseFile();
    Report::openReportFile();
    Reporter::openReporterFile();
}

/***********************************************/
void UserInterface::runMainMenu()
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
        
        int selection = getUserSelectionForMenu(1, 5);

        // Use a try and catch to handle exiting from any "interior" calls by throwing an exception
        try
        {
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
                    Product prod = Product::getProductFromUser(true);
                    ProductRelease newRelease = ProductRelease::getProductReleaseFromUser(prod.getProductName());
                    Product::writeToFile(prod);
                    ProductRelease::writeToFile(newRelease);
                    break;
                case 5:
                    this->m_bRunMenu = false;
                    break;
            }
        }
        catch(...)
        {
            
        } 
    }
}

/***********************************************/
void createNewIssue()
{
    Reporter newReporter = Reporter();
    Product selectedProduct = Product::getProductFromUser();
    std::string selectedChange = Changes::viewChangesFromProduct(selectedProduct.getProductName());
    Report::openReportFileAndWrite(); // Needs a way to write the report
}

/***********************************************/
bool getTrueorFalseFromUser() // TODO: change this to a public static function
{
    std::string YesNo;
    bool validResponse = false;
    bool response;
    while(!validResponse)
    {
        getline(std::cin, YesNo);
        try
        {
            response = UserInterface::isYesOrNo(YesNo);
            validResponse = true;
        }
        catch(const std::invalid_argument e)
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
int getUserSelectionForMenu(int min, int max) // TODO: change this to public too
{
    bool isResponseValid = false;
    std::string response;
    int selection = 0;
    while(!isResponseValid)
    {
        getline(std::cin, response);
        if(response.empty())
            throw std::invalid_argument("Invalid Response by User");
        if(response.size() == 1)
            selection = response.at(0) - '0';
        isResponseValid = UserInterface::isEnteredValid(selection, min, max);
        if(!isResponseValid)
        {
            std::cout << "Invalid selection!\n";
        }
    }
    return response;
}

/***********************************************/
void checkNewChanges()
{
    Changes selectedChange = Changes::viewNewChangesUI();
    ProductRelease selectedRelease = ProductRelease::getProductReleaseFromUser(selectedChange.getProductName());
    std::cout << "=====New Changes=====\n";
    std::cout << "Is this a bug (Y/N)?\n";
    
    selectedChange.setIsBug(getTrueorFalseFromUser());
    Changes::writeToFile(selectedChange);
}

/***********************************************/
void viewChangesForProduct()
{
    Product productToView = Product::getProductFromUser();
    Changes changeToEdit = Changes::viewChangesFromProduct(productToView.getProductName()); 
    //TODO: fix this when updated (section 4.3, edit change, will be a new function call)

    std::cout << "Would you like to edit the Change Product Release (Y/N)?\n";
    bool editRelease = getTrueorFalseFromUser();

    if(editRelease)
    {
        ProductRelease::getProductReleaseFromUser(productToView.getProductName());
    }
    Changes::writeToFile(changeToEdit);
}

/***********************************************/
void viewUnfinishedChangesForRelease()
{
    Product productToView = Product::getProductFromUser();
    ProductRelease releaseToView = ProductRelease::getProductReleaseFromUser(productToView.getProductName());
    Changes::viewUnfinishedChanges(); // TODO: this requires a string for product release
}

/***********************************************/
void changesMenu()
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
            checkNewChanges();
            break;
        case 2:
            viewChangesForProduct();
            break;
        case 3:
            viewUnfinishedChangesForRelease();
            break;
    }

}

/***********************************************/
void viewCustomersRequestedChange()
{
    Product prouctToView = Product::getProductFromUser();
    Changes changeToView = Changes::viewChangesFromProduct(prouctToView.getProductName());
    // TODO: figure out a good way of getting the customers to do with the change
}



/***********************************************/
void customerMenu()
{
    std::cout << "======Customers======\n";
    std::cout << "\t1) View Customers Who Requested Change\n";
    std::cout << "\t2) View All Customers\n";
    std::cout << "\t3) Add Customer\n";
    std::cout << "Which item are you interested in?\n";
    int selection = getUserSelectionForMenu(1, 3);

    switch(selection)
    {
        case 1:
            viewCustomersRequestedChange();
            break;
        case 2:
            Reporter::viewAllReporter();
            break;
        case 3:
            Reporter newReporter = Reporter();
            Reporter::openReporterFileAndWrite(newReporter);
            break;
    }
}

/***********************************************/
bool UserInterface::isEnteredValid(int entered, int min, int max)
{
    return entered <= max && entered >= min;
}

/***********************************************/
bool UserInterface::isYesOrNo(const std::string& entered)
{
    if(entered.size() != 1)
        throw std::invalid_argument("Entered value is neither a Y or an N.");
    char value = tolower(entered[0]);
    if(value != 'y' && value != 'n')
        throw std::invalid_argument("Entered value is neither a Y or an N.");
    return value == 'y';
}