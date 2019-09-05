/*
 * File name: dateInfo.h
 *
 * Author: Mo Chen
 *
 * Purpose: Header file for holiday information
 */

#ifndef _HOLIDAY_H_
#define _HOLIDAY_H_

#include <stdbool.h>
#include "dateInfo.h"

#define HOLIDAY_LIST_MAX 1000

/* Define Holiday structure
 * including date info and holiday name
 */
typedef struct
{
	Date date;
	char name[50];
} Holiday;

/* Define Holiday File Record Structure
 * including date info and holiday name
 */
typedef struct
{
	Holiday record;
	unsigned int is_dynamic;
} HolidayFileRecord;

/*
 * This function adds holidays information on a given date
 *
 * param[in] record - pointer that points to new holiday record
 * param[in] is_dynamic - flag indicating whether it is a dynamic holiday
 *
 * returns - None
 */
void addHolidayRecord(Holiday* record, unsigned char is_dynamic);

/*
 * This function checks if there is a holiday on a given date
 *
 * param[in] year - input year
 * param[in] month - input month
 * param[in] day - input day
 * param[in] index - If there is a holiday,
 *		     then pass the index of holiday list to this param;
 *		   - Otherwise, it points to a zero value.
 *
 * returns - boolean value true if that date is a holiday, otherwise false
 */
bool isHoliday(unsigned int year, 
	       unsigned int month, 
	       unsigned int day,
	       unsigned int* index);

/*
 * This function display holidays information on certain date
 *
 * param[in] year - input year
 * param[in] month - input month
 * param[in] day - input day
 * param[in] is_holiday - A pointer that points to a integer value 1 / 0
 *						 -> 1 indicates there is an holiday on this date
 *						 -> 0 indicates there is no holiday on this date
 * param[in] is_holiday_list - Pointing to an array containing all index
 *							 of holiday list on this date
 * param[in] num_holiday - A pointer points to the number of holidays
 *
 * returns - none
 */
void displayHolidays(unsigned int year,
		     unsigned int month,
		     unsigned int day,
	             unsigned int* is_holiday,
	 	     unsigned int* is_holiday_list,
		     unsigned int* num_holiday);


/*
 * This function display monthly holiday information
 *
 * param[in] month - input month
 * param[in] year - input year
 * param[in] coord_x - pointer pointing to x-axis coordinate for output
 * param[in] coord_y - pointer pointing to y-axis coordinate for output
 *
 * returns - none
 */
void displayMonthlyHolidays(unsigned int month, 
			    unsigned int year,
			    unsigned int* coord_x, 
			    unsigned int* coord_y);
#endif
