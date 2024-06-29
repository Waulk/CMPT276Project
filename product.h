/***********************************************
 * Module: product.h
 * 
 * Code Version History: 
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Product class provides name of the product.
 * You must call the constructor Product() or Product(string productName) before you can use this class.
***********************************************/

/***********************************************
 * #ifndef PRODUCT_H
 * #define PRODUCT_H
 * #include <iostream>
 * using namespace std;
 ***********************************************/

#include <iostream>
using namespace std;

class Product
{
    public:
        /***********************************************/
        Product();
        // Returns: None since this is a constructor
        /* This is a constructor of Product
        *  This constructor initializes productName with a null character 

        /***********************************************/
        Product(
            string productName  // string productName - a name to assign the product (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Product
       
        /***********************************************/
        string getProductName();
        // Returns: string - productName of the Product
        /* This is a getter of productName

        /***********************************************/
        void setProductName(
            string productName  // string productName - a name to assign the product (in)
        );
        // Returns: void
        /* This is a setter of productName
         * It assigns the parameter value to the productName

        /***********************************************/
        void printProductName();
        // Returns: void
        /* This functions print the product name

        /***********************************************/
        void displayProductUI();
        // Returns: void
        /* Write a detailed description of what the function does.
        * This function displays a user interface to show a list of products.
        * t displays up to 20 products on each page.
        * If there are more than 20 products, it includes buttons to move to the next or previous set of 20 products.
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
        *              <-P  N->
        * Make a Selection:
        */
       
    private:
        // char[] - name of the product. Fixed length (10 char)
        char productName[SIZE];

        // size of product name
        static const SIZE = 10;

};

