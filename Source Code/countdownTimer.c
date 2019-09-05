/*
 * File name: countdownTimer.c
 *
 * Author: Mo Chen
 *
 * Purpose: c file for countdown timer information
 */

#include "countdownTimer.h"
#include "setColor.h"
#include "setCursor.h"
#include "print.h"

void displayTimerMenu(void)
{
	system("CLS");
	setColor(TEXT_COLOR_WHITE);
	printHeader();

	/* Display countdown timer menu */
	printf("   +------------------------------+");
	printf("\n   |     "); 
	setColor(TEXT_COLOR_YELLOW);
	printf("Dear Countdown Timer"); 
	setColor(TEXT_COLOR_WHITE);
	printf("     |");
	printf("\n   +------------------------------+");	
}

void timer(void)
{
	int hour = 0, minute = 0, second = 0, msecond = 0;
	unsigned int i;

	// Flags indicating if timer is started or is finished
	unsigned int is_started = 0, is_finished = 0; 
	// user choice from keyboard
	char key = 0, last_choice = 0;	

	displayTimerMenu();		// Display timer menu
	visibleCursor(1);		// Make cursor visible
	
	// Set up timer
	setColor(TEXT_COLOR_CYAN);
	gotoxy(5, 8);
	printf("Set time to countdown: ");
	gotoxy(5, 9);
	printf("Hours:    Min:    Sec:    ");
	gotoxy(11, 9);
	
	// Get hour, minute, and second
	setColor(TEXT_COLOR_WHITE);
	scanf_s("%d", &hour);
	gotoxy(19, 9);
	scanf_s("%d", &minute);
	gotoxy(27, 9);
	scanf_s("%d", &second);
	
	// Check if second is greater than 60
	if (second >= 60)
	{
		gotoxy(11, 11);
		printf("[ERROR] Invalid Input!");
		Sleep(1);

		timer();	// Go back to timer() function
	}
	// Check if second is greater than 60
	if (minute >= 60)
	{
		gotoxy(11, 11);
		printf("[ERROR] Invalid Input!");
		Sleep(1);
		
		timer();	// Go back to timer() function
	}
	else
	{
		// Hide cursor
		visibleCursor(0);	
		
		// Display instructions
		gotoxy(38, 8);
		printf("<Press Enter to start timer>");
		gotoxy(38, 9);
		printf("<Press 1 to Reset timer>");
		gotoxy(38, 10);
		printf("<Press 2 to Pause timer>");
		gotoxy(38, 11);
		printf("<Press 3 to Resume timer>");
		gotoxy(38, 12);
		printf("<Press ESC to Quit>");
		
		do
		{
			// Check if hit keyboard 'ESC'
			if (_kbhit() == 1)
			{
				key = _getch();
			}

			if (key == KEY_ESC)
			{
				// Set text color to white
				setColor(TEXT_COLOR_WHITE);
				break;
			}

			// Switch input key
			switch (key)
			{
				// Hit key 'Enter' - Start timer
				case KEY_ENTER:
				{
					is_started = 1;
					is_finished = 0;
					break;
				}

				// Hit key '1' - Reset timer
				case KEY_ONE:
				{
					timer();
					break;
				}

				// Hit key '2' - Pause timer
				case KEY_TWO:
				{
					is_started = 0;
					is_finished = 0;
					break;
				}

				// Hit key '3' - Resume timer
				case KEY_THREE:
				{
					is_started = 1;
					is_finished = 0;
					break;
				}

				default:
				{
					is_started = 0;
					is_finished = 0;
					break;
				}
			}

			// Check if timer is started
			if (1 == is_started)
			{
				// Start countdown timer
				if (key != KEY_TWO)
				{
					--msecond;
				}

				if (msecond <= 0)
				{
					--second;
					msecond = 99;

					if (second < 0)
					{
						--minute;
						second = 59;

						if (minute < 0)
						{
							--hour;
							minute = 59;

							if (hour < 0)
							{
								// Running out of time so set timer to zero
								hour = 0;
								minute = 0;
								second = 0;
								msecond = 0;
								
								// Display timer
								gotoxy(10, 12);
								setColor(TEXT_COLOR_LIGHTGREEN);
								printf(" %02d : %02d : %02d ", 
										minute, second, msecond);

								// Set flags value
								is_started = 0;
								is_finished = 1;	
							}
						}
					}
				}
				// Sleep for 10 ms
				Sleep(10);

				// Display timer info
				gotoxy(10, 12);
				setColor(TEXT_COLOR_LIGHTGREEN);
				printf(" %02d : %02d : %02d ", minute, second, msecond);
				last_choice = key;
			}

			// Check if timer is finished
			if (1 == is_finished)
			{
				// Beep signal sound
				for (i = 0; i < 2; i++)
				{
					Beep(5000, 150);
				}

				is_finished = 0;
				key = last_choice;
				
			}
		}while (key != KEY_ESC);
	} 
	
	return;
}
