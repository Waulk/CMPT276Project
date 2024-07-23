/***********************************************
 * Module: productrelease.h
 * 
 * Code Version History: 
 * Ver. 3: - 2024-07-12 Edited by Maki Hosokawa
 *         - Removed isValid() and adjust comments for the costructors
 * Ver. 2: - 2024-07-02 Edited by Jayden Brown
 *         - Updated the prototypes to handle UI internally.
 * Ver. 1: - 2024-06-28 Original by Maki Hosokawa
 *         - Initial version 
 ***********************************************/

/***********************************************
 * The ProductRelease class provides the name of the product.
 * You must call the constructor ProductRelease() or ProductRelease(char *productName, char *releaseId, char *date) before you can use this class.
***********************************************/

#ifndef PRODUCTRELEASE_H
#define PRODUCTRELEASE_H
#include <iostream>
#include <fstream>
#include "product.h" // Required for "PRODUCTNAMESIZE"
using std::string;

class ProductRelease
{
    public:
        // size of date
        static const int DATESIZE = 10;

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
        * If these preconditions are not met, it will create a ProductRelease object with invalid name
        */

       /***********************************************/
       static ProductRelease createNewProductRelease(
            string productName      // string productName - the name of the product we're getting the release for (in)
       );
       // Returns: The new ProductRelease created by prompts
       /* Prompts the user to create a new Product Release
       *  Handles UI and interactions until a new ProductRelease is created.
       * ---------------------------------------------
       * Precondition: productName must be a valid product within the system.
       */

       /***********************************************/
       static ProductRelease getProductReleaseFromUser(
            string productName      // string productName - the name of the product we're getting the release for (in)
       );
       // Returns: A ProductRelease from the user's selection
       /* Prompts the user for a Product Release for a specific Product
       *  It displays up to 20 product releases per page from the local file.
       *  If there are more than 20 product releases, it includes buttons to move to the next or previous set of 20 product releases.
       * ---------------------------------------------
       * Precondition: productName must be a valid product within the system.
       * * Example UI:
        *   =======Release=======
            SELECTION  RELEASE   DATE    
            ---------  --------  --------            
                1)  xxxxxxxx  dddd-dd-dd
                2)  1.19.1    2024-09-04
                ...
                19)  1.20.6    2025-01-10
                20)  1.25.93   2028-09-06
                                <-P  N->
            Make a Selection:
       *
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
        static ProductRelease readFromFile(
            bool &isEnd    // bool &notEnd - indicates whether it has reached to the end of the file. True if it has reached the end, false otherwise (out)
        );
        // Returns: ProductRelease - the ProductRelease from the file
        /* This function read and return the ProductRelease from the file
         * ---------------------------------------------
         * Precondition: file is properly open
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
        static bool writeToFile(
            ProductRelease productRelease     // product to add to the file (in)
        );
        // Returns: bool - return true if writing to the file succeed, false otherwise
        /* This function write a ProcutRelease to the file
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
       static bool openProductReleaseFile();
       // Returns: bool - return true if the file got opened successfully, false otherwise
        /* This function opens the file and creates a new one if it does not already exist
        */

       /***********************************************/
       static bool closeProductReleaseFile();
       // Returns: bool - return true if the file got closed successfully, false otherwise
        /* This function closes the file
         * ---------------------------------------------
         * Precondition: The file to get closed exists
         * If this precondition is not met, it will display an error message and throw an exception
        */

       /***********************************************/
       static bool productReleaseExists(ProductRelease input);
       // Returns: bool - return true if there exists a product with the name and releaseID
        /* This will search through the file to check if a product exists for entity integrity
         * ---------------------------------------------
         * Precondition: The file is open and valid
        */

       static bool isNumber(const std::string& s);

    private:
        // char[] - name of the product. Fixed length (Fixed Length: 10 chars)
        char productName[Product::PRODUCTNAMESIZE + 1];

        // char[] - the ID of the release version. Fixed length (Fixed Length: 8 chars)
        char releaseId[IDSIZE + 1];

        // char[] - Release date. The format must be YYYY-MM-DD (Fixed Length: 10 chars)
        char date[DATESIZE + 1]; 

        // fstream - File to save ProductRelease objects
        inline static std::fstream file;
        
        
};

#endif

