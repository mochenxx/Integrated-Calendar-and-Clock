/*
 * File name: print.h
 *
 * Author: Mo Chen
 *
 * Description: Header file that prints messages to screen
 */

#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "dateInfo.h"
#include "timeInfo.h"
#include "input.h"
#include "softwareInfo.h"
#include "worldClock.h"

/*
 * This function prints the header of program
 *
 * @returns - Nothing
 */
void printHeader(void);

/*
 * This function prints calendar of a given month and year
 *
 * @param[in] month - Input month number (1-12)
 * @param[in] year - Input year number
 *
 * @returns - Nothing
 */
void displayCalendar(unsigned int month, unsigned int year);

/*
 * This function prints pause message between each operation
 *
 * @returns - Nothing
 */
void printPauseMsg(void);


/*
 * This function displays main menu for the calendar
 *
 * @returns - Nothing
 */
void displayMainMenu(void);

/*
 * This function prints error message for invalid input
 * when choosing the operation
 *
 * @param[in] max - maximum number of options for certain operation
 */
void printInvalidError(unsigned int max);

/*
* This function displays upcoming birthdays, events, and holidays
*
* @param[in] coord - previous coordinates
* @param[in] month - input month
* @param[in] year - input month
*/
void displayUpcomingEvents(COORD coord, unsigned int month, unsigned int year);

#endif // !_PRINT_H_
