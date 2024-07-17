/***********************************************
 * Module: userinterface.h
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-14 Updated by Jayden Brown
 *         - Added a member to track if the main menu should loop
 *         - Removed several functions that were deemed as unrequired
 * Ver. 1: - 2024-07-02 Original by Jayden Brown
 *         - Initial version
 ***********************************************/

/***********************************************
 * The UserInterface class will handle basic prompts for the main menu 
 * but delegate other tasks to each module when required.
 * There should only ever be one instance of this class.
***********************************************/

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iostream>
#include <vector>

class UserInterface
{
    public:
        /***********************************************/
        UserInterface();
        // Returns: None since this is a constructor
        /* This is a constructor of UserInterface
        */

       /***********************************************/
        void runMainMenu();
        // Returns: void
        /* Handles the main loop for the User Interface which includes the main menu.
        *  This will only return if the user selects to exit the program.
        *  Should only be run once, and if it returns should not be ran again.
        */

        /***********************************************/
        static bool isEnteredValid(
            int entered,                    // int entered - the value that the user entered which needs to be verified as valid (in)
            int minimum,                    // int minimum - the minimum value that will be allowed when a number is entered (in)
            int maximum                     // int maximum - the maximum value that will be allowed when a number is entered (in)
        );
        // Returns: True if the entered value is between minimum and maximum (inclusive), false otherwise
        /* This method determines if an entered value between two numbers.
        */

        /***********************************************/
        static bool isEnteredValid(
            const std::string& entered,     // std::string& entered - a constant reference to a string to be verified (in)
            int minLength,                  // int minLength - the minimum allowable length of the string (in)
            int maxLength                   // int maxLength - the maxLength allowable length of the string (in)
        );
        // Returns: True if the length of the entered value is between minLength and maxLength (inclusive), false otherwise
        /* This method determines if an entered string has the length between two values.
        */

        /***********************************************/
        static bool isYesOrNo(
            const std::string& entered      // std::string& entered - a constant reference to a string that must be in the format of 'Y' or 'N' (in)
        );
        // Returns: True if the string == 'Y' and false if the string == 'N'
        // Exception: If the string is neither 'Y' or 'N' an "std::invalid_argument" exception is thrown.
        /* This method determines if an entered string is a yes or a no for a (Y/N) question.
        */

    private:

        // Whether the main menu should keep running or exit and return.
        bool m_bRunMenu = true;
};

#endif