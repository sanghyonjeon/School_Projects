/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Sang Hyon Jeon
Student ID#: 1123552194
Email      : shjeon5@myseneca.ca
Section    : NGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

/**************************** SYSTEM LIBRARIES *****************************/

#include <stdio.h>
#include <ctype.h>

/************************* USER-DEFINED LIBRARIES **************************/

#include "core.h"

/*************************** FUNCTION DEFINITION ***************************/

//////////////////////////////
// USER INTERFACE FUNCTIONS //
//////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////
// USER INPUT FUNCTIONS //
//////////////////////////

// Get an integer input
int inputInt(void)
{
    int value, keeptrying = 1, rc;
    char after;

    // Repeat prompt user for input until an integer is entered
    do {
        // Check if input is read
        rc = scanf("%d%c", &value, &after);

        // Display error and clear buffer if no input is read, or input is not followed by a new line
        if (rc == 0 || after != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        // Exit the input prompt loop if integer input is read, and is followed by a new line
        else
        {
            keeptrying = 0;
        }
    } while (keeptrying == 1);

    // Return the integer entered by the user
    return value;
}

// Get a positive integer input
int inputIntPositive(void)
{
    int value, keeptrying = 1, rc;
    char after;

    // Repeat prompt user for input until a positive integer is entered
    do {
        // Check if input is read
        rc = scanf("%d%c", &value, &after);

        // Display error and clear buffer if no input is read, or input is not followed by a new line
        if (rc == 0 || after != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        // Display error if input is read, and is followed by a new line, but is less than 0
        else if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        // Exit the input prompt loop if a positive integer input is read, and is followed by a new line
        else
        {
            keeptrying = 0;
        }
    } while (keeptrying == 1);

    // Return the integer entered by the user
    return value;
}

// Get an integer input within given range
int inputIntRange(int lowerBound, int upperBound)
{
    int value, keeptrying = 1, rc;
    char after;

    // Repeat prompt user for input until an integer within range is entered
    do {
        // Check if input is read
        rc = scanf("%d%c", &value, &after);

        // Display error and clear buffer if no input is read, or input is not followed by a new line
        if (rc == 0 || after != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        // Display error if input is read, and is followed by a new line, but is out of given range
        else if (value < lowerBound || value > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
        // Exit the input prompt loop if an integer input within range is read, and is followed by a new line
        else
        {
            keeptrying = 0;
        }
    } while (keeptrying == 1);

    // Return the integer within range entered by the user
    return value;
}

// Get a character input matching any of the characters in a given string
char inputCharOption(char* validChars)
{
    int i, keeptrying = 1, rc;
    char letter, after;

    // Repeat prompt user for input until a character matching a character in the given string is entered
    do
    {
        // Check if input is read
        rc = scanf(" %c%c", &letter, &after);

        // Display error and clear buffer if no input is read, or input is not followed by a new line
        if (rc == 0 || after != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", validChars);
            clearInputBuffer();
        }
        // Check if input matches a character in the given string, if input is read, and is followed by a new line
        else
        {
            i = 0;
            while (validChars[i] != '\0' && keeptrying == 1)
            {
                // Exit the input prompt loop if the input matches a character in the given string
                if (letter == validChars[i])
                {
                    keeptrying = 0;
                }
                i++;
            }
            // Display error if input does not match any of the characters in the given string
            if (keeptrying == 1)
            {
                printf("ERROR: Character must be one of [%s]: ", validChars);
            }
        }
    } while (keeptrying == 1);
    
    // Return the character that matches a character in the given string
    return letter;
}

// Get a string input within given range of string length
void inputCString(char* cString, int minNumChars, int maxNumChars)
{
    int i, length = 0, keeptrying = 1;
    char value[100] = {'\0'};

    // Repeat prompt user for input until a string with a length within the given range is entered
    do
    {
        // Accept all characters, until a new line and discard the rest of the characters in the buffer
        scanf("%[^\n]", value);
        clearInputBuffer();

        // Count and store the length of the input
        length = 0;
        for (i = 0; value[i] != '\0'; i++)
        {
            length++;
        }

        // Display corresponding error message if the length of the input is out of given range
        if (minNumChars == maxNumChars && length != minNumChars)
        {
            printf("Invalid %d-digit number! Number: ", minNumChars);
        }
        else if (length > maxNumChars)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxNumChars);
        }
        else if (length < minNumChars)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minNumChars, maxNumChars);
        }
        // Save the input and exit the input prompt loop if the length of the inputted string is within given range
        else
        {
            keeptrying = 0;

            for (i = 0; value[i] != '\0'; i++)
            {
                cString[i] = value[i];
            }
            cString[i] = '\0';
        }
    } while (keeptrying == 1);

    // Return control
    return;
}

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

// Format and display 10 digit phone number
void displayFormattedPhone(const char* cString)
{
    int i, j, allDigits = 1;
    char phoneNum[14] = {'\0'};

    // Format the default blank field of phone number
    for (i = 0; i < 13; i++)
    {
        if (i == 0)
        {
            phoneNum[i] = '(';
        }
        else if (i == 4)
        {
            phoneNum[i] = ')';
        }
        else if (i == 8)
        {
            phoneNum[i] = '-';
        }
        else
        {
            phoneNum[i] = '_';
        }
    }

    // Display the default blank phone number if the phone number passed to this function is NULL
    if (cString == NULL)
    {
            printf("%s", phoneNum);
    }
    // If a phone number is entered, validate the input
    else
    {
        // Check to make sure each character in the string is a number
        for (i = 0; cString[i] != '\0'; i++)
        {
            // Display the default blank phone number and exit the loop if a character in the string is not a number
            if (isdigit(cString[i]) == 0)
            {
                printf("%s", phoneNum);
                allDigits = 0;
            }
        }
        // Display the default blank phone number if the phone number is not 10 characters
        if (i != 10)
        {
            printf("%s", phoneNum);
        }
        // Update and display the default blank phone number if the phone number is 10 digits
        else if (allDigits == 1)
        {
            i = 0;
            for (j = 0; j < 13; j++)
            {
                if (j != 0 && j != 4 && j != 8)
                {
                    phoneNum[j] = cString[i];
                    i++;
                }
            }
            printf("%s", phoneNum);
        }
    }
    
    // Return control
    return;
}