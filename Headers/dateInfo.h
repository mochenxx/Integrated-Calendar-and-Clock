/*
 * File name: dateInfo.h
 *
 * Author: Mo Chen
 *
 * Purpose: Header file for date information
 */

#ifndef _DATEINFO_H_
#define _DATEINFO_H_

#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Check leap year */
#define LEAPYEAR(year) ((year % 400 == 0)\
						||((year % 4 == 0) && (year % 100 != 0)))

/* Date string maximum length */
#define DATE_MAX_LIMIT 10 

/* Name of 12 months */
static const char* month_names[] = {
	"MONTH_NAME_NONE",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
	"MONTH_NAME_MAX",
};

/* Abbreviation name of 12 months */
static const char* month_names_abbr[] = {
	"MONTH_NAME_NONE",
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC",
	"MONTH_NAME_MAX"
};

/* Define Date structure */
typedef struct
{
	int day;
	int month;
	int year;
} Date;

/*
 * This function returns the day of the week
 * for a given date - day/month/year
 * For e.g. -
 *
 *		Index		Day
 *		  0		   Sunday
 *		  1		   Monday
 *		  2		   Tuesday
 *		  3		   Wednesday
 *		  4		   Thursday
 *		  5		   Friday
 *		  6		   Saturday
 *
 * @param[in] day - input day of the month
 * @param[in] month - input month (1 = Jan, 2 = Feb, ...,12 = Dec)
 * @param[in] year - input year
 *
 * @returns - the day of the week (0 = Sun, 1 = Mon, ..., 5 = Fri, 6 = Sat)
 * 
 * Reference: en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#
 * Based on Disparate variation Algorithm
 */
int getDayOfWeek(unsigned int day, unsigned int month, unsigned int year);

/*
 * This function returns the number of days in a month
 *
 * For e.g. -
 *
 * Month Number	     Name	  Number of Days
 *		  1		   January			31
 *		  2		   February			28(non-leap) / 29 (leap year)
 *		  3		   March			31
 *		  4		   April			30
 *		  5		   May				31
 *		  6		   June				30
 *		  7		   July				31
 *		  8		   August			31
 *		  9		   September		30
 *		  10	   October			31
 *		  11	   November			30
 *		  12	   December			31
 *
 * @param[in] month - input month (1 = Jan, 2 = Feb, ...,12 = Dec)
 * @param[in] year - input year
 *
 * @returns - the number of days in a given month and year
 */
unsigned int getMonthDays(int month, int year);
#endif // !_DATEINFO_H_