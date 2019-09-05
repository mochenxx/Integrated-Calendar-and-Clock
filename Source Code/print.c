/*
 * File name: print.c
 *
 * Author: Mo Chen
 *
 * Description: c file for printing messages to user screen
 */

#include "print.h"
#include "holiday.h"
#include "birthday.h"
#include "event.h"
#include "setColor.h"
#include "setCursor.h"

void printHeader(void)
{
	/* Print author and local time */
	system("CLS");
	printf("\nCreated By: %s                %s\n\n", AUTHOR, timestamp());
}

void displayCalendar(unsigned int month, unsigned int year)
{
	unsigned int number_of_days, first_day_of_week, holiday_idx;
	unsigned int bday_index, event_index;
	unsigned int i, j, day_of_week;

	/* Print header of the program */
	setColor(TEXT_COLOR_WHITE);
	printHeader();

	/* Get number of days in a given month */
	number_of_days = getMonthDays(month, year);

	/* Calculate day of first date of given month */
	first_day_of_week = getDayOfWeek(1, month, year);

	/* Print the corresponding month name and year */
	setColor(DEFAULT_TEXT_COLOR);
	printf("   +---------------------------------------------------+\n");
	setColor(TITLE_TEXT_COLOR);
	printf("                Calendar %s - %d\n", month_names[month], year);
	setColor(DEFAULT_TEXT_COLOR);
	printf("   +---------------------------------------------------+\n");

	/* Print the columns from Sunday to Saturday */
	setColor(SUNDAY_TEXT_COLOR);
	printf("    SUN");
	setColor(WEEKDAY_TEXT_COLOR);
	printf("     MON     TUE     WED     THU     FRI");
	setColor(SATURDAY_TEXT_COLOR);
	printf("     SAT\n");
	setColor(DEFAULT_TEXT_COLOR);
	printf("   +---------------------------------------------------+\n");
	
	/* Check number of empty position before the first day of input month */
	for (i = 0; i < first_day_of_week; i++)
	{
		printf("        ");
	}
	
	setColor(DEFAULT_TEXT_COLOR);
	j = first_day_of_week;

	/* Print the month info starting from day 1*/
	for (i = 1; i <= number_of_days; i++)
	{
		// Get the day of week on certain day
		day_of_week = getDayOfWeek(i, month, year);

		// For Saturday
		if (6 == day_of_week)
		{
			// Set corresponding text color
			setColor(SATURDAY_TEXT_COLOR);
		}
		// For Sunday
		else if (0 == day_of_week)
		{
			// Set corresponding text color
			setColor(SUNDAY_TEXT_COLOR);
		}
		else
		{
			// Set corresponding text color
			setColor(DEFAULT_TEXT_COLOR);
		}

		/* Check if the first day is Saturday */
		if ( j++ % 7 == 0 && j != 1)
		{
			// Print a new line and the date
			printf("\n");
			printf("    %2d", i);
		}
		else if (1 == i)
		{
			printf("    %2d", i);
		}
		else
		{
			printf("   %2d", i);
		} 

		/* Check if there are birthday & holiday & event on a day */
		if (isBirthday(month, i, &bday_index) &&
		    isHoliday(year, month, i, &holiday_idx) &&
		    isEvent(year, month, i, &event_index))
		{
			// Print signs
			setColor(BDAY_SIGN_COLOR);
			printf("*");
			setColor(HOLIDAY_SIGN_COLOR);
			printf("+");
			setColor(EVENT_SIGN_COLOR);
			printf("@");
		}

		/* Check if there are birthday & holiday on a day */
		else if (isBirthday(month, i, &bday_index) &&
			 isHoliday(year, month, i, &holiday_idx))
		{
			// Print signs
			setColor(BDAY_SIGN_COLOR);
			printf("*");
			setColor(HOLIDAY_SIGN_COLOR);
			printf("+");
			setColor(DEFAULT_TEXT_COLOR);
			printf(" ");
		}

		/* Check if there are birthday & event on a day */
		else if (isBirthday(month, i, &bday_index) && 
			 isEvent(year, month, i, &event_index))
		{
			// Print signs
			setColor(BDAY_SIGN_COLOR);
			printf("*");
			setColor(EVENT_SIGN_COLOR);
			printf("@");
			setColor(DEFAULT_TEXT_COLOR);
			printf(" ");
		}

		/* Check if there are holiday & event on a day */
		else if (isHoliday(year, month, i, &holiday_idx) &&
			 isEvent(year, month, i, &event_index))
		{
			// Print signs
			setColor(HOLIDAY_SIGN_COLOR);
			printf("+");
			setColor(EVENT_SIGN_COLOR);
			printf("@");
			setColor(DEFAULT_TEXT_COLOR);
			printf("  ");
		}

		/* Check if there is birthday on a day */
		else if (isBirthday(month, i, &bday_index)) {
			// Print signs
			setColor(BDAY_SIGN_COLOR);
			printf("*");
			setColor(DEFAULT_TEXT_COLOR);
			printf("  ");
		}

		/* Check if there is holiday on a day */
		else if (isHoliday(year, month, i, &holiday_idx))
		{
			// Print signs
			setColor(HOLIDAY_SIGN_COLOR);
			printf("+");
			setColor(DEFAULT_TEXT_COLOR);
			printf("  ");
		}

		/* Check if there is event on a day */
		else if (isEvent(year, month, i, &event_index))
		{
			// Print signs
			setColor(EVENT_SIGN_COLOR);
			printf("@");
			setColor(DEFAULT_TEXT_COLOR);
			printf("  ");
		}

		else {
			printf("   ");
		}

		setColor(DEFAULT_TEXT_COLOR);
	}

	/* Print instructions of signs */
	printf("\n   +---------------------------------------------------+\n");
	setColor(TITLE_TEXT_COLOR);
	printf("      Signs: (*) = Birthday, (+) = Holiday, (@) = Event\n");
	setColor(DEFAULT_TEXT_COLOR);
}

