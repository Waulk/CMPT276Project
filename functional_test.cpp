#include <iostream>
#include <string>
#include "reporter.h"

using namespace std;

// Function declarations
void mainMenu();
void addCustomer();
bool isValidPhoneNumber(const string &phoneNumber);

int main() {
    // Start the program and show the main menu
    mainMenu();
    return 0;
}

void mainMenu() {
    int selection = 0;

    while (true) {
        cout << "======Main Menu======" << endl;
        cout << "1) Add Issue" << endl;
        cout << "2) Changes" << endl;
        cout << "3) Customers" << endl;
        cout << "4) Add Product Release" << endl;
        cout << "5) Exit" << endl;

        //cout << "Enter your selection (1-5): "; 
        //Not taking input here for the purpose of testing
        cout << "Choosing selection 3.";
        selection = 3;

        switch (selection) {
            case 1:
                // Add Issue functionality (not implemented in this test case)
                break;
            case 2:
                // Changes functionality (not implemented in this test case)
                break;
            case 3:
                // Add a new customer
                addCustomer();
                break;
            case 4:
                // Add Product Release functionality (not implemented in this test case)
                break;
            case 5:
                // Exit the program
                return;
            default:
                cout << "Invalid selection. Please enter a number between 1 and 5." << endl;
        }
    }
}

//method to create new customers and add them to the file
void addCustomer() {
    string email, name, phoneNumber;
    
    cout << "=====New Customer====" << endl;
    //prompt user for email
    cout << "Enter the Customer's Email (max 24 char.): ";
    cin >> email;
    //prompt user for name
    cout << "Enter the Customer's Name (max 30 char.): ";
    cin.ignore();
    getline(cin, name);
    //prompt user for phone number
    cout << "Enter the Customer's Phone Number (10-11 digits): ";
    cin >> phoneNumber;
    //if phone number is not valid, continue requesting phone number
    bool isValid = isValidPhoneNumber(phoneNumber);
    while (isValid) {
        cout << "Error! Invalid phone number." << endl;
        cout << "Enter the Customer's Phone Number (10-11 digits): ";
        cin >> phoneNumber;
        isValid = isValidPhoneNumber(phoneNumber);
    }
    //create new reporter object using provided information
    Reporter *reportObj = new Reporter(email, name, phoneNumber);

    if(reportObj->checkEmail(reportObj->getEmail())){
        cout << "Customer added successfully, email found!" << endl;
    }
}

//method for determing if a phone number is valid
bool isValidPhoneNumber(const string &phoneNumber){
    if (phoneNumber.empty() || phoneNumber.size() > 11 + 1){
        return false;
    }
    return true;
}
