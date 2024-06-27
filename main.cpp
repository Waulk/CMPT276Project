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
 * Include statements go here
 * Example:
 * #include <iostream>
 * #include "example.h"
 ***********************************************/


class Group22 
{
    /***********************************************
    * Rules for Reference Parameters
    * These rules only apply when a function parameter is pass-by-reference.
    * There is no need to specify when a function parameter is pass-by-value.
    * ---------------------------------------------
    * in       - Parameter is passed by reference with the 'const' keyword. 
    *          - The function should NOT modify the parameter.
    *          - The caller function is responsible for deleting the object when memory reallocation is needed.
    * 
    * out      - Parameter is passed by reference WITHOUT the 'const' keyword.
    *          - The function must modify the parameter.
    *          - If the function needs to modify the parameter by creating a new object and making the parameter pointer point to that new object, 
    *            the called function is responsible to reallocate the memory of the original object if needed.
    *          - The caller function is responsible for deleting the object when memory reallocation is needed.
    * 
    * in/out   - Parameter is passed by reference. The parameter is whether nullptr or NULL.
    *          - The function must fill out the parameter.
    *          - The caller function is responsible for deleting the object when memory reallocation is needed.
     ***********************************************/

    
    /***********************************************
    * Function Name : addTwoNumbers
    * ---------------------------------------------
    * Write a detailed description of what the function does.
    * Example: This function takes two integers as inputs, adds them together, and return the result.
    * ---------------------------------------------
    * Input: int num1 - the first integer to be added
    *        int num2 - the second integer to be added
    * Output: int - the sum of num1 and num2
    ***********************************************/
    int addTwoNumbers(int num1, int num2) 
    {
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
        // Function implementation here
    }


    // The below is an example of an IN reference parameter 
    /***********************************************
    * Function Name: countVowels
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function takes a string parameter by constant reference and counts the number of vowels in the string.
    * ---------------------------------------------
    * Input: string str -  a constant reference to the input string whose vowels need to be counted (in)
    * Output: int - the number of vowels in the input string
    ***********************************************/
    int countVowels(const string& str) 
    {   
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
        // Function implementation here
    }


    // The below is an example of an OUT reference parameter 
    /***********************************************
    * Function Name: multiplyByTwo
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function takes a double parameter by reference and multiply it by 2.
    * ---------------------------------------------
    * Input: double& num - a reference to the double value that needs to be multiplied by 2 (out)
    * Output: void
    ***********************************************/
    void multiplyByTwo(double& num) 
    {
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
        // Function implementation here
    }


    // The below is an example of an IN/OUT reference parameter 
    /***********************************************
    * Function Name: initializeChar
    * ---------------------------------------------
    * Brief description of what the function does.
    * Example: This function takes a nullptr by reference. 
    * the function allocates memory for the char and sets its value to a specified character.
    * ---------------------------------------------
    * Input: char*& charPtr - a reference to a pointer to a char that needs to be initialized (in/out)
    * Output: void
    ***********************************************/
    void initializeChar(char*& charPtr) 
    {
        // See "Rules for Reference Parameters" in the beginning of class Group22
        // Use tab size 4 for indentation
        // Opening/Closing braces must be on a line by themselves
        // Function implementation here
    }

};


// memo: Check lists, prrofread