void printPauseMsg(void)
{
	/* Print pause message */
	printf("\nPress any key to continue ...\n");
	(void)_getch();
}

void displayMainMenu(void)
{
	/* Display main menu */
	printf("\n  [ Use Left,Right,Up & Down Arrow to navigate calendar. ]\n");
	printf("\n    %d) Press %d to %s", 1, 1, "Input New Month & Year.");
	printf("\n    %d) Press %d to %s", 2, 2, "Add Birthday.");
	printf("\n    %d) Press %d to %s", 3, 3, "Add Events.");
	printf("\n    %d) Press %d to %s", 4, 4, 
		   "Delete Birthday / Events for certain date.");
	printf("\n    %d) Press %d to %s", 5, 5, "use Stopwatch.");
	printf("\n    %d) Press %d to %s", 6, 6, "use Countdown Timer.");
	printf("\n    %d) Press %d to %s", 7, 7, "use World Clock.\n");
	printf("\n  [ Press ESC for Exit. ]\n");
}

void printInvalidError(unsigned int max)
{
	/* Print error message for invalid input */
	printf("\n\n[ERROR] Invalid input. "
		"You should enter a number between 1 and %d.\n", max);
}

void displayUpcomingEvents(COORD coord, unsigned int month, unsigned int year)
{
	unsigned int new_coord_x, new_coord_y;    // New coordinates

	new_coord_x = 60;
	new_coord_y = 2;

	/* Print header for upcoming events */
	gotoxy(new_coord_x, ++new_coord_y);
	printf("    +------------------------------------------------+\n");
	gotoxy(new_coord_x, ++new_coord_y);
	printf("    |");
	setColor(TITLE_TEXT_COLOR);
	     printf("             B-days & Holidays & Events         ");
	setColor(DEFAULT_TEXT_COLOR);
	printf("|\n");
	gotoxy(new_coord_x, ++new_coord_y);
	printf("    +------------------------------------------------+\n");

	// Display monthly birthdays 
	displayMonthlyBdays(month, year, &new_coord_x, &new_coord_y);

	// Display monthly holidays
	displayMonthlyHolidays(month, year, &new_coord_x, &new_coord_y);

	// Display monthly events 
	displayMonthlyEvents(month, year, &new_coord_x, &new_coord_y);

	// Go back to previous coordinates
	gotoxy(coord.X, coord.Y);
}
