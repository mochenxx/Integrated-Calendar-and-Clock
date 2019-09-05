/*
 * File name: birthday.h
 *
 * Author: Mo Chen
 *
 * Purpose: Header file for birthday information and functions
 */

#ifndef _BIRTHDAY_H_
#define _BIRTHDAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "dateInfo.h"

/* Define Birthday structure
 * including date info and friend's name 
 */
typedef struct{
	Date date;
	char name[50]; 
} Birthday;

/* Define Birthday Log File Record structure */
typedef struct {
	time_t time;			// Time that stored this birthday info
	Birthday birthday;		// Birthday information
} BdayFileRecord;

#define BIRTHDAY_LIST_MAX 250	// Maximum index of birthday list

/*
 * This function adds a new birthday to calendar
 * 
 * @param[in] p_date - pointer that points to new birthday date
 *
 * @returns - none
 */
void addBirthday(Date* p_date);

/*
 * This function adds a new birthday record to birthday list
 *
 * @param[in] record - pointer that point to the recored
 *
 * @returns - none
 */
void addBirthRecord(BdayFileRecord* record);

/*
 * This function returns a pointer that points to birthday list 
 * containing all birthday file records
 *
 * @returns - pointer to birthday list record
 */
const BdayFileRecord* getBirthdayList(void);

/*
 * This function returns birthday list count (number of stored birthdays)
 *
 * @returns - birthday list count value
 */
unsigned int getBirthdayListCount(void);

/*
 * This function checks if there is a birthday on a given date
 *
 * @param[in] month - input month
 * @param[in] day - input day
 * @param[in] index - If there is a birthday,
 *					 then pass the index of birthday list to this param;
 *				   - Otherwise, it points to a zero value.
 *
 * @returns - boolean value true if that date is a birthday, otherwise false
 */
bool isBirthday(unsigned char month, unsigned char day, unsigned int* index);

/*
 * This function display birthday information on certain date
 *
 * @param[in] month - input month
 * @param[in] day - input day
 * @param[in] is_birthday - A pointer that points to a integer value 1 / 0
 *						 -> 1 indicates this date is a birthday
 *						 -> 0 indicates this date is not a birthday
 * @param[in] is_birthday_list_index - Pointing to an array containing all index
 *									  of birthdays list on this date
 * @param[in] num_bday - A pointer points to the number of birthday on this date
 *
 * @returns - none
 */
void displayBirthdays(unsigned int month,
	unsigned int day,
	unsigned int* is_birthday,
	unsigned int* is_birthday_list_index,
	unsigned int* num_bday);

/*
 * This function asks if user wants to delete birthday on a given date, 
 * if so then delete corresponding info
 *
 * @param[in] is_birthday_list - Pointer points to a array that contains 
 *								all birthdays info for certain date
 * @param[in] length - The length of this array ( = number of birthdays)
 *
 * @returns - none
 */
void askDeleteBday(unsigned int* is_birthday_list, unsigned int* length);

/*
 * This function display monthly birthday information
 *
 * @param[in] month - input month
 * @param[in] year - input year
 * @param[in] coord_x - pointer pointing to x-axis coordinate for output
 * @param[in] coord_y - pointer pointing to y-axis coordinate for output
 *
 * @returns - none
 */
void displayMonthlyBdays(unsigned int month, unsigned int year,
				  	     unsigned int* coord_x, unsigned int* coord_y);
#endif
