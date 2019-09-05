/*
 * File name: logFile.h
 *
 * Author: Mo Chen
 *
 * Description: Header file to keep logs of holidays, birthdays, and events
 */

#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <stdio.h>
#include <time.h>
#include "birthday.h"
#include "holiday.h"
#include "event.h"
#include "worldClock.h"

#define BIRTHDAY_FILENAME "birthdays.dat"
#define HOLIDAY_STATIC_FILENAME "holidays_static.csv"
#define HOLIDAY_DYNAMIC_FILENAME "holidays_dynamic_copy.csv"
#define EVENT_FILENAME "events.dat"
#define WORLD_CLOCK_FILENAME "world_clock.csv"
#define WORLD_CLOCK_RECORD_FILENAME "world_clocks.dat"
#define BSIZE 80

/*
 * This function synchronizes birthday information to related log file
 *
 * @returns - nothing
 */
void syncToBdayFile(void);

/*
 * This function synchronizes event information to related log file
 *
 * @returns - nothing
 */
void syncToEventFile(void);

/*
 * This function synchronizes world clock information to related log file
 *
 * @returns - nothing
 */
void syncToWorldClockFile(void);

/*
 * This function reads the content of the birthday log file
 * and display them in screen
 *
 * @returns - nothing
 */
void readBdayFile(void);

/*
 * This function reads the content of the holiday log file
 * and display them in screen
 *
 * @returns - nothing
 */
void readHolidayFile(void);

/*
 * This function reads the content of the event log file
 * and display them in screen
 *
 * @returns - nothing
 */
void readEventFile(void);

/*
 * This function reads content of world clock file containing available cities
 * and display them in screen
 *
 * @returns - nothing
 */
void readWorldClockFile(void);

/*
 * This function reads the content of the world clock log file
 * and display them in screen
 *
 * @returns - nothing
 */
void readWorldClockLogFile(void);
#endif
