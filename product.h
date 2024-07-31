/***********************************************
 * Module: product.h
 * 
 * Code Version History: 
 * Ver. 3: - 2024-07-12 Edited by Maki Hosokawa
 *         - Removed isValid()
 *         - adjust comments for the costructors
 *         - moved setProductNameUI() from productrelease.h
 * Ver. 2: - 2024-07-02 Edited by Jayden Brown
 *         - Updated the prototypes to handle UI internally.
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version
 ***********************************************/

/***********************************************
 * The Product class provides name of the product.
 * You must call the constructor Product() or Product(string productName) before you can use this class.
***********************************************/

#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <fstream>
using std::string;

class Product
{
    public:
        // Size of product name
        static const int PRODUCTNAMESIZE = 10;

    public:
        /***********************************************/
        Product();
        // Returns: None since this is a constructor
        /* This is a constructor of Product
        *  This constructor initializes productName with a null character 

        /***********************************************/
        Product(
            string name  // string productName - a name to assign the product (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Product
        * ---------------------------------------------
        * Precondition: 
        * productName != "" (empty string). The max length of productName is 10. 
        * If these preconditions are not met, it will create a Product object with invalid name
       
        /***********************************************/
        string getProductName();
        // Returns: string - productName of the Product
        /* This is a getter of productName

        /***********************************************/
        void setProductName(
            const string &name  // string name - a name to assign the product (in)
        );
        // Returns: void
        /* This is a setter of productName
         * It assigns the parameter value to the productName
         * ---------------------------------------------
         * Precondition: productName != "" (empty string). The max length of productName is 10.
         * If this precondition is not met, it will display an error message and return the function 
         * WITHOUT assigning the parameter value to the productName

        /***********************************************/
        void printProductName();
        // Returns: void
        /* This functions print the product name

        /***********************************************/
        static Product getProductFromUser(
            bool createNew = false  // bool createNew - If the User Interface should allow a user to create a new Product (in)
        );
        // Returns: Product - the Product from the user's selection. It throws an out_of_range exception if user selects invalid number.
        /* This function displays a user interface for the selection of a product.
        *  It displays up to 20 products per page from the local file.
        *  If there are more than 20 products, it includes buttons to move to the next or previous set of 20 products.
        * It does NOT display 'X' when createNew == false.
        * 
        * Example UI:
        * =======Product=======
        * SELECTION  PRODUCT     
        * ---------------------                              
        * 1)  xxxxxxxxxx
        * 2)  Sea Water
        *  ...
        * 19)  Canvas
        * 20)  ProdMan
        *             <-P X N->
        * Make a Selection:
        */

       /***********************************************/
        static Product setProductNameUI();
        // Returns: Product
        /* This function displays an UI to prompt a user to enter a product name
        * Example UI:
        * =====New Product=====
        * Enter the Product Name (max 10 char.):
        */

       /***********************************************/
        static Product readFromFile(
            bool &isEnd    // bool &notEnd - indicates whether it has reached to the end of the file. True if it has reached the end, false otherwise (out)
        );
        // Returns: Product - the Product from the file
        /* This function read and return the Product from the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
        static bool writeToFile(
            Product product     // product to add to the file (in)
        );
        // Returns: bool - return true if writing to the file succeed, false otherwise
        /* This function write a Procut to the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool seekToBeginningOfFile();
        // Returns: bool - return true if reached to the beginning of file successfully, false otherwise
        /* This function rewinds to the beginning of the file 
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool openProductFile(
            string path     // path for the new technovo/products.bin file
       );
       // Returns: bool - return true if the file got opened successfully, false otherwise
        /* This function opens the file and creates a new one if it does not already exist
        */

       /***********************************************/
       static bool closeProductFile();
       // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file is already open
         * If this precondition is not met, it will display an error message and throw an exception

       /***********************************************/
       static bool isNumber(
            const string& s // string to check if this is a number (in)
        );
       // Returns: bool - returns true if the string consists entirely of numeric digits, false otherwise
        /* This function checks if the input string is a number
        * ---------------------------------------------
        * Precondition: The input string is provided
        * This function iterates over each character in the string and uses std::isdigit to check if it is a digit. 
        * If any character is not a digit, it returns false; otherwise, it returns true.
        */
       
    private:
        // char[] - name of the product. Fixed length (10 char)
        char productName[PRODUCTNAMESIZE + 1];

        // fstream - File to save Product objects
        inline static std::fstream file;

};

#endif
