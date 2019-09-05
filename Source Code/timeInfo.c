/*
 * File name: timeInfo.c
 *
 * Author: Mo Chen
 *
 * Description: c file that gets time information
 */

#include "timeInfo.h"

 /*
  * Disable warning of unsafe functions
  * _CRT_SECURE_NO_WARNINGS
  */
#pragma warning(disable : 4996)

void getCurrentMonthYear(int* current_month, int* current_year)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);		// Get local time

	// Store current month and year
	*current_month = tm.tm_mon + 1;
	*current_year = tm.tm_year + 1900;
}

char* timestamp(void)
{
	static char time_buffer[TIME_SIZE];
	struct tm* tm;
	time_t now;

	// Get current time
	now = time(NULL);
	tm = localtime(&now);

	// Return a string representing a date and time using tm
	strftime(time_buffer, TIME_SIZE, "%d %b %Y %H:%M:%S", tm);
	return time_buffer;
}