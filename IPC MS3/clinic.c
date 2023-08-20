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
#include <string.h>

/************************* USER-DEFINED LIBRARIES **************************/

#include "core.h"
#include "clinic.h"

/*************************** FUNCTION DEFINITION ***************************/

///////////////////////
// DISPLAY FUNCTIONS //
///////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}

/////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS //
/////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, emptyRecord = 1;

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        // Patient records that have a zero value for the patient number should NOT be displayed.
        if (patient[i].patientNumber != 0)
        {
            // Display a single record
            displayPatientData(&patient[i], fmt);
            emptyRecord = 0;
        }
    }

    // Display: "*** No records found ***" if there were no eligible records to display.
    if (emptyRecord == 1)
    {
        printf("*** No records found ***\n");
    }
    
    printf ("\n");
    
    return;
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);

        if (selection == 1)
        {
            printf("\n");
            searchPatientByPatientNumber(patient, max);
            printf("\n");
            suspend();
        }
        else if (selection == 2)
        {
            printf("\n");
            searchPatientByPhoneNumber(patient, max);
            printf("\n");
            suspend();
        }
        else
        {
            printf("\n");
        }
    } while (selection != 0);

    return;
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, index, nextNum, flag = 0;

    // Check if the patient array has a free element for a new record
    for (i = 0; i < max && flag == 0; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            index = i;
            flag = 1;
        }
    }

    // Display error message if array does not have room for a new record
    if (flag == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    // Otherwise, assign the next unique patient number and get user input
    else
    {
        nextNum = nextPatientNumber(patient, max);
            
        patient[index].patientNumber = nextNum;

        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    }

    return;
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int num, index;

    printf("Enter the patient number: ");
    num = inputIntPositive();
    printf("\n");
    
    // Check if there is a record with a matching phone number
    index = findPatientIndexByPatientNum(num, patient, max);

    if (index > 0)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }

    return;
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int num, index;
    char response;
    char yesOrNo[3] = "yn";

    printf("Enter the patient number: ");
    num = inputIntPositive();
    printf("\n");

    // Check if there is a record with a matching phone number
    index = findPatientIndexByPatientNum(num, patient, max);

    if (index > 0)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");
        response = inputCharOption(yesOrNo);

        // Set the patient information to a safe empty state if user says yes
        if (response == 'y')
        {
            strcpy(patient[index].name, "\0");
            patient[index].patientNumber = 0;
            strcpy(patient[index].phone.description, "\0");
            strcpy(patient[index].phone.number, "\0");
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
    // Display error message if there is no matching patient record
    else
    {
        printf("ERROR: Patient record not found!\n");
    }

    printf("\n");

    return;
}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int index, i = 0;

    displayScheduleTableHeader(&data->appointments[i].date, YES_INDICATOR);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if(data->appointments[i].patientNumber != 0)
        {
            index = findPatientIndexByPatientNum (data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], YES_INDICATOR);
        }
    }

    printf("\n");

    return;
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    struct Date tempDate = { 0 };
    int index, i;
    
    // Call function to get the appointment date and save it
    tempDate = getApptDate();

    printf("\n");

    displayScheduleTableHeader(&tempDate, NO_INDICATOR);

    for (i = 0; i < data->maxAppointments; i++)
    {
        // If there is/are appointment(s) on the entered date, display appointment information
        if (data->appointments[i].patientNumber != 0 &&
            data->appointments[i].date.year == tempDate.year &&
            data->appointments[i].date.month == tempDate.month &&
            data->appointments[i].date.day == tempDate.day)
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], NO_INDICATOR);
        }
    }

    printf("\n");

    return;
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients)
{
    int i, emptyIndex, patientIndex = -1;
    int tempPatientNumber;
    int apptAvailable = 1;
    int emptyAppt = 0;
    struct Date tempDate = { 0 };
    struct Time tempTime = { 0 };
    
    // Check if there is an available element in the appointments array for a new appointment to be added
    for (i = 0; i < maxAppts && emptyAppt == 0; i++)
    {
        if (appointments[i].patientNumber == 0)
        {
            emptyIndex = i;
            emptyAppt = 1;
        }
    }

    // Continue with the appointment setup process, if there is an available appointment timeslot
    if (emptyAppt == 1)
    {
        // Prompt user for the patient number
        printf("Patient Number: ");
        tempPatientNumber = inputIntPositive();

        // Call function to find and save the patient index using the entered patient number
        patientIndex = findPatientIndexByPatientNum(tempPatientNumber, patients, maxPatients);

        // Repeat prompting user for the desired appointment date (until input is valid), or display message
        do
        {
            apptAvailable = 1;
            // Continue if patient with the entered patient number exists
            if (patientIndex >= 0)
            {
                // Call functions to get the date and time information of the appointment to add
                tempDate = getApptDate();
                tempTime = getApptTime();

                printf("\n");

                // Display message if there is an appointment with the same date and time already
                for (i = 0; i < maxAppts && apptAvailable == 1; i++)
                {
                    if (appointments[i].patientNumber != 0 &&
                        appointments[i].date.year == tempDate.year &&
                        appointments[i].date.month == tempDate.month &&
                        appointments[i].date.day == tempDate.day &&
                        appointments[i].time.hour == tempTime.hour &&
                        appointments[i].time.min == tempTime.min)
                    {
                        printf("ERROR: Appointment timeslot is not available!\n\n");
                        apptAvailable = 0;
                    }
                }
            }
            // Display message if there are no patients with the entered patient number
            else
            {
                printf("ERROR: Patient record not found!\n");
            }
        } while (apptAvailable == 0);
    }
    // Display message if there are no available appointment timeslots
    else
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }

    // Save the new appointment information if input is valid and appointment timeslot is available
    if (patientIndex >= 0 && apptAvailable == 1)
    {
        appointments[emptyIndex].patientNumber = patients[patientIndex].patientNumber;
        appointments[emptyIndex].date.year = tempDate.year;
        appointments[emptyIndex].date.month = tempDate.month;
        appointments[emptyIndex].date.day = tempDate.day;
        appointments[emptyIndex].time.hour = tempTime.hour;
        appointments[emptyIndex].time.min = tempTime.min;

        printf("*** Appointment scheduled! ***\n\n");
    }

    // Call function to sort the appointments by date in ascending order
    sortApptData(appointments, maxAppts);

    return;
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppts, struct Patient* patients, int maxPatients)
{
    int index, i, flag = 0;
    int tempPatientNumber, patientIndex;
    char yesOrNo = ' ';
    struct Date tempDate = { 0 };

    // Prompt user for the patient number
    printf("Patient Number: ");
    tempPatientNumber = inputIntPositive();

    // Call function to find and save the patient index using the entered patient number
    patientIndex = findPatientIndexByPatientNum(tempPatientNumber, patients, maxPatients);

    // Display message if there are no patients with the entered patient number
    if (patientIndex < 0)
    {
        printf("ERROR: Patient record not found!\n");
    }
    // Continue if the patient with the patient number exists
    else
    {
        // Call function to find and save the appointment date to remove
        tempDate = getApptDate();
        
        printf("\n");

        displayPatientData(&patients[patientIndex], FMT_FORM);

        // Check if there exists an appointment with the entered appointment date
        for (i = 0; i < maxAppts && flag == 0; i++)
        {
            if (appointments[i].patientNumber == patients[patientIndex].patientNumber &&
                appointments[i].date.year == tempDate.year &&
                appointments[i].date.month == tempDate.month &&
                appointments[i].date.day == tempDate.day)
            {
                index = i;
                flag = 1;
            }
        }

        // Confirm with user if they want to remove the appointment
        if (flag == 1)
        {
            printf("Are you sure you want to remove this appointment (y,n): ");
            yesOrNo = inputCharOption("yn");

            if (yesOrNo == 'y')
            {
                appointments[index].patientNumber = 0;
                appointments[index].date.year = 0;
                appointments[index].date.month = 0;
                appointments[index].date.day = 0;

                printf("\n");
                printf("Appointment record has been removed!\n");
            }

        }
    }
    
    printf("\n");

    return;
}

