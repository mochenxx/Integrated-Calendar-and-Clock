/*
 * File name: event.c
 *
 * Author: Mo Chen
 *
 * Purpose: c file for birthday information and functions
 */

#include "event.h"
#include "logFile.h"
#include "setColor.h"
#include "setCursor.h"

#pragma warning(disable : 4996)
unsigned int event_list_count = 0;
EventFileRecord event_list[EVENT_LIST_MAX];

void addEvent(Date* new_date)
{
	Event new_event = { 0 };

	// Add new date to new_event structure
	new_event.date = *new_date;
	
	// Print input date for new event for checking
	printf("\n------- Add New Event on %s %d, %d-------\n", 
		month_names_abbr[new_date->month], 
		new_date->day, 
		new_date->year);

	// Get event title
	printf("Enter title: ");	
	(void)getchar();
	gets_s(new_event.title, 50);
	
	// Get event location
	printf("Add location: ");
	gets_s(new_event.place, 50);

	// Get starting time
	printf("Starts (format is HH:MM): ");
	(void)scanf("%d:%d", &new_event.time.start_hour,
						   &new_event.time.start_minute);

	// Get ending time
	printf("Ends (format is HH:MM): ");
	(void)scanf("%d:%d", &new_event.time.end_hour, 
						   &new_event.time.end_minute);

	// Print success Info
	printf("\nEvent information has been successfully added!\n");
	printf("\nEvent: %s\n%02d:%02d - %02d:%02d at %s\n", 
		new_event.title, 
		new_event.time.start_hour, new_event.time.start_minute,
		new_event.time.end_hour, new_event.time.end_minute,
		new_event.place);

	// Check if list is full
	if (event_list_count == EVENT_LIST_MAX) {
		printf("\n[Error] Programmed is not designed for this many events!\n");
		exit(-1);
	}

	// Add new event to event list
	event_list[event_list_count].record = new_event;
	event_list[event_list_count].creaed_time = time(NULL);
	event_list_count++;

	// Synchronize the contents of array with file
	syncToEventFile();
}

void addEventRecord(EventFileRecord* record)
{
	// Check if event list is full 
	if (event_list_count == EVENT_LIST_MAX) {
		printf("\n[Error] Programmed is not designed for this many events!\n");
		exit(-1);
	}

	// Add event record to event list
	event_list[event_list_count] = *record;
	event_list_count++;
}

const EventFileRecord* getEventList(void)
{
	return event_list;
}

unsigned int getEventListCount(void)
{
	return event_list_count;
}

bool isEvent(unsigned int year, unsigned int month, unsigned int day,
			 unsigned int* index)
{
	unsigned int i;
	*index = 0;		// Index of event in event list 
					// if an event exists on this day

	// Check if there is an event
	for ( i = 0; i < event_list_count; i++)
	{
		if (year != event_list[i].record.date.year) {
			continue;
		}
		if (month != event_list[i].record.date.month) {
			continue;
		}

		if (day != event_list[i].record.date.day) {
			continue;
		}

		// Found corresponding event, store its index i
		*index = i;

		return true;
	}

	return false;
}

void displayEvents (unsigned int year, 
					  unsigned int month, 
					  unsigned int day,
					  unsigned int* is_event,
					  unsigned int* is_event_list, 
					  unsigned int* num_event)
{
	unsigned int i, count = 0;
	*is_event = 0;	// Flag that indicate if there is an event on input date

	// Check for existing events
	for (i = 0; i < event_list_count; i++)
	{
		if (year != event_list[i].record.date.year) {
			continue;
		}
		if (month != event_list[i].record.date.month) {
			continue;
		}

		if (day != event_list[i].record.date.day) {
			continue;
		}

		// Display event information
		printf("\n==>Event: %s\n   Time: %s %d, %d %d:%02d - %d:%02d at %s\n",
			event_list[i].record.title,
			month_names_abbr[event_list[i].record.date.month],
			event_list[i].record.date.day,
			event_list[i].record.date.year,
			event_list[i].record.time.start_hour, 
			event_list[i].record.time.start_minute,
			event_list[i].record.time.end_hour, 
			event_list[i].record.time.end_minute,
			event_list[i].record.place);

		*is_event = 1;				// Set flag to 1
		is_event_list[count] = i;	// Store its index i to a list
		count++;					// Increment count
	}
	*num_event = count;
}

void displayMonthlyEvents(unsigned int month, unsigned int year,
						  unsigned int* coord_x, unsigned int* coord_y)
{
	// Get number of days on input month
	unsigned int month_len = getMonthDays(month, year);
	unsigned int i, j, event_index = 0;

	// Check existing events on input month
	for (i = 1; i <= month_len; i++)
	{
		// Check if there is an event on certain date
		for (j = 0; j < event_list_count; j++)
		{
			// Check year info
			if (year != event_list[j].record.date.year) {
				continue;
			}

			// Check month info
			if (month != event_list[j].record.date.month) {
				continue;
			}

			// Check day info
			if (i != event_list[j].record.date.day) {
				continue;
			}
			
			// Display event info
			setColor(EVENT_TEXT_COLOR);
			gotoxy(*coord_x, ++(*coord_y));
			printf("    - Event: %s\n", event_list[j].record.title);

			setColor(DEFAULT_TEXT_COLOR);
			gotoxy(*coord_x, ++(*coord_y));
			printf("      Time: %s %d, %d %02d:%02d - %02d:%02d at %s\n",
				month_names_abbr[event_list[j].record.date.month],
				event_list[j].record.date.day,
				event_list[j].record.date.year,
				event_list[j].record.time.start_hour,
				event_list[j].record.time.start_minute,
				event_list[j].record.time.end_hour,
				event_list[j].record.time.end_minute,
				event_list[j].record.place);
		}
	}
}

void askDeleteEvent(unsigned int* is_event_list, unsigned int* length)
{
	char choice = '\0';
	unsigned int delete = 0;
	unsigned int i;

	/* Get choice for deleting an event */
	printf("\nDo you want to delete event? Y/N\n");
	choice = _getche();

	/* Check if user wants to delete event */
	if ('Y' == toupper(choice))
	{
		/* Check if there are multiple birthdays in the same day */
		if (*length > 1)
		{
			/* Get user choice for deleting */
			printf("Which event do you want to delete?\n"
				"Enter the number(1,2,3 ...): ");
			(void)scanf("%d", &delete);
			delete--;
		}

		/* Delete selected event */
		for (i = is_event_list[delete]; i < event_list_count; i++)
		{
			event_list[i] = event_list[i + 1];
		}

		/* Print success message */
		printf("\nYou've deleted event!\n");

		/* Synchronize the contents of array with file */
		syncToEventFile();
	}
}