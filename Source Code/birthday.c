/*
 * File name: birthday.c
 *
 * Author: Mo Chen
 *
 * Purpose: c file for birthday information and functions
 */

#include "birthday.h"
#include "logFile.h"
#include "setColor.h"
#include "setCursor.h"

#pragma warning(disable : 4996)
unsigned int birthday_list_count = 0;			 // birthday list count number
BdayFileRecord birthday_list[BIRTHDAY_LIST_MAX]; // birthday list

const BdayFileRecord* getBirthdayList(void)
{
	return birthday_list;
}

unsigned int getBirthdayListCount(void)
{
	return birthday_list_count;
}

void addBirthRecord(BdayFileRecord* record)
{
	// Check if there is no more room in birthday list
	if (birthday_list_count == BIRTHDAY_LIST_MAX) {
		printf("\n[Error] Programmed is not designed for this many friends\n");
		exit(-1);
	}

	// Add record to birthday list, increment list count
	birthday_list[birthday_list_count] = *record;
	birthday_list_count++;
}

void addBirthday(Date* p_date)
{
	Birthday new_birthday = { 0 };
	
	// Store input date to new birthday date
	new_birthday.date = *p_date;

	// Get friend's name
	printf("\nWho's birthday is this day? ");
	(void)getchar();
	gets_s(new_birthday.name, 50);

	// Display entered birthday information
	printf("\n==>Birthday information has been successfully added!\n");
	printf("%s's Birthday: %d %d %d", 
			new_birthday.name,
			new_birthday.date.month, 
			new_birthday.date.day,
			new_birthday.date.year);

	// Check is birthday list reaches its maximum index
	if (birthday_list_count == BIRTHDAY_LIST_MAX) {
		printf("\n[Error] Programmed is not designed for this many friends\n");
		exit(-1);
	}

	// Add this new birthday to birthday list with local time
	birthday_list[birthday_list_count].birthday = new_birthday;
	birthday_list[birthday_list_count].time = time(NULL);
	birthday_list_count++;

	// Synchronize the contents of array with file
	syncToBdayFile();
}

bool isBirthday(unsigned char month, unsigned char day, unsigned int* index)
{
	unsigned int i;
	*index = 0;		// Index in birthday_list

	/* Traversal birthday_list to check if input date has a birthday */
	for ( i = 0; i < birthday_list_count; i++)
	{
		// Check month
		if (month != birthday_list[i].birthday.date.month) {
			continue;
		}

		// Check day
		if (day != birthday_list[i].birthday.date.day) {
			continue;
		}

		// Store index number in birthday list
		*index = i;
		return true;
	}

	return false;
}

void displayBirthdays(unsigned int month, 
					  unsigned int day, 
					  unsigned int* is_birthday,
					  unsigned int* is_birthday_list_index, 
					  unsigned int* num_bday)
{
	unsigned int i, count = 0;
	*is_birthday = 0;	// Flag indicates if there is a birthday
						// 0 by default

	/* Traversal birthday_list to check if input date has a birthday */
	for (i = 0; i < birthday_list_count; i++)
	{
		// Check month
		if (month != birthday_list[i].birthday.date.month) {
			continue;
		}

		// Check day
		if (day != birthday_list[i].birthday.date.day) {
			continue;
		}

		// Display birthday info
		printf("\n==>Name: %s\n   Birthday: %s %d %d\n", 
			birthday_list[i].birthday.name,
			month_names_abbr[birthday_list[i].birthday.date.month],
			birthday_list[i].birthday.date.day,
			birthday_list[i].birthday.date.year
		);

		*is_birthday = 1;	// Set flag to 1
		
		// Store index of birthday_list
		is_birthday_list_index[count] = i;	
	
		count++;
	}

	*num_bday = count;
	//return &birthday_list[i];
}

void askDeleteBday(unsigned int* is_birthday_list, unsigned int* length)
{
	unsigned char choice = 0;		// User's choice to delete birthday or not
	unsigned int delete_num = 0;	// Number of order for the friend
	char delete_name[51] = {0};		// Name string that will be deleted
	unsigned int i;

	// Get user choice for deleting birthday or not
	printf("\nDo you want to delete birthday? Y/N\n");
	choice = _getche();

	/* Check if input is 'y' OR 'Y' */
	if ('Y' == toupper(choice))
	{
		/* Check if there are multiple birthdays in the same day */
		if (*length > 1)
		{
			// Get the order number of birthday to be deleted
			printf("\nWhich birthday do you want to delete?" 
					"Enter the number:\n");
			(void)scanf_s("%d", &delete_num);

			// Decrement delete_num as the showing number is 
			// 1 greater than actual index in list
			delete_num--;

			// Store deleted friend's name
			strcpy_s(delete_name, 51,
				birthday_list[is_birthday_list[delete_num]].birthday.name);
		}
		else
		{
			// Store deleted friend's name
			strcpy_s(delete_name, 51, 
				birthday_list[is_birthday_list[delete_num]].birthday.name);
		}

		/* Delete selected friend's birthday info */
		for (i = is_birthday_list[delete_num]; i < birthday_list_count; i++)
		{
			birthday_list[i] = birthday_list[i + 1];
		}
		
		// Display success message to screen
		printf("\nYou've deleted %s's birthday!", delete_name);

		// Synchronize to birthday log file
		syncToBdayFile();
	}
}

void displayMonthlyBdays(unsigned int month, unsigned int year,
				   	     unsigned int* coord_x, unsigned int* coord_y)
{
	// number of days for a given month
	unsigned int month_len = getMonthDays(month, year); 
	unsigned int i, j;
	
	// Check if there is a birthday for everyday in a month
	for (i = 1; i <= month_len; i++)
	{
		// Check if there are birthdays for certain day
		for (j = 0; j < birthday_list_count; j++)
		{
			// Check month info
			if (month != birthday_list[j].birthday.date.month) {
				continue;
			}

			// Check day info
			if (i != birthday_list[j].birthday.date.day) {
				continue;
			}

			// If there is a birthday
			// Display friend's name
			setColor(BDAY_TEXT_COLOR);
			gotoxy(*coord_x, ++(*coord_y));
			printf("    - %s's Birthday:",
				birthday_list[j].birthday.name);

			// Display birthday info
			gotoxy(*coord_x, ++ * (coord_y));
			setColor(DEFAULT_TEXT_COLOR);
			printf("      %s %d, %d\n\n",
				month_names[birthday_list[j].birthday.date.month],
				birthday_list[j].birthday.date.day,
				birthday_list[j].birthday.date.year
			);
		}
	}
}