///////////////////////
// UTILITY FUNCTIONS //
///////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int num, index;
    
    printf("Search by patient number: ");
    num = inputIntPositive();

    // Check if there is a record with a matching phone number
    index = findPatientIndexByPatientNum(num, patient, max);
    
    printf("\n");

    // Display the record if the patient record exists
    if (index > 0)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    // Display error message if the patient record does not exist
    else
    {
        printf("*** No records found ***\n");
    }

    return;
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, found = 0;
    char phoneNum[PHONE_LEN + 1];

    printf("Search by phone number: ");
    inputCString(phoneNum, PHONE_LEN, PHONE_LEN);

    printf ("\n");
    displayPatientTableHeader();

    // Check if patient array has matching phone number
    for (i = 0; i < max; i++)
    {
        // For each patient record found, display it in tabular format
        if (strcmp(phoneNum, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            found = 1;
        }
    }

    // Display error message if no matching patient record is found
    if (!found)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }

    return;
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, nextNum;

    nextNum = 0;
    
    // Find and save the largest patient number in the patient array
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > nextNum)
        {
            nextNum = patient[i].patientNumber;
        }
    }

    // Calculate the next patient number by adding 1
    nextNum++;

    return nextNum;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i = 0, found = 0;
    
    // Search the patient array for elements that match the "patientNumber"
    do
    {
        if (patientNumber == patient[i].patientNumber)
        {
            found = 1;
        }
        i ++;
    } while (i < max && found == 0);

    // Return -1 if matching record can't be found
    if (!found)
    {
        i = -1;
    }
    // Return the index position for the matched element if found
    else
    {
        i--;      
    }

    return i;
}

