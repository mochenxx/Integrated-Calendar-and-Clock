/*
 * File name: input.h
 *
 * Author: Mo Chen
 *
 * Description: Header file for user input
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "dateInfo.h"

/* System dependent key codes */
enum KEYCODE {
	KEY_ESC = 27,
	ARROW_UP = 256 + 72,
	ARROW_DOWN = 256 + 80,
	ARROW_LEFT = 256 + 75,
	ARROW_RIGHT = 256 + 77,
	KEY_ONE = 49,
	KEY_TWO = 50,
	KEY_THREE = 51,
	KEY_FOUR = 52,
	KEY_FIVE = 53,
	KEY_SIX = 54,
	KEY_SEVEN = 55,
	KEY_ENTER = 13,
	KEY_A_CAPITAL = 65,
	KEY_A = 97,
	KEY_D = 100,
	KEY_D_CAPITAL = 68
};

/* Get code from keyboard */
int getCode(void);

/*
 * This function checks if the input string is a number 
 *
 * @param[in] s[] - the string to be analyzed
 *
 * @returns - boolean value, is true if the input is a number
 */
bool isNumber(char s[]);

/*
 * This function gets input from the user keyboard 
 *
 * @param[in] pMonth - Pointer that points to input month
 * @param[in] pYear - Pointer that points to input year
 *
 * @returns - Nothing
 */
void inputMonthYear(int* p_month, int* p_year);

/*
 * This function gets input from the user keyboard
 *
 * @param[in] p_day - Pointer that points to input day
 * @param[in] p_month - Pointer that points to input month
 * @param[in] p_year - Pointer that points to input year
 *
 * @returns - Nothing
 */
void inputDate(Date* p_date, int cur_month, int cur_year);

/*
 * This function checks if the input date is valid
 *
 * @param[in] day - input day
 * @param[in] month - input month
 * @param[in] year - input year
 *
 * @returns - true if input date is valid otherwise false 
 */
bool isValidDate(int day, int month, int year);
#endif // !_INPUT_H_
