/*
 * File name: setCursor.h
 *
 * Author: Mo Chen
 *
 * Description: Header file to set cursor coordinates and property
 */

#ifndef _SETCURSOR_H_
#define _SETCURSOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/*
 * This function sets cursor to certain coordinates
 *
 * @param[in] x - x-axis coordinate
 * @param[in] y - y-axis coordinate
 *
 * @returns - Nothing
 */
void gotoxy(int x, int y);

/*
 * This function gets current position of cursor
 *
 * @returns - Coordinates of current cursor
 */
COORD GetConsoleCursorPosition(void);

/*
 * This function changes the visibility of cursor
 *
 * @param[in] flag - an integer indicating whether cursor is visible
 *                 -> 1 to make cursor visible
 *			 	   -> 0 to hide cursor
 * 
 * @returns - None
 */
void visibleCursor(int flag);

#endif
