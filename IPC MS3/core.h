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

/******************************* SAFE GUARD ********************************/

#ifndef CORE_H
#define CORE_H

/************************** FUNCTION DECLARATION ***************************/

//////////////////////////////
// USER INTERFACE FUNCTIONS //
//////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

//////////////////////////
// USER INPUT FUNCTIONS //
//////////////////////////

// Get an integer input
int inputInt(void);

// Get a positive integer input
int inputIntPositive(void);

// Get an integer input within given range
int inputIntRange(int, int);

// Get a character input matching any of the characters in a given string
char inputCharOption(char*);

// Get a string input within given range of string length
void inputCString(char*, int, int);

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

// Format and display 10 digit phone number
void displayFormattedPhone(const char*);

#endif // !CORE_H