#include "worldClock.h"
#include "setColor.h"
#include "input.h"
#include "print.h"
#include "setColor.h"
#include "setCursor.h"
#include "logFile.h"

/*
 * Disable warning of unsafe functions
 * _CRT_SECURE_NO_WARNINGS
 */
#pragma warning(disable : 4996)

// World clock list including user-added clocks info
unsigned int world_clock_list_count = 0;
WorldClockFileRecord world_clock_list[WORLDCLOCK_LIST_MAX];

// A list including all available clocks info
unsigned int avail_clocks_list_count = 0;
WorldClock avail_clocks_list[WORLDCLOCK_LIST_MAX];

const WorldClockFileRecord* getWorldClockList(void)
{
	return world_clock_list;
}

unsigned int getWorldClockCount(void)
{
	return world_clock_list_count;
}

const WorldClock* getAvailClocksList(void)
{
	return avail_clocks_list;
}

unsigned int getAvailClocksListCount(void)
{
	return avail_clocks_list_count;
}

void addWorldClockRecord(WorldClockFileRecord* record)
{
	// Check if world clock list is full
	if (world_clock_list_count == WORLDCLOCK_LIST_MAX)
	{
		printf("[ERROR] Program is not designed to add so many places!\n");
		exit(-1);
	}

	// Add new record to list
	world_clock_list[world_clock_list_count] = *record;
	world_clock_list_count++;
}

void addWorldClock(WorldClock* new_clock)
{
	// Check if available clock list is full
	if (avail_clocks_list_count == WORLDCLOCK_LIST_MAX)
	{
		printf("[ERROR] Program is not designed to add so many places!\n");
		exit(-1);
	}

	// Add new record to list
	avail_clocks_list[avail_clocks_list_count] = *new_clock;
	avail_clocks_list_count++;
}

void displayWorldClock(WorldClock *p_clock)
{
	time_t curtime = time(NULL);
	struct tm* ptime;
	int hour = 0;

	// Get GMT form of current time
	ptime = gmtime(&curtime);

	// Set GMT of input city
	hour = (ptime->tm_hour + p_clock->gmt_hour) % 24;

	// Check if hour of GMT is less than 24
	if ((ptime->tm_hour + p_clock->gmt_hour) % 24 < 0)
	{
		hour += 24;
	}

	// Print the current time 
	setColor(TEXT_COLOR_YELLOW);
	printf("%s", p_clock->city);
	setColor(TEXT_COLOR_WHITE);
	printf(" : %2d:%02d:%02d\n", 
			hour, 
			(ptime->tm_min + p_clock->gmt_min), 
			ptime->tm_sec);
}

void displayWorldClockMenu(void)
{
	system("CLS");
	setColor(TEXT_COLOR_WHITE);

	/* Print header */
	printHeader();
	
	/* Hide cursor */
	visibleCursor(0);

	/* Display stopwatch menu */
	printf("   +---------------------------+");
	printf("\n   |        ");
	setColor(TEXT_COLOR_YELLOW);
	printf("World Clock");
	setColor(TEXT_COLOR_WHITE);
	printf("        |");
	printf("\n   +---------------------------+");
	printf("\n   [ Press ESC for Main Menu. ]");
	printf("\n   [ Press A to Add New Clock ]");
}

void worldClock(void)
{
	char key = 0;
	unsigned int i, new_clock_idx = 0;
	unsigned int have_deleted_clock = 0;	// Flag indicating if a clock 
											// has been deleted

	displayWorldClockMenu();

	while(1)
	{
		// Check if hitting keyboard
		if (_kbhit() == 1)
		{
			// Get input key code
			key = _getch();
		}

		// Check if entered 'ESC' key
		if (KEY_ESC == key)
		{
			return;
		}

		// Check if entered 'A' or 'a' key - Add a clock info
		if (KEY_A == key || KEY_A_CAPITAL == key)
		{
			// Display world clock menu
			displayWorldClockMenu();

			// Choose a clock info from available cities
			gotoxy(4, 10);
			new_clock_idx = chooseClock();
			
			// Add clock info to world clock list
			world_clock_list[world_clock_list_count].clock_info =
				avail_clocks_list[new_clock_idx];

			// Add log time to world clock list
			world_clock_list[world_clock_list_count].log_time = time(NULL);

			// Increment world clock list count
			world_clock_list_count++;
			
			// Go back to worldClock() function
			worldClock();
		}

		// Display added world clocks
		for (i = 0; i < world_clock_list_count; i++)
		{
			gotoxy(4, 10+ 2*i);
			printf("%d) ", i + 1);
			displayWorldClock(&world_clock_list[i].clock_info);
		}

		// Check if a city's clock has been added
		if (world_clock_list_count > 0)
		{
			// Get delete choice
			deleteClOCK(key, &have_deleted_clock);
			key = 0;

			// Check if there is a city clock that has been deleted
			if (1 == have_deleted_clock)
			{
				// Go back to world clock function
				worldClock();
			}
		}
	}

	// Synchronize to world clock file
	syncToWorldClockFile();
}

unsigned int chooseClock(void)
{
	unsigned int i, choice;

	setColor(TEXT_COLOR_LIGHTRED);
	printf("Available clocks are as below:\n\n");

	// Get and store console cursor position
	COORD coord = GetConsoleCursorPosition();

	// Display available cities clocks info
	setColor(TEXT_COLOR_WHITE);
	for (i = 0; i < avail_clocks_list_count; i++)
	{
		// Set one column with 15 elements
		// If i is greater than 15, go to another column
		if (i >= 15)
		{
			gotoxy(33, coord.Y + 1* (i - 15));
		}

		// Print available cites with their countries name
		printf("      %d.  %s (%s)\n", 
				i + 1, 
				avail_clocks_list[i].city, 
				avail_clocks_list[i].country);
	}

	// Make cursor visible
	visibleCursor(1);

	// Get choice to add clock of a certain city
	gotoxy(4, coord.Y + 15);
	printf("Enter a number : ");
	(void)scanf("%d", &choice);
	
	// Return the index of selected city in avail_clock_list array
	return (choice - 1);
}

void deleteClOCK(char key, unsigned int *have_deleted_clock)
{
	unsigned delete_idx, i;
	*have_deleted_clock = 0;

	// Get and store console cursor position
	COORD coord = GetConsoleCursorPosition();

	printf("\nPress D to delete existing world clock\n");

	// Check if entered 'ESC' - return to previous function
	if (KEY_ESC == key)
	{
		return;
	}

	// Check if entered 'D' or 'd' - Delete a city clock
	if (KEY_D == key || KEY_D_CAPITAL == key)
	{
		gotoxy(coord.X, coord.Y + 1);

		// Get choice for deleting a clock
		printf("For Delete a clock - Press the number before its name: ");
		(void)scanf("%d", &delete_idx);

		// Print success message
		printf("\nYou've deleted the clock info for %s!\n",
			world_clock_list[delete_idx-1].clock_info.city);

		// Delete selected city clock in world clock list
		for (i = delete_idx - 1; i < world_clock_list_count; i++)
		{
			world_clock_list[i] = world_clock_list[i + 1];
		}

		// Decrement world list count
		world_clock_list_count--;

		// Set flag to 1
		*have_deleted_clock = 1;

		// Synchronize to world clock file
		syncToWorldClockFile();

		// Print pause message
		printPauseMsg();
	}
}