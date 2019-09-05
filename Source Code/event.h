/*
 * File name: event.h
 *
 * Author: Mo Chen
 *
 * Purpose: Header file for event information and functions
 */

#ifndef _EVENT_H_
#define _EVENT_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dateInfo.h"
#include "setColor.h"

/* Event list maximum length */
#define EVENT_LIST_MAX 500 	  

/* Define Event Time Structure */
typedef struct
{
	int start_hour;
	int start_minute;
	int end_hour;
	int end_minute;
} EventTime;

/* Define Event Structure */
typedef struct  
{
	Date date;
	EventTime time;
	char title[50];
	char place[50];
} Event;

/* Define Event File Record Structure */
typedef struct
{
	Event record;
	time_t creaed_time;
} EventFileRecord;

/*
 * This function adds event information for a given date
 *
 * @param[in] new_date - a pointer pointing to input date to add event
 *
 * @returns - None
 */
void addEvent(Date* new_date);

/*
 * This function adds event information for a given date
 *
 * @param[in] record - pointer that points to new event record
 *
 * @returns - None
 */
void addEventRecord(EventFileRecord* record);

/*
 * This function returns a pointer that points to event list
 * containing all event file records
 *
 * @returns - Address of Event file record
 */
const EventFileRecord* getEventList(void);

/*
 * This function returns event list count (number of stored events)
 *
 * @returns - event list count value
 */
unsigned int getEventListCount(void);

/*
 * This function checks if there is a event on a given date
 *
 * @param[in] year - input year
 * @param[in] month - input month
 * @param[in] day - input day
 * @param[in] index - If there is a event,
 *		      then pass the index of event list to this param;
 *	            - Otherwise, it points to a zero value.
 *
 * @returns - boolean value true if that date is a event, otherwise false
 */
bool isEvent(unsigned int year, unsigned int month, unsigned int day, 
			 unsigned int* index);

/*
 * This function display event information on certain date
 *
 * @param[in] year - input year
 * @param[in] month - input month
 * @param[in] day - input day
 * @param[in] is_event - A pointer that points to a integer value 1 / 0
 *						 -> 1 indicates there is an event on this date
 *						 -> 0 indicates there is no event on this date
 * @param[in] is_event_list - Pointing to an array containing all index
 *							 of event list on this date
 * @param[in] num_event - A pointer points to the number of event on this date
 *
 * @returns - none
 */
void displayEvents(unsigned int year,
	unsigned int month,
	unsigned int day,
	unsigned int* is_event,
	unsigned int* is_event_list,
	unsigned int* num_event);

/*
 * This function display monthly event information
 *
 * @param[in] month - input month
 * @param[in] year - input year
 * @param[in] coord_x - pointer pointing to x-axis coordinate for output
 * @param[in] coord_y - pointer pointing to y-axis coordinate for output
 *
 * @returns - none
 */
void displayMonthlyEvents(unsigned int month, unsigned int year,
			  unsigned int* coord_x, unsigned int* coord_y);

/*
 * This function asks if user wants to delete event on a given date,
 * if so then delete corresponding info
 *
 * @param[in] is_event_list - Pointer points to a array that contains
 *							 all events info on certain date
 * @param[in] length - The length of this array ( = number of events)
 *
 * @returns - none
 */
void askDeleteEvent(unsigned int* is_event_list, unsigned int* length);
#endif
