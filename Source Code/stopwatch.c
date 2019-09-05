/*
 * File name: stopwatch.c
 *
 * Author: Mo Chen
 *
 * Description: c file that implements stopwatch functions
 */

#include "stopwatch.h"
#include "setColor.h"
#include "setCursor.h"
#include "print.h"

void displayStopwatchMenu(void)
{
	system("CLS");
	setColor(TEXT_COLOR_WHITE);
	printHeader();
	
	/* Display stopwatch menu */
	printf("\n   +--------------------------+");
	printf("\n   |     ");
	setColor(TEXT_COLOR_YELLOW);
	printf("Lovely Stopwatch");
	setColor(TEXT_COLOR_WHITE);
	printf("     |");
	printf("\n   +--------------------------+");
	printf("\n   [ Press ESC for Main Menu. ]");
	gotoxy(40, 5);
	setColor(TEXT_COLOR_LIGHTRED);
	printf("Laps:");

	// Display the instruction
	setColor(TEXT_COLOR_YELLOW);
	gotoxy(5, 12);
	printf("Press 1 to start watch        ");
}

void stopwatch(void)
{
	unsigned int msec = 0, sec = 0, minute = 0, hour = 0;
	unsigned int lap = 0, is_start = 0, hit_stop = 0;
	char choice = 'm', last_choice = 0;	// user choice from keyboard

	displayStopwatchMenu();
	
	/* Hide Cursor */
	visibleCursor(0);
	
	while (1)
	{
		setColor(TEXT_COLOR_YELLOW);

		// Check if user hit 'ESC' to go back to main menu
		if (_kbhit() == 1 && ((choice = _getch()) == 27))
		{
			setColor(DEFAULT_TEXT_COLOR);
			gotoxy(5, 14);

			/* Make Cursor visible */
			visibleCursor(1);
			break;
		}

		switch (choice)
		{
			// Check if user input nothing
			case 'm':
			{
				is_start = 0;
				hit_stop = 0;
				break;
			}

			// Start stopwatch
			case '1':
			{
				// Display instructions
				gotoxy(5, 12);
				printf("2.Stop    3.Reset    5.Lap\n");
				is_start = 1;
				hit_stop = 0;
				break;
			}

			// Stop watch
			case '2':
			{
				// Display instructions
				gotoxy(5, 12);
				printf("3.Reset    4.Resume    5.Lap\n");
				gotoxy(5, 13);
				is_start = 1;
				hit_stop = 1;
				break;
			}

			// Reset watch
			case '3':
			{
				displayStopwatchMenu();
				gotoxy(5, 12);
				msec = 0, sec = 0, minute = 0, hour = 0;
				choice = 'm';
				lap = 0;
				is_start = 0;
				hit_stop = 0;
				break;
			}

			// Resume watch
			case '4':
			{
				gotoxy(5, 12);
				printf("2.Stop    3.Reset    5.Lap  ");
				is_start = 1;
				hit_stop = 0;
				break;
			}

			// Record Lap
			case '5':
			{
				setColor(TEXT_COLOR_CYAN);
				gotoxy(50, 7 + (lap * 2));
				printf("%d : %d : %d : %d ", hour, minute, sec, msec);
				choice = last_choice;
				lap++;
				is_start = 1;
				hit_stop = 0;
				break;
			}

			default:
			{
				is_start = 0;
				hit_stop = 0;
				break;
			}
		}

		if (1 == is_start && 1 != hit_stop)
		{
			Sleep(10);

			/* Update stopwatch */
			if (choice != 'm' && choice != '2')
			{
				msec++;
			}
			if (99 == msec)
			{
				sec++;
				msec = 0;
			}
			if (59 == sec)
			{
				minute++;
				sec = 0;
			}
			if (59 == minute)
			{
				hour++;
				minute = 0;
			}
		}
		
		/* Display Stopwatch */
		setColor(TEXT_COLOR_LIGHTGREEN);
		gotoxy(7, 10);
		printf("%d : %d : %d : %d ", hour, minute, sec, msec);
		last_choice = choice;
	}
}