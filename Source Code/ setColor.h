/*
 * File name: setColor.h
 *
 * Author: Mo Chen
 *
 * Description: Header file to set different output color
 */

#ifndef _SETCOLOR_H_
#define _SETCOLOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/* Signs color of birthday, holiday, event in calendar */
#define BDAY_SIGN_COLOR 96
#define HOLIDAY_SIGN_COLOR 192
#define EVENT_SIGN_COLOR 48

/* Text color in calendar */
#define DEFAULT_TEXT_COLOR 15
#define BDAY_TEXT_COLOR 6
#define HOLIDAY_TEXT_COLOR 12
#define EVENT_TEXT_COLOR 9
#define TITLE_TEXT_COLOR 14
#define SUNDAY_TEXT_COLOR 12
#define SATURDAY_TEXT_COLOR 9
#define WEEKDAY_TEXT_COLOR 10

/* Text color options */
#define TEXT_COLOR_GREEN 2
#define TEXT_COLOR_CYAN 3
#define TEXT_COLOR_RED 4
#define TEXT_COLOR_MAGENTA 5
#define TEXT_COLOR_BROWN 6
#define TEXT_COLOR_LIGHTBLUE 9
#define TEXT_COLOR_LIGHTGREEN 10
#define TEXT_COLOR_LIGHTRED 12
#define TEXT_COLOR_LIGHTCYAN 11
#define TEXT_COLOR_YELLOW 14
#define TEXT_COLOR_WHITE 15

/*
 * This function shows various color options
 */
void color(void);

/*
 * This function set output color
 *
 * @param[in] k - output color code
 * 
 * @returns - Nothing
 */
void setColor(unsigned int k);

#endif // _SETCOLOR_H_