// Find the patient array index with the earliest date and time
int findLowestApptDate(const struct Appointment appointment[], int max)
{
    int i, index = 0;
    int lowestYear = 9999;
    int lowestMonth = 12;
    int lowestDay = 31;
    int lowestHour = 24;
    int lowestMin = 60;

    // Find and save the appointment with the earliest year
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year < lowestYear)
        {
            lowestYear = appointment[i].date.year;
        }
    }
    // Find and save the appointment with the earliest month, in the earliest year
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear
                                              && appointment[i].date.month < lowestMonth)
        {
            lowestMonth = appointment[i].date.month;
        }
    }
    // Find and save the appointment with the earliest day, in the earliest year, and month
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear
                                              && appointment[i].date.month == lowestMonth
                                              && appointment[i].date.day < lowestDay)
        {
            lowestDay = appointment[i].date.day;
        }
    }
    // Find and save the appointment with the earliest hour, in the earliest year, month, and day
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear
                                              && appointment[i].date.month == lowestMonth
                                              && appointment[i].date.day == lowestDay
                                              && appointment[i].time.hour < lowestHour)
        {
            lowestHour = appointment[i].time.hour;
        }
    }
    // Find and save the appointment with the earliest minute, in the the earliest year, month, day, and hour
    for (i = 0; i < max; i++)
    {
        if (appointment[i].patientNumber != 0 && appointment[i].date.year == lowestYear
                                              && appointment[i].date.month == lowestMonth
                                              && appointment[i].date.day == lowestDay
                                              && appointment[i].time.hour == lowestHour
                                              && appointment[i].time.min < lowestMin)
        {
            lowestMin = appointment[i].time.min;
            index = i;
        }
    }
    
    // Return the index of the appointment with the earliest date and time
    return index;
}

