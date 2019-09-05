/*
 * File name: setCursor.c
 *
 * Author: Mo Chen
 *
 * Description: c file to set cursor coordinates and property
 */

#include "setCursor.h"

void gotoxy(int x, int y)
{
	COORD coord;

	// Assign input x-y coordinates to COORD
	coord.X = x;
	coord.Y = y;

	// Set console cursor position with input coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD GetConsoleCursorPosition(void)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;

	// Retrieves information about the specified console screen buffer 
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void visibleCursor(int flag)
{
	// Get handle for standard output
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;

	// Get and set console cursor visibility
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = flag;
	SetConsoleCursorInfo(hOut, &cci);
}