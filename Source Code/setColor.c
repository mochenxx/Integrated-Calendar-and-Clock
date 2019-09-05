/*
 * File name: setColor.c
 *
 * Author: Mo Chen
 *
 * Description: c file to set different output color
 */

#include "setColor.h"

void color(void)
{
	HANDLE hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices
	for (k = 1; k < 255; k++)
	{
		// pick the color attribute k you want
		SetConsoleTextAttribute(hConsole, k);
		printf("%d I want to be nice today!\n", k);
	}
}


void setColor(unsigned int k)
{
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// pick the color attribute k you want
	SetConsoleTextAttribute(hConsole, k);
}