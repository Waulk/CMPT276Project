/***********************************************
 * Module: productrelease.h
 * 
 * Code Version History: 
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The ProductRelease class provides the name of the product.
 * You must call the constructor ProductRelease() or ProductRelease(char *productName, char *releaseId, char *date) before you can use this class.
***********************************************/

/***********************************************
 * #ifndef PRODUCTRELEASE_H
 * #define PRODUCTRELEASE_H
 * #include <iostream>
 ***********************************************/


class ProductRelease
{
    public:
        /***********************************************/
        ProductRelease();
        // Returns: None since this is a constructor
        /* This is a constructor of ProductRelease
        *  This constructor initializes productName with nullptr

        /***********************************************/
        ProductRelease(
            char *productName,
            char *releaseId,
            char *date
        );
        // Returns: None since this is a constructor
        /* This is a constructor of ProductRelease
        *  This constructor initializes productName with nullptr

        /***********************************************/
        // Functions:
        // getters, setters, 3 user interfaces, print a product name
        

    private:
        // char[] - name of the product. Fixed length (10 char)
        char *productName; 

        // char[] - the ID of the release version. Fixed length (8 char)
        char *releaseId;

        // char[] - Release date. The format must be YYYY-MM-DD
        char *date; //10char
};

/***********************************************

=======Product=======
SELECTION  PRODUCT     
---------  -------                              
       1)  xxxxxxxxxx
       2)  Sea Water
       ...
      19)  Canvas
      20)  ProdMan
                       <-P X N->
Make a Selection:
X


=====New Product=====
Enter the Product Name (max 10 char.):
User Input: NetScape


=====New Release=====
Enter Release Date (YYYY-MM-DD):
2User Input: 2024-06-19

Enter Release Version (max 8 char.):
1.19.1

***********************************************/