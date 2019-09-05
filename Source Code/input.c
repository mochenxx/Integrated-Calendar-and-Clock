/*
 * File name: input.c
 *
 * Author: Mo Chen
 *
 * Description: c file that gets input from user
 */

#include "input.h"
#include "print.h"
#include "dateInfo.h"
#include "setColor.h"
#include "setCursor.h"

 /*
  * Disable warning of unsafe functions
  * _CRT_SECURE_NO_WARNINGS
  */
#pragma warning(disable : 4996)


bool isNumber(char s[])
{
	for (unsigned int i = 0; i < strlen(s); i++)
	{
		/* Check if the input value is a digit number */
		if (false == isdigit(s[i]))
		{
			return false;
		}
	}

	/* Returns true if input string is a number else false */	
	return true;
}

void inputMonthYear(int* p_month, int* p_year)
{
	char month_string[20], year_string[20];		// Input month & year strings
	unsigned char error_flag = 0;	// flag for whether error occurs

	while (true)
	{
		fflush(stdin);
		
		/* Check if there is an error occurred before */
		if (1 == error_flag)
		{
			printPauseMsg();
		}

		/* Print header of the program */
		printHeader();

		/* Get month and year input from user keyboard */
		printf("\nThis program shows a calendar of a given month\n");
		printf("\nEnter a month (format is mm): ");
		(void)scanf("%s", month_string);
		printf("\nEnter a year (format is yyyy): ");
		(void)scanf("%s", year_string);

		/* Check if input values are numbers */
	 	if (isNumber(month_string) && isNumber(year_string))
		{	
			/* If input values are numbers, */
			/* convert stored strings to integers*/
			*p_month = atoi(month_string);
			*p_year = atoi(year_string);

			if (!isValidDate(2, *p_month, *p_year))
			{
				/* Set error flag to 1 */
				error_flag = 1;
				continue;
			}
		}
		else
		{
			/* Print error message */
			printf("\n[ERROR] Input can only be integer! Please try again...\n");
			
			/* Set error flag to 1 */
			error_flag = 1;		
			continue;
		}
		break;
	} // End of while loop
}

void inputDate(Date *p_date, int cur_month, int cur_year)
{
	char day_str[DATE_MAX_LIMIT],
		 month_str[DATE_MAX_LIMIT],
		 year_str[DATE_MAX_LIMIT];
	unsigned char error_flag = 0;	// flag for whether error occurs

	while (true)
	{
		fflush(stdin);

		/* Check if there is an error occurred before */
		if (1 == error_flag)
		{
			printPauseMsg();
		}

		/* Print header of the program */
		printHeader();
		displayCalendar(cur_month, cur_year);
		fflush(stdin);
		/* Get current cursor position */
		COORD coord = GetConsoleCursorPosition();

		/* Display upcoming events on the RHS or Calendar */
		displayUpcomingEvents(coord, cur_month, cur_year);

		printf("\n------------------ Input Date --------------------\n");;
		printf("Enter the Month (format is mm): ");
		(void)scanf("%s", month_str);
		fflush(stdin);

		printf("Enter the Day (format is dd): ");
		(void)scanf("%s", day_str);
		fflush(stdin);

		printf("Enter the Year (format is yyyy): ");
		(void)scanf("%s", year_str);


		/* Check if input values are numbers */
		if (isNumber(day_str) && isNumber(month_str) && isNumber(year_str))
		{
			p_date->day = atoi(day_str);
			p_date->month = atoi(month_str);
			p_date->year = atoi(year_str);

			if (false == isValidDate(p_date->day, p_date->month, p_date->year))
			{
				error_flag = 1;
				continue;
			}
			break;
		}
		else
		{
			printf("\n[ERROR] Input can only be integer! Please try again...\n");
			error_flag = 1;
			continue;
		}
		break;
	} // End of while loop
}

bool isValidDate(int day, int month, int year)
{
	/* Check if input month value is out of range (1-12) */
	if (month < 1 || month > 12)
	{
		printf("\n[ERROR] Invalid month value! Please try again...\n");
		return false;
	}

	int month_length = getMonthDays(month, year);

	/* Check if input day value is out of range */
	if (day < 1 || day > month_length)
	{
		printf("\n[ERROR] Invalid day value! Please try again...\n");
		return false;
	}

	/* Check if input year value is less than 0 */
	else if (year < 0)
	{
		printf("\n[ERROR] Invalid year value! Please try again...\n");
		return false;
	}
	
	return true;
}

int getCode(void)
{
	/* Get input from keyboard hit */
	int ch = getch();

	/* Store key ASCII code */
	if (0 == ch || 224 == ch)
	{
		ch = 256 + getch();
	}

	/* Return key code */
	return ch;
}