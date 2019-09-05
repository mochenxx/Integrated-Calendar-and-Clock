/*
 * File name: holiday.c
 *
 * Author: Mo Chen
 *
 * Purpose: c file for holiday information and functions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "holiday.h"
#include "setColor.h"
#include "setCursor.h"

unsigned int holiday_list_count = 0;			// Holiday list count
HolidayFileRecord holiday_list[HOLIDAY_LIST_MAX];	// Holiday file record list

void addHolidayRecord(Holiday* record, unsigned char is_dynamic)
{
	// Check if list is full
	if (holiday_list_count == HOLIDAY_LIST_MAX) {
		printf("Error: Programmed is not designed for this many holidays\n");
		exit(-1);
	}

	// Add holiday record info to holiday list
	holiday_list[holiday_list_count].record = *record;
	holiday_list[holiday_list_count].is_dynamic = is_dynamic;
	holiday_list_count++;
}

bool isHoliday(unsigned int year, unsigned int month, 
			   unsigned int day, unsigned int* index)
{
	unsigned int i;
	*index = 0;		// Index of holiday in list if there is a holiday

	/* Check if there is a holiday on input date */
	for ( i = 0; i < holiday_list_count; i++)
	{
		/* Check if this date is a dynamic holiday */
		/* Since there is no need to check year value for static holidays*/
		if (1 == holiday_list[i].is_dynamic)
		{
			if ((year != holiday_list[i].record.date.year)) {
				continue;
			}
		}

		/* Check month */
		if (month != holiday_list[i].record.date.month) {
			continue;
		}
		
		/* Check day */
		if (day != holiday_list[i].record.date.day) {
			continue;
		}

		// Found corresponding holiday, store its index i
		*index = i;
		return true;
	}

	return false;
}

void displayHolidays(unsigned int year, 
		     unsigned int month, 
		     unsigned int day, 
		     unsigned int* is_holiday,
		     unsigned int* is_holiday_list, 
		     unsigned int* num_holiday)
{
	unsigned int i, count = 0;
	*is_holiday = 0;	// Flag indicating if there is no holiday on input date

	for (i = 0; i < holiday_list_count; i++)
	{
		/* Check if this date is a dynamic holiday */
		/* Since there is no need to check year value for static holidays*/
		if (1 == holiday_list[i].is_dynamic)
		{
			if ((year != holiday_list[i].record.date.year)) {
				continue;
			}
		}
		
		/* Check month value */
		if (month != holiday_list[i].record.date.month) {
			continue;
		}

		/* Check day value */
		if (day != holiday_list[i].record.date.day) {
			continue;
		}

		/* If input is a holiday, print that holiday's name and date */
		printf("\n==>Holiday: %s   Date: %s %d %d\n",
			holiday_list[i].record.name,
			month_names_abbr[month],
			day,
			year);
		
		
		*is_holiday = 1;		// Set flag to one	
		is_holiday_list[count] = i;	// Store holiday's index value i
		count++;			// Increment count
	}

	*num_holiday = count;	// Pass count value to *num_holiday
}

void displayMonthlyHolidays(unsigned int month,
			    unsigned int year,
			    unsigned int* coord_x,
			    unsigned int* coord_y)
{
	// Get number of days on input month
	unsigned int month_len = getMonthDays(month, year);
	unsigned int i, holiday_index = 0;

	// Check existing holidays on input month
	for (i = 1; i <= month_len; i++)
	{
		// Check existing holiday on certain day
		if (isHoliday(year, month, i, &holiday_index))
		{
			// Display event info
			setColor(HOLIDAY_TEXT_COLOR);
			++(*coord_y);
			gotoxy(*coord_x, *(coord_y));
			printf("    - Holiday: %s", holiday_list[holiday_index].record.name);
			
			gotoxy(*coord_x, ++*(coord_y));
			setColor(DEFAULT_TEXT_COLOR);
			printf("      Date: %s %d, %d\n\n",
				month_names[holiday_list[holiday_index].record.date.month],
				holiday_list[holiday_index].record.date.day,
				year);
		}
	}
}
