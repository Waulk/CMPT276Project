/***********************************************
 * Module: productrelease.h
 * 
 * Code Version History: 
 * Ver. 2: - 2024-07-02 Edited by Jayden Brown
 *         - Updated the prototypes to handle UI internally.
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * Example: The ProductRelease class provides the name of the product.
 * You must call the constructor ProductRelease() or ProductRelease(char *productName, char *releaseId, char *date) before you can use this class.
***********************************************/

#ifndef PRODUCTRELEASE_H
#define PRODUCTRELEASE_H
#include <iostream>
using std::string;

class ProductRelease
{
    public:
        // size of productName and date
        static const int NAMEDATESIZE = 10;

        // size of releaseId
        static const int IDSIZE = 8;
    public:
        /***********************************************/
        ProductRelease();
        // Returns: None since this is a constructor
        /* This is a constructor of ProductRelease
        *  This constructor initializes productName with nullptr

        /***********************************************/
        ProductRelease(
            string productName,     // string productName - a name to assign the product (in)
            string releaseId,       // string releaseId - a releaseId of the product (in)
            string date             // string date - a release date of the product (in) (Format: YYYY-MM-DD) (in)
        );
        // Returns: None since this is a constructor
        /* This is a constructor of ProductRelease
        *  This constructor initializes productName, releaseId, and date
        * ---------------------------------------------
        * Precondition: 
        * productName != "" (empty string). The max length of productName is 10.
        * releaseId != "" (empty string). The max length of releaseId is 8.
        * The date format must be YYYY-MM-DD. 
        *   Specifically:
        *   - The year is in the format "2024" or "1990", NOT "24" or "90".
        *   - The month is in the format of "11" for November or "01" for January, NOT "1" for January.
        *   - The date is in the format of "25" for the 25th or "03" for the 3rd, NOT "3" for the 3rd. 
        * If these preconditions are not met, it will throw an exception with an error message
        */

       /***********************************************/
       static ProductRelease createNewProductRelease(
            string productName      // string productName - the name of the product we're getting the release for
       );
       // Returns: The new ProductRelease created by prompts
       /* Prompts the user to create a new Product Release
       *  Handles UI and interactions until a new ProductRelease is created.
       * ---------------------------------------------
       * Precondition: productName must be a valid product within the system.
       */

       /***********************************************/
       static ProductRelease getProductReleaseFromUser(
            string productName      // string productName - the name of the product we're getting the release for
       );
       // Returns: A ProductRelease from the user's selection
       /* Prompts the user for a Product Release for a specific Product
       *  It displays up to 20 product releases per page from the local file.
       *  If there are more than 20 product releases, it includes buttons to move to the next or previous set of 20 product releases.
       * ---------------------------------------------
       * Precondition: productName must be a valid product within the system.
       */

        /***********************************************/
        string getProductName();
        // Returns: string - productName of the Product
        /* This is a getter of productName
        */

        /***********************************************/
        string getReleaseId();
        // Returns: string - releaseId of the Product
        /* This is a getter of releaseId
        */

        /***********************************************/
        string getDate();
        // Returns: string - release date of the Product
        /* This is a getter of release date
        */

        /***********************************************/
        void setProductName(
            const string &productName  // string productName - a name to assign the product (in)
        );
        // Returns: void
        /* This is a setter of productName
        * It assigns the parameter value to the productName
        * ---------------------------------------------
        * Precondition: productName != "" (empty string). The max length of productName is 10.
        * If this precondition is not met, it will display an error message and return the function 
        * WITHOUT assigning the parameter value to the productName
        */
        
        /***********************************************/
        void setReleaseId(
            const string &releaseId    // string releaseId - a releaseId of the product (in)
        );
        // Returns: void
        /* This is a setter of releaseId
        * It assigns the parameter value to the releaseId.
        * ---------------------------------------------
        * Precondition: releaseId != "" (empty string). The max length of releaseId is 8.
        * If this precondition is not met, it will display an error message and return the function 
        * WITHOUT assigning the parameter value to the releaseId
        */

        /***********************************************/
        void setDate(
            const string &date     // string date - a release date of the product (in) (Format: YYYY-MM-DD)
        );
        // Returns: void
        /* This is a setter of productName
        * It assigns the parameter value to the productName
        * ---------------------------------------------
        * Precondition: 
        * The date format must be YYYY-MM-DD. 
        *   Specifically:
        *   - The year is in the format "2024" or "1990", NOT "24" or "90".
        *   - The month is in the format of "11" for November or "01" for January, NOT "1" for January.
        *   - The date is in the format of "25" for the 25th or "03" for the 3rd, NOT "3" for the 3rd. 
        * If these preconditions are not met, it will display an error message and return the function 
        * WITHOUT assigning the parameter values to the date.
        */
        
        /***********************************************/
        void printProductName();
        // Returns: void
        /* This function prints the product name
        */

        /***********************************************/
        void printProductName();
        // Returns: void
        /* This function prints the product name
        */

        /***********************************************/
        void setProductNameUI();
        // Returns: void
        /* This function displays an UI to prompt a user to enter a product name
        * Example UI:
        * =====New Product=====
        * Enter the Product Name (max 10 char.):
        */
        
        /***********************************************/
        void setDateUI();
        // Returns: void
        /* This function displays an UI to prompt a user to enter a release date of the product
        * Example UI:
        * =====New Release=====
        * Enter Release Date (YYYY-MM-DD):
        */
        
        /***********************************************/
        void setReleaseIdUI();
        // Returns: void
        /* This function displays an UI to prompt a user to enter a release ID of the product
        * Example UI:
        * =====New Release=====
        * Enter Release Version (max 8 char.):
        */

        /***********************************************/
        bool isValid();
        // Returns: True if the ProductRelease is valid and was created properly, False otherwise
        /* This function determines if a generated ProductRelease from functions such as createNewProductRelease
        * and getProductReleaseFromUser were generated correctly
        */

    private:
        // char[] - name of the product. Fixed length (Fixed Length: 10 chars)
        char productName[NAMEDATESIZE];

        // char[] - the ID of the release version. Fixed length (Fixed Length: 8 chars)
        char releaseId[IDSIZE];

        // char[] - Release date. The format must be YYYY-MM-DD (Fixed Length: 10 chars)
        char date[NAMEDATESIZE]; 
        
        
};

#endif

