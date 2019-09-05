/*
 * File name: worldClock.h
 *
 * Author: Mo Chen
 *
 * Description: Header file for world clock functions
 */

#ifndef _WORLDCLOCK_H_
#define _WORLDCLOCK_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define WORLDCLOCK_LIST_MAX 50

/* Define World Clock structure */
typedef struct 
{
	char city[50];
	char country[50];
	int gmt_hour;
	int gmt_min;
} WorldClock;

/* Define World Clock File Record structure */
typedef struct  
{
	WorldClock clock_info;
	time_t log_time;
} WorldClockFileRecord;

/*
 * This function returns a pointer that points to world clock list
 * containing user-added world clock file records
 *
 * @returns - pointer to world clock list
 */
const WorldClockFileRecord* getWorldClockList(void);

/*
 * This function returns world clock list count (number of stored cities clocks)
 *
 * @returns - world clock list count value
 */
unsigned int getWorldClockCount(void);

/*
 * This function returns a pointer that points to available clocks list
 *
 * @returns - pointer to available clocks list
 */
const WorldClock* getAvailClocksList(void);

/*
 * This function returns available clock list count (number of clocks options)
 *
 * @returns - available clock list count
 */
unsigned int getAvailClocksListCount(void);

/*
 * This function adds a new world clock record to world clock list
 *
 * @param[in] record - pointer that point to the recored
 *
 * @returns - none
 */
void addWorldClockRecord(WorldClockFileRecord* record);

/*
 * This function adds available world clocks to available clock list
 *
 * @param[in] record - pointer that point to the recored
 *
 * @returns - none
 */
void addWorldClock(WorldClock* new_clock);

/*
 * This function displays clock information for certain city
 *
 * @param[in] p_clock - pointer that points to a certain city's clock info
 *
 * @returns - none
 */
void displayWorldClock(WorldClock* p_clock);

/*
 * This function displays world clock menu to screen
 *
 * @returns - none
 */
void displayWorldClockMenu(void);

/*
 * This function displays available cities clock info
 * and chooses clock info of certain city
 *
 * @returns - none
 */
unsigned int chooseClock(void);

/*
 * This function implements world clock function
 *
 * @returns - none
 */
void worldClock(void);

/*
 * This function delete clock info of a given city
 *
 * @param[in] key - user input key
 * @param[in] have_deleted_clock - a flag that indicates if this clock 
 *								   has been deleted
 *
 * @returns - none
 */
void deleteClOCK(char key, unsigned int* have_deleted_clock);

#endif // _WORLDCLOCK_H_
