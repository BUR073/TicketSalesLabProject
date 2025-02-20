# Car Sales Project - C Programming

This is for my 'Introduction to Programming' Module in term 1. As such, it is not my highest quality program. 
This project is a C program for managing car sales, fulfilling the requirements for a module assessment. It provides a menu-driven interface for managing car stock, sales, and customer feedback.

## Features

This program includes the following features:

* **Looping Menu:** A menu-driven interface allows users to select from the following actions:
    * View Car Stock
    * Buy Cars
    * View Sales Data
    * Customer Feedback
* **Car Data Storage:** Four arrays are used to store car information:
    * Two arrays for car price and model.
    * One array for the year of manufacture.
    * One array for the remaining amount of each car model.
    * Car data is randomly generated/selected.
* **View Car Stock:** Displays a list of car models, year of manufacture, and remaining stock, sorted by year of manufacture in descending order.
* **Buying Cars:** Records sales information, including:
    * Total price
    * Customer name
    * Customer age
    * Discount (if applicable)
    * Discount value
    * Number of cars purchased
    * Date of purchase
    * Updates car stock arrays after a sale.
* **Input Validation:** User input is validated and filtered to ensure correct data entry.  The program will prompt the user until valid input is provided.
* **Sales Data:** Displays sales data for each car model, including the total sum and details of each customer purchase.  Sales data is sorted by total sale amount in descending order.
* **Sales Data Persistence:** Sales data is stored in a file and loaded at program startup.
* **Customer Feedback:** Allows customers to leave feedback (rating out of 5 and a short comment) after a purchase. Feedback is stored and associated with the purchased car model.
* **Advanced Features:**  The project incorporates topics beyond the core module content to enhance functionality (e.g., dynamic memory allocation, file encryption – details in the code and logbook).
* **Coding Standards:** The code adheres to recommended coding standards and best practices (see Week 2 materials).

## Compilation

To compile the program, use a C compiler (e.g., GCC):

```bash
gcc car_sales.c -o car_sales
