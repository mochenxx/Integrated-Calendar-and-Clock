/*
 * File name: main.c
 *
 * Author: Mo Chen
 *
 * Copyright: 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <windows.h>

#include "print.h"
#include "softwareInfo.h"
#include "timeInfo.h"
#include "dateInfo.h"
#include "input.h"
#include "birthday.h"
#include "holiday.h"
#include "event.h"
#include "logFile.h"
#include "setColor.h"
#include "setCursor.h"
#include "stopwatch.h"
#include "countdownTimer.h"
#include "worldClock.h"

int main()
{
	unsigned int month, year;
	unsigned int is_birthday = 0, is_event = 0; 	// Flags for a given date
	int key_code;					// User input from keyboard
	unsigned int given_date_bdays[20] = { 0 };  	// Birthdays info on given date
	unsigned int given_date_events[20] = { 0 };	// All Events on a given date
	
	// number of birthday, holiday, event on certain date
	unsigned int num_bday = 0, num_holiday = 0, num_event = 0;	
	 
	Date new_date = { 0 };		// New date structure
	Event new_event = { 0 };	// New event structure

	/* Read birthday record file */
	readBdayFile();

	/* Read holiday record file */
	readHolidayFile();

	/* Read event record file */
	readEventFile();

	/* Read world clock file containing all available cities clock info */
	readWorldClockFile();

	/* Read world clock record file including user-selected city clock info */
	readWorldClockLogFile();

	// Get current month and year
	// Store corresponding value to month and year variables
	getCurrentMonthYear(&month, &year);

	do
	{
		/* Display the calendar for given month and year numbers */
 		displayCalendar(month, year);

		/* Display main menu */
		displayMainMenu();

		/* Make cursor visible */
		visibleCursor(1);

		/* Get current cursor position */
		COORD coord = GetConsoleCursorPosition();

		/* Display upcoming events on the RHS or Calendar */
		displayUpcomingEvents(coord, month, year);

		/* Get key code from keyboard input */
		key_code = getCode();
		
		switch (key_code)
		{
			// Up Arrow Key
			case ARROW_UP:
			{
				year++;
				break;
			}

			// Down Arrow Key
			case ARROW_DOWN:
			{
				year--;
				break;
			}

			// Left Arrow Key 
			case ARROW_LEFT:
			{
				month--;

				/* Check if month is less than 0 -> go to last year */
				if (month <= 0)
				{
					month = 12;
					year--;
				}
				break;
			}

			// Right Arrow Key
			case ARROW_RIGHT:
			{
				month++;

				/* Check if month is greater than 12 -> go to next year */
				if (month > 12)
				{
					month = 1;
					year++;
				}
				break;
			}

			// ESC key
			case KEY_ESC:
			{
				exit(1);
			}

			// Entered Key One '1' - Input New Month & Year
			case KEY_ONE:
			{
				/* Input month and year from user keyboard */
				inputMonthYear(&month, &year);

				break;
			}

			// Entered Key Two '2' - Add Birthday
			case KEY_TWO:
			{
				/* Input new date, month and year from user keyboard */
				inputDate(&new_date, month, year);

				/* Add birthday info */
				addBirthday(&new_date);

				/* Print pause message */
				printPauseMsg();

				break;
			}

			// Entered Key Three '3' - Add Event
			case KEY_THREE:
			{
				/* Input new date, month and year from user keyboard */
				inputDate(&new_date, month, year);

				/* Add event info */
				addEvent(&new_date);

				/* Print pause message */
				printPauseMsg();

				break;
			}

			// Entered Key Five '4' - Delete Birthday or Event Information
			case KEY_FOUR:
			{
				/* Input new date, month and year from user keyboard */
				inputDate(&new_date, month, year);
				
				/* Display birthdays information for input date */
				displayBirthdays(new_date.month, 
								 new_date.day,
								 &is_birthday, 
								 given_date_bdays, 
								 &num_bday);

				/* Display events information for input date */
				displayEvents(new_date.year, 
							  new_date.month, 
							  new_date.day, 
							  &is_event, 
							  given_date_events, 
							  &num_event);

				// Check if there is a birthday
				if (is_birthday)
				{
					/* Ask if user wants to delete birthday info */
					askDeleteBday(given_date_bdays, &num_bday);
				}

				// Check if there is a event
				if (is_event)
				{
					/* Ask if user wants to delete event info */
					askDeleteEvent(given_date_events, &num_event);
				}

				/* Print pause message */
				printPauseMsg();

				break;
			}

			// Entered Key Four '5' - Stopwatch
			case KEY_FIVE:
			{
				/* Run stopwatch */
				stopwatch();

				/* Print pause message */
				printPauseMsg();

				break;
			}

			// Entered Key Four '6' - Timer
			case KEY_SIX:
			{
				/* Run timer */
				timer();

				/* Print pause message */
				printPauseMsg();

				break;
			}

			// Entered Key Four '7' - World Clock
			case KEY_SEVEN:
			{
				/* Run world clock */
				worldClock();

				/* Print pause message */
				printPauseMsg();

				break;
			}

			default:
			{
				/* Print error message for invalid input */
				printInvalidError(7);

				/* Print pause message */
				printPauseMsg();

				break;
			}
		}	
	} while (key_code != KEY_ESC); 	// Break if hits key ESC
}