// Sorts the appointment data in ascending order by date and time
void sortApptData(struct Appointment appointment[], int max)
{
    int i, index;
    struct Appointment sortedAppts[50] = { {0} };

    for (i = 0; i < max; i++)
    {
        index = findLowestApptDate(appointment, max);

        // Add to new array
        sortedAppts[i].patientNumber = appointment[index].patientNumber;
        sortedAppts[i].date.year = appointment[index].date.year;
        sortedAppts[i].date.month = appointment[index].date.month;
        sortedAppts[i].date.day = appointment[index].date.day;
        sortedAppts[i].time.hour = appointment[index].time.hour;
        sortedAppts[i].time.min = appointment[index].time.min;
    
        // Remove from original array
        appointment[index].patientNumber = 0;
    }

    for (i = 0; i < max; i++)
    {
        // Save the values of the new array to the original array
        appointment[i].patientNumber = sortedAppts[i].patientNumber;
        appointment[i].date.year = sortedAppts[i].date.year;
        appointment[i].date.month = sortedAppts[i].date.month;
        appointment[i].date.day = sortedAppts[i].date.day;
        appointment[i].time.hour = sortedAppts[i].time.hour;
        appointment[i].time.min = sortedAppts[i].time.min;        
    }

    return;
}

// Prompt user for the date (year, month, day) of the appointment
struct Date getApptDate(void)
{
    struct Date date = { 0 };

    // Prompt user and save the valid year input
    printf("Year        : ");
    date.year = inputIntPositive();

    // Prompt user and save the valid month input
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    // Prompt user and save the valid day input for odd months
    if (date.month % 2 != 0)
    {
        printf("Day (1-31)  : ");
        date.day = inputIntRange(1, 31);
    }
    // Prompt user and save the valid day input for even months
    else if (date.month % 2 == 0)
    {
        // Check for leap year if month is February
        if (date.month == 2)
        {
            if (date.year % 4 == 0)
            {
                printf("Day (1-29)  : ");
                date.day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                date.day = inputIntRange(1, 28);
            }
        }
        else
        {
            printf("Day (1-30)  : ");
            date.day = inputIntRange(1, 30);
        }
    }

    // Return the date (year, month, day)
    return date;
}

// Prompt user for the time (hour, minute) of the appointment
struct Time getApptTime(void)
{
    int flag = 0;
    struct Time time = { 0 };

    // Repeat prompting for the hour and minute, until valid input is entered
    do
    {
        // Prompt user for the hour
        printf("Hour (0-23)  : ");
        time.hour = inputIntRange(0, 23);

        // Prompt user for the minute
        printf("Minute (0-59): ");
        time.min = inputIntRange(0, 59);

        // Check if entered time is within business hours, and make sure time is at valid minute intervals
        if ((time.hour == OPERATION_END_HOUR && time.min != 0) ||
            (time.hour < OPERATION_START_HOUR || time.hour > OPERATION_END_HOUR) ||
            ((time.hour >= OPERATION_START_HOUR && time.hour <= OPERATION_END_HOUR) && (time.min % OPERATION_MINUTE_INTERVAL != 0)))
        {
            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
        }
        else
        {
            flag = 1;
        }
    } while (flag == 0);


    return time;
}

//////////////////////////
// USER INPUT FUNCTIONS //
//////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    
    printf("\n");

    inputPhoneData(&patient->phone);

    return;
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    selection = inputIntRange(1, 4);

    switch (selection)
    {
    case 1:
            printf("\n");
            strcpy((*phone).description, "CELL");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            break;
    case 2:
            printf("\n");
            strcpy((*phone).description, "HOME");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            break;
    case 3:
            printf("\n");
            strcpy((*phone).description, "WORK");
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputCString(phone->number, PHONE_LEN, PHONE_LEN);
            break;
    case 4:
            strcpy((*phone).description, "TBD");
            strcpy((*phone).number, "\0");
            break;
    }

    printf("\n");

    return;
}

////////////////////
// FILE FUNCTIONS //
////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* fp = NULL;

    int rc, i = 0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        do
        {
            rc = fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber, patients[i].name,
                                                        patients[i].phone.description, patients[i].phone.number);
            if (rc > 0)
            {
                i++;
            }
        } while (rc > 0 && i < max);

        fclose(fp);
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;

    int i = 0;

    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber, &appoints[i].date.year,
                                                 &appoints[i].date.month, &appoints[i].date.day,
                                                 &appoints[i].time.hour, &appoints[i].time.min) == 6 && i < max)
        {
            i++;
        }

        fclose(fp);
    }

    sortApptData(appoints, i);

    return i;
}