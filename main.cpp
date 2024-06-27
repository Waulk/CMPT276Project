/***********************************************
 * Module: main.h
 * 
 * Code Version History:
 * Ver. 2: - 2024-07-10 Modified by John Smith
 *         - Explanation of modification(s). If there is more than one modification, put each on a separate line.
 *         - Ex1: Added function X
 *         - Ex2: Modified the parameters of function Y
 * Ver. 1: - 2024-06-26 Original by Sophia Brown
 *         - Initial version 
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


    // The below is an example of an IN parameter (pass-by-value)
    /***********************************************
    * Function Name : divideIntegers
    * ---------------------------------------------
    * Write a detailed description of what the function does.
    * Example: This function takes two integers (a and b) as inputs, divides a by b, and returns the quotient.
    * ---------------------------------------------
    * Input: int a - dividend. i.e. the number to be divided (in)
    *        int b - divisor. i.e. the number by which the dividend is to be divided (in)
    * Output: int - The quotient of the division
    * ---------------------------------------------
    * Precondition: This section is optional. Ex: b != 0
    ***********************************************/
    int divideIntegers(int a, int b) 
    {
        // Use tab size 4 for indentation.
        // Opening/Closing braces must be on a line by themselves.
    }


    // The below is an example of an IN reference parameter 
    /***********************************************
    * Function Name: countVowels
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function takes a string parameter by constant reference and counts the number of vowels in the string.
    * ---------------------------------------------
    * Input: string& str -  a constant reference to the input string whose vowels need to be counted (in)
    * Output: int - the number of vowels in the input string
    ***********************************************/
    int countVowels(const string& str) 
    {   
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
    }


    // The below is an example of an OUT reference parameter with reference syntax
    /***********************************************
    * Function Name: initializeChar
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function assigns the character 'A' to the provided char reference.
    * ---------------------------------------------
    * Input: char& charPtr - a reference to a char that will be set to 'A' (out)
    * Output: void
    ***********************************************/
    void initializeChar(char& charPtr) 
    {
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
    }


    // The below is an example of an OUT reference parameter with pointer
    /***********************************************
    * Function Name: initializeOne
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function assigns the value '1' to all elements in the provided array.
    * ---------------------------------------------
    * Input: int* arr - a pointer to an array of integers (out)
    *        int n - the number of elements in the array  (in)
    * Output: void
    ***********************************************/
    void initializeOne(int* arr, int n) 
    {
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
    }


    // The below is an example of an IN/OUT reference parameter with reference syntax
    /***********************************************
    * Function Name: multiplyByTwo
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function takes a double parameter by reference and multiply it by 2.
    * The result of multiplication will be stored in the parameter.
    * ---------------------------------------------
    * Input: double& num - a reference to the double value that needs to be multiplied by 2 (in/out)
    * Output: void
    ***********************************************/
    void multiplyByTwo(double& num) 
    {
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
    }


    private:
        /***********************************************
        * Private data members go here
        ***********************************************/
        const int capacity;
        char* name;

};

//#endif