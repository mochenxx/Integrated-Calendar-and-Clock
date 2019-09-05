/*
 * File name: timeInfo.h
 *
 * Author: Mo Chen
 *
 * Description: Header file for time information
 */

#ifndef _TIMEINFO_H_
#define _TIMEINFO_H_
#define TIME_SIZE 40

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

/*
 * This function gets the current month and year
 *
 * @param[in] pMonth - Pointer that points to current month number
 * @param[in] pYear - Pointer that points to current year number
 *
 * @returns - Nothing
 */
void getCurrentMonthYear(int* pMonth, int* pYear);

/*
 * This function prints the current YMDHMS data as a time stamp 
 * 
 * Example: Aug 15 2019 10:20:32 AM
 * 
 */
char* timestamp(void);

#endif // !_TIMEINFO_H_
