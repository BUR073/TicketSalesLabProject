#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define DISCOUNT_MIN_AGE 18

#define DISCOUNT_MAX_AGE 25
#define DISCOUNT_PERCENTAGE 0.20f // this means 20%
#define MAX_SALES 10

#define TRUE 1 // ditto
#define FALSE 0 // ditto

char *getDate() {
   // get current time
   time_t now = time(NULL);
   // convert to time that is more readable by humans
   // and store in a struct to make each element accessible
   struct tm *t = localtime(&now);
   // declare static char arr to store date
   static char date_string[11];

   // Format the date string using printf
   // - %02d: Format two-digit day
   // - %02d: Format two-digit month
   // - %04d: Format four-digit year
   sprintf(date_string, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
   // return the date
   return date_string;
}


// Function that will return the index of the model requested in the carModelAvailable array
unsigned short getModelIndex(const char *modelChoice, char *carModelsAvailable[], int numberOfModels) {
   // start loop from 0 to the number Of models which is 5
   for (int i = 0; i < numberOfModels; i++) {
       if (strcmp(modelChoice, carModelsAvailable[i]) == 0) { // If the model is found then return i - the index
           return i;
       }
   }
   // this return will never be used but its stops an error as the function has to always return a value
   return 0;
}



// The function to view all sales
void menu_viewSales(const int SalesData_numberOfSales, const float SalesData_totalSalePrice[], char SalesData_customerNames[][201],
                   const unsigned short SalesData_carsSold, char SalesData_carModelsSold[MAX_SALES][201],
                   int numberOfModels, int yearOfManufactureByModel[], char SalesData_dates[MAX_SALES][11],
                   int SalesData_unitsSoldBySale[MAX_SALES], char SalesData_discountGiven[MAX_SALES][6]) {



   char *carModelsAvailable[] = {"BMW", "Audi", "VW", "Mercedes", "Bentley"};


   int carModelsAvailable_numberOfSales[] = {0, 0, 0, 0, 0};
   int carModelsAvailable_totalSalesValue[]  = {0, 0, 0, 0, 0};
   // These two arrays are going to be used to store the data for sales by model
   // the toal sales value per model and number of each model sold


   // If there are no sales
   if (SalesData_carsSold == 0) {
       printf("\nNo Sales to display");
   } else {
       // and if there are sales
       int SalesData_totalSalePriceValue = 0;
       // var that is going to be used to store the value of all the cars sold
       printf("\nIndividual Sales");
       printf("\n-------------------\n");

       // start a for loop that loops from 0 to the total number of sales
       for (int i = 0; i < SalesData_numberOfSales; i++) {

           // Call the getModelIndex function, this will return the index of the model in the carModelsAvailable
           // This will then be used so that I can correctly assign the value to the sales per model arrays
           int index = getModelIndex(SalesData_carModelsSold[i], carModelsAvailable, numberOfModels);

           // the reason there is an if statement is to make the sales data more readable
           // if there wasn't a discount given on the sale there is no need to show the discount value
           if (strcmp(SalesData_discountGiven[i], "FALSE") == 0) {
               // Print out the sales data in a readable way
               printf("Sale ID: %d | Sale Date: %s | Units Bought: %d | Sale Amount: %f | Discount Given: %s | Car Year: %d | Car Model: %s | Customer Name: %s\n",
                      i, SalesData_dates[i], SalesData_unitsSoldBySale[i], SalesData_totalSalePrice[i], SalesData_discountGiven[i], yearOfManufactureByModel[index],
                      SalesData_carModelsSold[i], SalesData_customerNames[i]);
           } else {
               // same as above but with the discount value
               printf("Sale ID: %d | Sale Date: %s | Units Bought: %d | Sale Amount: %f | Discount Given: %s | Discount Value: 20%% | Car Year: %d | Car Model: %s | Customer Name: %s\n",
                      i, SalesData_dates[i], SalesData_unitsSoldBySale[i], SalesData_totalSalePrice[i], SalesData_discountGiven[i], yearOfManufactureByModel[index],
                      SalesData_carModelsSold[i], SalesData_customerNames[i]);
           }



           // Add the value of the sale to totalSalePriceValue so that it is counted toward the value of total sales
           SalesData_totalSalePriceValue += (int)SalesData_totalSalePrice[i];

           // Add one to the number of sales for the particular model
           carModelsAvailable_numberOfSales[index] += 1;
           // Add the value of the sales to the total sales of the particular model
           carModelsAvailable_totalSalesValue[index] += (int)SalesData_totalSalePrice[i];

       }
       // here is were we are going to print out the sales data per model
       printf("\n\nSales Data by Model\n");
       printf("-------------------\n"); // Just to make it look more pretty
       // Loop from 0 to 5
       for (int i = 0; i < numberOfModels; i++) {
           printf("%d %s\n", yearOfManufactureByModel[i], &*carModelsAvailable[i]);
           printf("Units Sold: %d\n", carModelsAvailable_numberOfSales[i]);
           printf("Total Sales Value: %d\n\n", carModelsAvailable_totalSalesValue[i]);
       }


       // and print out the value of all the sales
       printf("\nTotal Sales Data\n\n");
       // also display some overall statistics
       printf("\n%hd cars have been sold with a total value of %d GBP.\n",
              SalesData_carsSold, SalesData_totalSalePriceValue);
   }


}

// Clear the screen, this does not work for me. All the other options do not work but this does in theory work
void clearScreen() {
   printf("\033[2J\033[H");
}





// Purchase confirmation printed out
void purchaseConfirmation (const short carsNeeded, const double totalPrice, const short carsAvailable) {
   printf("\n\nThank you.\n");
   printf("You have bought %hd cars.\n", carsNeeded);
   printf("Total cost is %f GBP.", totalPrice);
   printf("\n\nThere are %hd cars remaining.", carsAvailable);


}





// Display the menu
void menu_showMenu() {
   #define MENU_OPTION_BUY_CAR 'a'
   #define MENU_OPTION_VIEW_SALES 'b'
   #define MENU_OPTION_VIEW_CAR_STOCK 'c'
   #define MENU_OPTION_CUSTOMER_FEEDBACK 'd'
   #define MENU_OPTION_EXIT 'x'

   // Above is for readability

   // contains ANSI escape code which will make the words bold, just to make it look better
   printf("\n\033[1mWelcome to the Car Sales Office!\033[0m\n");
   // ANSI escape code to make text bold
   printf("---------------------------------\n");
   printf("%c. Buy Cars\n", MENU_OPTION_BUY_CAR);
   printf("----------------------\n");

   printf("%c. View Sales Data\n", MENU_OPTION_VIEW_SALES);
   printf("----------------------\n");

   printf("%c. View Car Stock\n", MENU_OPTION_VIEW_CAR_STOCK);
   printf("----------------------\n");

   printf("%c. Customer Feedback\n", MENU_OPTION_CUSTOMER_FEEDBACK);
   printf("----------------------\n");

   printf("%c. Exit\n", MENU_OPTION_EXIT);
   printf("----------------------\n");
   printf("\n");

   // prompt user for their choice
   printf("Please choose one: ");
}






void menu_displayCars(char *carModelsAvailable[], int numberOfCarsAvailable[], int carPriceByModel[], const int numberOfModels, int yearOfManufactureByModel[]) {
// This displays the cars using bubble sort to sort by year in descending order

   // Sort the cars by year of manufacture in descending order

   // Bubble Sort
   // Loop 1 i = 0, j = 4 - compare 01, 12, 23, 34
   // Loop 2 i = 1, j = 3 - compare 01, 12, 23
   // Loop 3 i = 2, j = 2 - compare 01, 12
   // Loop 4 i = 3, j = 1 - compare 01
   // End Loop
   // Where j is less than j+1 they are swapped, so after all the loops the arr will be sorted
   // Some AI help writing this algorithm - gemini
   for (int i = 0; i < numberOfModels - 1; i++) {
       // The outer loop - iterates from 0 to numberOfModels - 2

       for (int j = 0; j < numberOfModels - i - 1; j++) {

           // This inner loop iterates from 0 to numberOfModels - i - 2.
           // It's used to compare adjacent elements and swap them if necessary.

           // Check if the year of manufacture on the right is larger than the one on its left
           // If they are not then nothing happens and we move to compare the next values
           if (yearOfManufactureByModel[j] < yearOfManufactureByModel[j + 1]) {
               // if they are...
               // Swap the years
               int temp = yearOfManufactureByModel[j];
               // Create a temporary var and store the value on the left

               yearOfManufactureByModel[j] = yearOfManufactureByModel[j + 1];
               // Move the value of the right to the left

               yearOfManufactureByModel[j + 1] = temp;
               // and finally put the contents of the temp var (the value that was on the left) to the right

               // the 3 sections of code below are identical to what is above
               // the reasons we have to do this is to stop the data getting mixed up
               // as these are all parallel arrays


               // Swap the car models
               char *tempModel = carModelsAvailable[j];
               carModelsAvailable[j] = carModelsAvailable[j + 1];
               carModelsAvailable[j + 1] = tempModel;

               // Swap the prices
               int tempPrice = carPriceByModel[j];
               carPriceByModel[j] = carPriceByModel[j + 1];
               carPriceByModel[j + 1] = tempPrice;

               // Swap the number of cars available
               int tempNumCars = numberOfCarsAvailable[j];
               numberOfCarsAvailable[j] = numberOfCarsAvailable[j + 1];
               numberOfCarsAvailable[j + 1] = tempNumCars;
           }
       }
   }

   // Print the table header
   printf("\n+----------+----------+--------+------------------+\n");
   printf("| Year     | Model    | Price  | Number Available |\n");
   printf("+----------+----------+--------+------------------+\n");

   // Print the car information
   for (int i = 0; i < numberOfModels; i++) {
       if (numberOfCarsAvailable[i] > 0) {
           printf("| %-8d | %-9s| £%-6d| %-16d |\n", yearOfManufactureByModel[i], carModelsAvailable[i], carPriceByModel[i], numberOfCarsAvailable[i]);
       }
   }

   printf("+----------+----------+--------+------------------+\n");
}




// This function checks whether a car model exists
bool validateCarModelInput(const char *modelChoice, char *carModelsAvailable[], int numberOfModels) {
   // Loop from 0 to the number of car models
   for (int i = 0; i < numberOfModels; i++) {
       // If the car models matches one in the array
       if (strcmp(modelChoice, carModelsAvailable[i]) == 0) {
           return true;
       }
   }
   // and if it does not
   return false;
}





int main() {
   // The top section of this function defines the variable that are going to be used in the program
   unsigned short carsNeeded = 0, userAge = 0, SalesData_carsSold = 0;
   int giveDiscount = 0;
   //unsigned short carsAvailable = 10;
   // SalesData_totalSalePriceValue will be used in the View Sales case
   float totalPrice = 0; //SalesData_totalSalePriceValue;
   char userChoice;
   // this array will hold the value of each sale transaction, including any discount given at the time



   // Define the cars for sale, their price, year and number of them available
   int yearOfManufactureByModel[] = {2020, 2021, 2018, 2016, 2017};
   int numberOfCarsAvailable[] = {1, 2, 3, 4, 1};
   int carPriceByModel[] = {5000, 4500, 4000, 4750, 15000};
   char *carModelsAvailable[] = {"BMW", "Audi", "VW", "Mercedes", "Bentley"};

   // number of sales will be used to track where data needs to be store in arrays
   int SalesData_numberOfSales = 0;

   // Now we are going to take data from files and store it in arrays

   int SalesData_unitsSoldBySale[MAX_SALES];
   // Open the file unitsSold.txt
   FILE *unitsSoldFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/unitsSold.txt", "r");
   // If you cannot open the file
   if (unitsSoldFile == NULL) {
       // If there is an error show error message
       printf("Error opening file unitsSold.txt: %s\n", strerror(errno));
   }
   // Loop through each line of the file assuming the maximum number of lines is going to be equal to the maximum number of sales
   for (int i = 0; i < MAX_SALES; i++) {
       // Read and store the int in the array, if it is unsuccessful then we have reached the end of the file so we break
       if (fscanf(unitsSoldFile, "%d\n", &SalesData_unitsSoldBySale[i]) != 1) {
           break;  // End of file reached or read error
       }
   }
       // Close the file
       fclose(unitsSoldFile);


       // And then below I am going to repeat it for the other files
       char SalesData_discountGiven[MAX_SALES][6];
       FILE *discountFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/discount.txt", "r");
       if (discountFile == NULL) {
           // If there is an error show error message
           printf("Error opening file discount.txt: %s\n", strerror(errno));
       }

       for (int i = 0; i < MAX_SALES; i++) {
           if (fgets(SalesData_discountGiven[i], 201, discountFile) == NULL) {
               break;
           }
           // This strips the new line character
           SalesData_discountGiven[i][strcspn(SalesData_discountGiven[i], "\n")] = '\0';
       }

       fclose(discountFile);
       // This one is a little different due to an error with empty lines and new line chars
       char SalesData_Dates[MAX_SALES][11];
       // Retrieve data for SalesData_Dates
       FILE *datesFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/dates.txt", "r");
       if (datesFile == NULL) {
           // If there is an error show error message
           printf("Error opening file dates.txt: %s\n", strerror(errno));
           return 1;
       }
       // i is used to keep track of the array index
       // if we didnt have this then evertime there was an empty line there would be an empty section of the arr
       int i = 0;
       char line[11];
       while (fgets(line, sizeof(line), datesFile) != NULL) {
           // Remove trailing newline character
           line[strcspn(line, "\n")] = '\0';

           // Check for empty line and skip it
           if (strlen(line) > 0) {
               strcpy(SalesData_Dates[i], line);
               i++;
           }

       }



       fclose(datesFile);

       int feedback_ratingBySale[MAX_SALES] = {0};
       char *feedback_commentBySale[MAX_SALES][255];
       // Finish collecting data

       // Retrieve data for SalesData_totalSalesPrice
       float SalesData_totalSalePrice[MAX_SALES];
       FILE *salePriceFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/salePrice.txt", "r");
       if (salePriceFile == NULL) {
           // If there is an error show error message
           printf("Error opening file salePrice.txt: %s\n", strerror(errno));
           return 1;
       }

       for (int i = 0; i < MAX_SALES; i++) {
           if (fscanf(salePriceFile, "%f\n", &SalesData_totalSalePrice[i]) != 1) {
               break;  // End of file reached or read error
           }
           // keep track of the number of sales and number of cars sold
           SalesData_numberOfSales++;
           SalesData_carsSold++;

           // set rating to 11 and comment to None
           // This shows that there is no feedback for this vehicle/sale
           feedback_ratingBySale[i] = 11;
           strcpy(feedback_commentBySale[i], "None");

           // To update numberOfSales var
       }

       fclose(salePriceFile);

       // Finish data collection



       // Retrieve data for SalesData_carModelsSold
       char SalesData_carModelsSold[MAX_SALES][201];
       FILE *carModelsSoldFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/carModelsSold.txt", "r");
       if (carModelsSoldFile == NULL) {
           // If there is an error show error message
           printf("Error opening file carModelsSold.txt: %s\n", strerror(errno));
           return 1;
       }

       for (int i = 0; i < MAX_SALES; i++) {
           if (fgets(SalesData_carModelsSold[i], 201, carModelsSoldFile) == NULL) {
               break;  // End of file reached
           }
           SalesData_carModelsSold[i][strcspn(SalesData_carModelsSold[i], "\n")] = '\0';
       }

       fclose(carModelsSoldFile);
       // Finsish data collection

       // Get data for SalesData_customerNames
       char SalesData_customerNames[MAX_SALES][201];
       FILE *customerNamesFile = fopen("/Users/henryburbridge/Desktop/ComputerScience/Programming/CarSales/customerNames.txt", "r");
       if (customerNamesFile == NULL) {
           printf("Error opening file customerNames.txt\n");
           return 1;
       }

       for (int i = 0; i < MAX_SALES; i++) {
           if (fgets(SalesData_customerNames[i], 201, customerNamesFile) == NULL) {
               break;  // End of file reached
           }
           SalesData_customerNames[i][strcspn(SalesData_customerNames[i], "\n")] = '\0';

       }

       fclose(customerNamesFile);
       // Finish data collection

       // Set numberOfModels to the length of the array carModelsAvailable
       const int numberOfModels = sizeof(carModelsAvailable) / sizeof(carModelsAvailable[0]);
       // this will track how many car sales took place; it will be used as an array index as a data counter

       // this array will hold the name of each customer, a maximum of 200 characters per name

       // int feedback_ratingBySale[MAX_SALES] = {0};
       int feedback_numberOfReviews = 0;

       do {



           int SalesData_yearOfManufactureByModelSold[MAX_SALES];


           // greet the user


           // call the function menu_showMenu() to display the menu
           menu_showMenu();
           // note the space in front of the %, this tells scanf to skip any whitespace (spaces, newlines, etc.)
           scanf(" %c", &userChoice);
           // validate user input
           if (userChoice != 'a' && userChoice != 'b' && userChoice != 'c' && userChoice != 'd' && userChoice != 'x') {
               printf("Please enter a valid choice. \n");
               clearScreen();
           }

           // for the user's benefit...
           clearScreen();


           // next, we check the user's choice and make a decision based on that
           switch (userChoice) {
               // If the user selects buy car
               case MENU_OPTION_BUY_CAR:
                   printf("Which model car would you like to buy? ");
               // Call function to display all car models available
               menu_displayCars(carModelsAvailable, numberOfCarsAvailable, carPriceByModel, numberOfModels, yearOfManufactureByModel);
               char modelChoice[50];
               // Start a loop to ask the user which model they would like and validate their input
               while (1) {
                   printf("\nPlease choose car model: ");

                   // scanf("%s", SalesData_carModelsSold[SalesData_numberOfSales]);
                   scanf("%s", SalesData_carModelsSold[SalesData_numberOfSales]);
                   // Insert the input into the arr SalesData_carModelsSold
                   // validate the input by calling function validateCarModelInput
                   if (validateCarModelInput(SalesData_carModelsSold[SalesData_numberOfSales], carModelsAvailable, numberOfModels)) {
                       break;
                   } else {
                       printf("\nPlease enter a valid car model");
                       // clear input buffer
                       while (getchar() != '\n');
                   }
               }
               // Copt the chosen model into the var modelChoice
               strcpy(modelChoice, SalesData_carModelsSold[SalesData_numberOfSales]);
               printf("Model Choice: %s\n", modelChoice);

               // declare var modelChoiceIndex
               int modelChoiceIndex = 0;
               // get the index for the chosen model
               modelChoiceIndex = getModelIndex(modelChoice, carModelsAvailable, numberOfModels);

               // using that index find out the year of the model from the array
               const int yearOfManufacture = yearOfManufactureByModel[modelChoiceIndex];

               // and use it again to find out how many of the model are available
               unsigned short carsAvailable = numberOfCarsAvailable[modelChoiceIndex];

               // and again for the car price
               const int carPrice = carPriceByModel[modelChoiceIndex];

               // if there are enough cars
               if (carsAvailable > 0) {
                   printf("There are %hd cars available. Each car costs £%d.\n\n", carsAvailable, carPrice);
               }
               // and if there are not enough cars
               else {
                   printf("Sorry, there are no more cars available.");
                   // this allows us to terminate/stop the case early
                   break;
               }

               // start loop to take customers name and validate it
               while(1) {
                   printf("What is your name? Name: ");
                   scanf(" %[^\n]s", SalesData_customerNames[SalesData_numberOfSales]);
                   while (getchar() != '\n');

                   // a name is not valid if it contains more than 200 chars
                   if (strlen(SalesData_customerNames[SalesData_numberOfSales]) > 0 && strlen(SalesData_customerNames[SalesData_numberOfSales]) >= 200) {
                       printf("Please enter a valid name. \n\n");

                   // if it is valid then break the loop
                   } else {
                       break;
                   }
               }

               // start another loop to ask the user how many cars they need and validate their response
               while(1) {
                   printf("\nHow many cars do you need? Amount: ");

                   // check that the input is an integer
                   if (scanf("%hd", &carsNeeded) == 1) {
                       break;
                   } else {
                       printf("Please enter a valid integer. \n");
                       while (getchar() != '\n'); // Clears the input buffer after failed input operation. Stops the infinite loop without chance for user re-input
                   }
               }


               // check if we have enough cars

               if (carsAvailable < carsNeeded) {
                   printf("Sorry, there are fewer cars remaining than you require.");
                   // we will terminate the case instead of stopping the entire program
                   break;
               }

               // calculate total price
               totalPrice = (float)carsNeeded * (float)carPrice;

               // update number of cars available by subtracting from it the amount of cars needed
               carsAvailable -= carsNeeded;

               // ask for the user's age
               while (1) {
                   printf("How old are you? Age: ");
                   if (scanf("%hd", &userAge) == 1) {
                       break;
                   } else {
                       printf("Please enter a valid integer. \n");
                       while (getchar() != '\n');
                   }
               }

               // reset the giveDiscount variable's value, we assume no discount will be given
               giveDiscount = 0;

               // check if we need to give a discount
               if (userAge >= DISCOUNT_MIN_AGE && userAge <= DISCOUNT_MAX_AGE) {
                   // change the value of giveDiscount to indicate that we should
                   // be giving them a discount on this purchase
                   giveDiscount = 1;
               }
               else {
                   // check if they have an NUS card, then we can also apply the discount
                   char discountCardResponse;
                   // printf("\n\nDo you have an NUS card? Answer 'y' or 'n': ");
                   //
                   // scanf(" %c", &nusCardResponse);
                   while (1) {
                       printf("\n\nDo you have an vehicle discount card? Answer 'y' or 'n': ");
                       if (scanf(" %c", &discountCardResponse) == 1) {
                           if (discountCardResponse == 'y' || discountCardResponse == 'n') {
                               break;
                           }
                           printf("Please enter a valid choice. \n");
                       } else {
                           printf("Please enter a valid choice. \n");
                           while (getchar() != '\n');
                       }
                   }

                   if (discountCardResponse == 'y') {
                       // change the value of giveDiscount to indicate that we should
                       // be giving them a discount on this purchase
                       giveDiscount = 1;
                   }
               }

               if (giveDiscount == 1) {
                   printf("Total Price %f\n", totalPrice);
                   // Calc discount
                   totalPrice = totalPrice * (1 - DISCOUNT_PERCENTAGE);
                   printf("Total Price is %f\n", totalPrice);

                   printf("\n\nYou get a discount!");
               } else {
                   printf("\n\nNo discount given.");
               }

               // present the outcome
               clearScreen();
               // call purhcasConfirmation function
               purchaseConfirmation(carsNeeded, totalPrice, carsAvailable);





               SalesData_unitsSoldBySale[SalesData_numberOfSales] = carsNeeded;

               // Record wether discount was given
               if (giveDiscount == 1) {
                   strcpy(SalesData_discountGiven[SalesData_numberOfSales], "TRUE");
               } else {
                   strcpy(SalesData_discountGiven[SalesData_numberOfSales], "FALSE");
               }



               char dateString[11];
               // get todays date
               strcpy(dateString, getDate());
               // SalesData_Dates[SalesData_numberOfSales] = dateString;
               // prevent buffer overflow by making sure that the string is null terminated
               strncpy(SalesData_Dates[SalesData_numberOfSales], dateString, sizeof(SalesData_Dates[SalesData_numberOfSales]) - 1);
               SalesData_Dates[SalesData_numberOfSales][sizeof(SalesData_Dates[SalesData_numberOfSales]) - 1] = '\0';

               // get total price
               SalesData_totalSalePrice[SalesData_numberOfSales] = totalPrice;
               // update number of cars sold
               SalesData_carsSold += carsNeeded;
               // get year of manufacture
               SalesData_yearOfManufactureByModelSold[modelChoiceIndex] = yearOfManufacture;
               // update number of cars available
               numberOfCarsAvailable[modelChoiceIndex] -= 1;

               // start feedback loop
               char feedback;
               while (1) {

                   printf("\nWould you like to leave feedback? (y/n): ");
                   scanf(" %c", &feedback); // Note the space before %c to consume newline character

                   if (feedback != 'y' && feedback != 'n') {
                       printf("Please enter a valid choice\n");
                   } else {
                       break;
                   }
               }


               switch(feedback) {
                   case 'y':


                       while (1) {
                           int rating;

                           printf("\nWhat do you rate the car out of 10?:\n ");
                           scanf("%d", &rating);
                           // validate input
                           if (rating > 10 || rating < 1) {
                               printf("Please enter a valid choice. \n");
                           } else {
                               feedback_ratingBySale[SalesData_numberOfSales] = rating;


                               break;
                           }
                       }


                   while (1) {
                       char comment[256];
                       printf("Please leave a comment on your experience of the car (max 256 characters):\n ");
                       scanf("%255s", comment);  // Limit input to 255 characters

                       // Check if the input is valid
                       if (strlen(comment) < 256) {
                           // Input is valid, break out of the loop
                           strcpy(feedback_commentBySale[SalesData_numberOfSales], comment);


                           break;
                       } else {
                           printf("Comment is too long. Please enter a shorter comment.\n");
                       }
                   }
                   // update the number of reviews
                   // important so that we dont list sales that dont have reviews under the reviews tab
                   feedback_numberOfReviews += 1;
                   break;



                   case 'n':
                       // Insert placeholders to keep these arrays aligned with the sales data arrays
                           feedback_ratingBySale[SalesData_numberOfSales] = 11;
                   strcpy(feedback_commentBySale[SalesData_numberOfSales], "None");
                   break;
               }



               SalesData_numberOfSales++;
               break;

               case MENU_OPTION_VIEW_SALES:

                   // just calls the function to view all sales
                   menu_viewSales(SalesData_numberOfSales, SalesData_totalSalePrice, SalesData_customerNames,
                       SalesData_carsSold, SalesData_carModelsSold, numberOfModels, yearOfManufactureByModel,
                       SalesData_Dates, SalesData_unitsSoldBySale, SalesData_discountGiven);

               break;

               case MENU_OPTION_VIEW_CAR_STOCK:
                   printf("\nCar Stock");
               // call function to view car stock
               menu_displayCars(carModelsAvailable, numberOfCarsAvailable, carPriceByModel, numberOfModels, yearOfManufactureByModel);

               case MENU_OPTION_EXIT:
                   printf("Thank you for using this car Sales program. Bye-bye!");
               break;

               case MENU_OPTION_CUSTOMER_FEEDBACK:
                   // feedback_commentBySale[SalesData_numberOfSales]
                       // feedback_ratingBySale[SalesData_numberOfSales]
                           // SalesData_customerNames[SalesData_numberOfSales]
                               printf("\n");
               // if there are no reviews
               if (feedback_numberOfReviews == 0) {
                   printf("Sorry, there is no customer feedback to review");
                   break;
               }
               for (int i = 0; i < SalesData_numberOfSales; i++) {
                   // only show review if the rating is not 11
                   // as we set the rating to 11 when a customer decides not to leave a review
                   if (feedback_ratingBySale[i] != 11) {
                       printf("\nModel: %s", &*SalesData_carModelsSold[i]);
                       printf(" | Rating: %d", feedback_ratingBySale[i]);
                       printf(" | Comment: %s\n", feedback_commentBySale[i]);
                       printf("--------------------------------------------");
                   }



               }
               break;

               defualt:
                   break;

           }

           // give the user a chance to read the previous output, allow them to continue when ready
           // customise the output depending on the user's choice
           if (userChoice == MENU_OPTION_EXIT) {
               printf("\n\nPress Enter to Exit...");
           }
           else {
               printf("\n\nPress Enter to return to the Menu...\n");
           }

           // we can use getchar() to simply pause the program and wait for an Enter key press
           getchar();
           // need two of these to handle the newline character left behind from
           // the previous time the user pressed Enter on a previous input
           getchar();
           clearScreen();

       } while (userChoice != MENU_OPTION_EXIT);

       // again, keep the screen clear

       // a good sentence almost never fails to warm the heart...
       printf("\n\nHave a good day!\n\n");

       return 0;
   }

