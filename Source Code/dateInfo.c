/*
 * File name: dateInfo.c
 *
 * Author: Mo Chen
 *
 * Description: c file that gets corresponding information on a given date
 */

#include "dateInfo.h"

int getDayOfWeek(unsigned int day, unsigned int month, unsigned int year)
{
	double d1;
	unsigned int i1, i2, i3;
	static int table[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; // Lookup table
	const int table_value = table[month-1];

	if (month < 3)
	{
		year--;
	}

	d1 = year;
	d1 = floor(d1 / 4);
	i1 = (unsigned int)d1;

	d1 = year;
	d1 = floor(year / 100);
	i2 = (unsigned int)d1;

	d1 = year;
	d1 = floor(year / 400);
	i3 = (unsigned int)d1;

	/* Return the day of the week */
	return (day + table[month-1] + year + year/4 - year/100 + year/400) % 7;
}

unsigned int getMonthDays(int month, int year)
{
	/* Array that includes number of days starting from January to December */
	unsigned int monthsDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	/* Check if input year is leak year */
	if (2 == month)
	{
		monthsDays[1] = LEAPYEAR(year) ? 29 : 28;
	}

	/* Return number of days in that month */
	return monthsDays[month - 1];
}