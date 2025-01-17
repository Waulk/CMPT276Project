/***********************************************
 * Module: main.cpp
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-15 Edited by Maki Hosokawa
 *         - Added the convention for commenting in a cpp file
 * Ver. 1: - 2024-07-02 Original by Jayden Brown
 *         - Initial version
 ***********************************************/

/***********************************************
 * Main handles startup and shutdown, and its main purpose is initializing the UserInterface.
***********************************************/

#include <iostream>
#include "userinterface.h"

int main()
{
    // Initialize the UserInterface and run the Main Menu
    UserInterface userInterface;
    userInterface.runMainMenu();
    return 0;
}

/***********************************************
 * Coding Conventions

/***********************************************
 * Module: main.h
 * 
 * Code Version History: (The latest top and the oldest bottom)
 * Ver. 2: - 2024-07-10 Modified by John Smith
 *         - Explanation of modification(s). If there is more than one modification, put each on a separate line.
 *         - Ex1: Added function X
 *         - Ex2: Modified the parameters of function Y
 * Ver. 1: - 2024-06-26 Original by Sophia Brown
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Write the purpose of the class/module.
 * Example: This class provides examples of different types of reference parameters: input (in), output (out), and input/output (in/out).
 * The purpose is to establish a coding convention for the team, ensuring consistency in the implementation and documentation of functions.
 * 
 * Below is the instructions/tips from Assignment 3 instruction paper:
 * It is important to state the nature of the cohesion of the module or the nature of (not implementation of) the data or control abstraction retained by/hidden in the module. You may also mention any general rules as to how the module should be used. e.g. "You must call CreateStack() before you can use a stack"
***********************************************/

/***********************************************
 * Header Guards/Include Statements/Using Directive go here
 * Example:
 * #ifndef MAIN_H
 * #define MAIN_H
 * #include <iostream>
 * #include "example.h"
 * using std::string;
 ***********************************************/

class Group22 
{
    public:
    /***********************************************
    * Rules for Reference Parameters
    * When a function parameter is pass-by-value, denote it as 'in'.
    * Whenever possible, use reference syntax rather than pointers for out and in/out parameters.
    * That is, use 'function(int& a)' instead of 'function(int* a)' when possible.
    * ---------------------------------------------
    * in       - Parameter is passed by reference WITH the 'const' keyword. 
    *          - The function only reads the value of the parameter and does NOT modify the parameter.
    * 
    * out      - Parameter is passed by reference without the 'const' keyword.
    *          - The function does NOT read the value of the parameter and completely overwrites/modifies the parameter.
    * 
    * in/out   - Parameter is passed by reference without the 'const' keyword. 
    *          - The function reads the value of the parameter, utilizes the value in some way, and modifies the parameter.
    ***********************************************/


    /***********************************************
    * Rules for name, capitalization, indentation, and positioning
    * ---------------------------------------------
    * Function Names: Use Camelcase. The first character in the function name must be in lower case.
    * Example: countVowels
    * ---------------------------------------------
    * Class Names: Use Pascalcase. The first character in the class name must be in upper case.
    * Example: ExampleClassName
    * ---------------------------------------------
    * Variable Names: Use Camelcase. The first character in the variable name must be in lower case.
    * Examples: int numOfExample;
    *           int num;
    * ---------------------------------------------
    * Constant Variables: Use uppercase letters for all characters in constant variable names.
    * Example: const COLOR;
    * ---------------------------------------------
    * File Name: Use lowercase letters for all characters in file name.
    *            If necessary, use '-'.
    * Examples: filename.h / filename.cpp / long-filename.h
    * ---------------------------------------------
    * Indentation and Spacing
    * Indentation: Use a tab size of 4.
    * Spacing: Surround '=' with spaces. 
    * Place a space after ','
    * Do NOT place a space before ';'.
    * Good Examples: int num = 1;
    *                int addNums(int a, int b);
    * Bad Examples:  int num=1 ;
    *                int addNums(int a,int b) ;
    * ---------------------------------------------
    * Position of Opening/Closing Braces 
    * Opening and closing braces must be on their own lines.
    * Good Example:
    int divideIntegers(int a, int b) 
    {
        // implementation
    }

    * Bad Example:
    int divideIntegers(int a, int b) {
        // implementation
    }
    /***********************************************/


    /***********************************************/
    int divideIntegers(
        int a,   // int a - dividend. i.e. the number to be divided (in)
        int b    // int b - divisor. i.e. the number by which the dividend is to be divided (in)
    );
    // Returns: int - The quotient of the division of a by b.
    /* Write a detailed description of what the function does.
    * Example: This function takes two integers (a and b) as inputs, divides a by b, and returns the quotient.
    * ---------------------------------------------
    * Precondition: This section is optional. Example: b != 0
    * Explain what will happen if precondition is not met
    * Example: If this precondition is not met, division by zero will occur, leading to a runtime error.
    
    /***********************************************/
    int countVowels(
        const std::string &str   // string& str -  a constant reference to the input string whose vowels need to be counted (in)
    );
    // Returns: int - the number of vowels in the input string
    /* Brief description of what the function does.
    * Example: This function takes a string parameter by constant reference and counts the number of vowels in the string.
    * ---------------------------------------------
    * Precondition: This section is optional. Ex: str is NOT an empty string
    * Explain what will happen if precondition is not met
    * Example: If this precondition is not met, the function will return -1 to indicate an error.

    /***********************************************/
    void initializeChar(
        char &charPtr   // char& charPtr - a reference to a char that will be set to 'A' (out)
    );
    // Returns: void
    /* Brief description of what the function does.
    * Example: This function assigns the character 'A' to the provided char reference.

    /***********************************************/
    void initializeOne(
        int *arr,    // a pointer to an array of integers (out)
        int n        // the number of elements in the array  (in)
    );
    // Returns: void
    /* Brief description of what the function does.
    * Example: This function assigns the value '1' to all elements in the provided array.
    
    /***********************************************/
    void multiplyByTwo(
        double &num    // a reference to the double value that needs to be multiplied by 2 (in/out)
    );
    // Returns: void
    /* Brief description of what the function does.
    * Example: This function takes a double parameter by reference and multiply it by 2.
    * The result of multiplication will be stored in the parameter.
    */
  
    private:
        // description of CAPACITY
        const int CAPACITY = 1;

        // description of name
        char *name;

};

//#endif

// Below is the convention for commenting in a C++ file
/***********************************************/
void getProductFromUser(bool createNew)
/*
 * This function interacts with the user to display a list of products and 
 * allows the user to select one. It handles pagination to display products 
 * in chunks of 20 per page. If createNew is true, the user has the option 
 * to create a new product.
 * 
 * Implementation Details:
 * - Initializes control variables for pagination and user input handling.
 * - Uses a while loop to continuously interact with the user until they exit.
 * - Seeks to the beginning of the file and skips products from previous pages 
 *   to display the current page's products.
 * - Displays the products for the current page and handles user input for 
 *   pagination or selection.
 * - If the user selects a valid product number, the function seeks the 
 *   corresponding position in the file and reads the product.
 */
{
    // function implementation.....
}