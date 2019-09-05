/*
 * File name: logFile.c
 *
 * Author: Mo Chen
 *
 * Description: c file to keep logs of holidays, birthdays, and events
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "logFile.h"
#include "timeInfo.h"

 /*
  * Disable warning of unsafe functions
  * _CRT_SECURE_NO_WARNINGS
  */
#pragma warning(disable : 4996)

/************************ Birthday Log-file Management ************************/
void syncToBdayFile(void)
{
	FILE* fp;
	size_t ret_val;		// Return value from fwrite()
	const BdayFileRecord* list = getBirthdayList();
	unsigned int list_count = getBirthdayListCount();

	fp = fopen(BIRTHDAY_FILENAME, "wb");	// delete everything and start again

	/* Check if file cannot be opened */
	if (NULL == fp) {
		
		/* Print error message and then exit */
		printf("\n\n[ERROR] Could not open birthday file!\n");
		exit(1);
	}

	for (unsigned int i = 0; i < list_count; i++) {

		/* Write record information to log file */
		ret_val = fwrite(&list[i], sizeof(list[i]), 1, fp);

		/* Check if return value is zero */
		if (0 == ret_val) {
			/* Print error message and then exit */
			printf("\n\n[ERROR] Could not write to file!\n");
			exit(1);
		}
	}

	fclose(fp);
}

void readBdayFile(void)
{
	BdayFileRecord new_record = { 0 };

	// Open file with read binary mode
	FILE* fp = fopen(BIRTHDAY_FILENAME, "rb");

	/* Check if file can be opened */
	if (fp == NULL) {
		
		// Display error message
		perror("\n\n[ERROR]Unable to open birthday file !");

		// Program exits when encountering an error
		exit(1);
	}

	/* Read log file records and display them */
	while (fread(&new_record, sizeof(new_record), 1, fp)) {
		
		/* Add new birthday record to birthday list */
		addBirthRecord(&new_record);
	}

	fclose(fp);
}

/************************ Holiday Log-file Management ************************/
void readHolidayFile(void)
{
	Holiday new_record = { 0 };
	unsigned char buffer[BSIZE] = { 0 };
	char* field;
	int year = 0, month, day;
	char holiday_name[50];

	/****************** Open the static holiday csv file ******************/
	FILE* fp_static = fopen(HOLIDAY_STATIC_FILENAME, "r");

	/* Check if csv file can be opened */
	if (fp_static == NULL) {
		
		// Display error message
		perror("\n[ERROR]Unable to open static holidays file!\n");
		exit(1);
	}

	/* Process the data */
	while (fgets(buffer, BSIZE, fp_static))
	{
		/* Get year */
		field = strtok(buffer, ",");
		month = atoi(field);

		/* Get month */
		field = strtok(NULL, ",");
		day = atoi(field);

		/* Get holiday name */
		field = strtok(NULL, ",");
		strcpy(holiday_name, field);

		/* Store input date info to new record */
		new_record.date.year = 0;
		new_record.date.month = month;
		new_record.date.day = day;
		strcpy(new_record.name, holiday_name);

		/* Add new holiday record to holiday list */
		addHolidayRecord(&new_record, 0);
	}

	fclose(fp_static);

	/****************** Open the dynamic holiday csv file ******************/
	// Dynamic holidays change vary year to year
	FILE* fp_dynamic = fopen(HOLIDAY_DYNAMIC_FILENAME, "r");

	/* Check if csv file can be opened */
	if (fp_dynamic == NULL) {
		
		// Display error message
		perror("\n[ERROR]Unable to open dynamic holidays file!\n");
		exit(1);
	}

	/* Process the data */
	while (fgets(buffer, BSIZE, fp_dynamic))
	{
		/* Get year */
		field = strtok(buffer, ",");
		year = atoi(field);

		/* Get month */
		field = strtok(NULL, ",");
		month = atoi(field);

		/* Get day */
		field = strtok(NULL, ",");
		day = atoi(field);
		
		/* Get holiday name */
		field = strtok(NULL, ",");
		strcpy(holiday_name, field);

		/* Store input date info to new record */
		new_record.date.year = year;
		new_record.date.month = month;
		new_record.date.day = day;
		strcpy(new_record.name, holiday_name);

		/* Add new holiday record to holiday list */
		addHolidayRecord(&new_record, 1);
	}

	fclose(fp_dynamic);
}

