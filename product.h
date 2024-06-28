/***********************************************
 * Module: product.h
 * 
 * Code Version History: 
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The Product class provides name of the product.
 * You must call the constructor Product() or Product(char *productName) before you can use this class.
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
        *  This constructor initializes productName with nullptr
   
        /***********************************************/
        Product(
            char *productName
        );
        // Returns: None since this is a constructor
        /* This is a constructor of Product
        *  This constructor initializes productName with nullptr
        */

       // getters, setters, user interface, pring product name


    private:
        const int SIZE = 20;
        char productName[SIZE];

};

/***********************************************
UI for Product

=======Product=======
SELECTION  PRODUCT     
---------  -------                              
       1)  xxxxxxxxxx
       2)  Sea Water
       ...
      19)  Canvas
      20)  ProdMan
                       <-P  N->
Make a Selection:


***********************************************/