/************************ Event Log-file Management ************************/
void syncToEventFile(void)
{
	FILE* fp;
	size_t ret_val;		// Return value from fwrite()
	const EventFileRecord* list = getEventList();
	unsigned int list_count = getEventListCount();

	fp = fopen(EVENT_FILENAME, "wb");	// delete everything and start again

	/* Check if file cannot be opened */
	if (NULL == fp) {
		
		/* Print error message and then exit */
		printf("\n\n[ERROR] Could not open event file %s!\n", EVENT_FILENAME);
		exit(1);
	}

	for (unsigned int i = 0; i < list_count; i++) {

		/* Write record information to log file */
		ret_val = fwrite(&list[i], sizeof(list[i]), 1, fp);

		/* Check if return value is zero */
		if (0 == ret_val) {
			
			/* Print error message and then exit */
			printf("\n\n[ERROR] Could not write to file!\n");
			exit(1);
		}
	}

	fclose(fp);
}

void readEventFile(void)
{
	EventFileRecord new_record = { 0 };

	// Open file with read binary mode
	FILE* fp = fopen(EVENT_FILENAME, "rb");

	/* Check if file can be opened */
	if (fp == NULL) {
		// Display error message
		perror("\n\n[ERROR]Unable to open file!");

		// Program exits when encountering an error
		exit(1);
	}

	/* Read events log file records and display them */
	while (fread(&new_record, sizeof(new_record), 1, fp)) {
		
		/* Add new event record to event list */
		addEventRecord(&new_record);
	}

	fclose(fp);
}

/********************* World Clock Log-file Management *********************/
void readWorldClockFile(void)
{
	WorldClock new_clock = { 0 };
	unsigned char buffer[BSIZE] = { 0 };
	char* field;
	int new_hour = 0;
	unsigned int new_min = 0;

	/****************** Open the world clock csv file ******************/
	FILE* fp = fopen(WORLD_CLOCK_FILENAME, "r");

	/* Check if csv file can be opened */
	
	if (fp == NULL)
	{
		// Display error message
		printf("\n[ERROR] Unable to open world clock file!\n");
		exit(1);
	}

	/* Process the data */
	while (fgets(buffer, BSIZE, fp))
	{
		/* Get city name */
		field = strtok(buffer, ",");
		strcpy(new_clock.city, field);

		/* Get country name */
		field = strtok(NULL, ",");
		strcpy(new_clock.country, field);

		/* Get GMT Hour Part */
		field = strtok(NULL, ",");
		new_clock.gmt_hour = atoi(field);

		/* Get GMT Minute Part */
		field = strtok(NULL, ",");
		new_clock.gmt_min = atoi(field);

		/* Add new world clock info to world clock list */
		addWorldClock(&new_clock);
	}
	
	fclose(fp);
}

void syncToWorldClockFile(void)
{
	FILE* fp;
	size_t ret_val;		// Return value from fwrite()
	const WorldClockFileRecord* list = getWorldClockList();
	unsigned int list_count = getWorldClockCount();
	unsigned int i;

	// Delete everything in world clock log file and start again
	fp = fopen(WORLD_CLOCK_RECORD_FILENAME, "wb");	

	/* Check if file cannot be opened */
	if (NULL == fp) {

		/* Print error message and then exit */
		printf("\n\n[ERROR] Could not open event file %s!\n", 
				WORLD_CLOCK_RECORD_FILENAME);
		exit(1);
	}

	for ( i = 0; i < list_count; i++) {

		/* Write record information to log file */
		ret_val = fwrite(&list[i], sizeof(list[i]), 1, fp);

		/* Check if return value is zero */
		if (0 == ret_val) {

			/* Print error message and then exit */
			printf("\n\n[ERROR] Could not write to file!\n");
			exit(1);
		}
	}

	fclose(fp);
}

void readWorldClockLogFile(void)
{
	WorldClockFileRecord new_record = { 0 };
	unsigned char buffer[BSIZE] = { 0 };
	int new_hour = 0;
	unsigned int new_min = 0;

	/****************** Open the world clock csv file ******************/
	FILE* fp = fopen(WORLD_CLOCK_RECORD_FILENAME, "rb");

	/* Check if file can be opened */
	if (fp == NULL) {
		// Display error message
		perror("\n\n[ERROR]Unable to open world clock log file !");

		// Program exits when encountering an error
		exit(1);
	}

	/* Read log file records and display them */
	while (fread(&new_record, sizeof(new_record), 1, fp))
	{
		/* Add new world clock record to world clock record list */
		addWorldClockRecord(&new_record);
	}

	fclose(fp);
}
