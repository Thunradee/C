/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 1: Analyzing Fitbit Data                                                            *
* Date: January 19, 2019                                                                                     *
* Description: This program cleans, analyzes Fitbit Data and reports the results and cleaned data set        *
*              to the report file and screen                                                                 *
*************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR "1000000"
#define ZERO "0"
#define INTERROR 1000000

typedef enum sleep
{
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit
{
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

char *myStrtok(char *str, char* delim);
void cleanData(char *temp[]);
void putTempToData(FitbitData *data, int i, char *temp[]);
void findLongestPoorSleep(FitbitData *data, int *poorSleepS, int *poorSleepE);
void calData(FitbitData *data, double *tolCals, double *tolDis, unsigned int *tolFls, unsigned int *tolSteps, double *avgHR, int *maxStepIndex, int *poorSleepS, int *poorSleepE);
void writeReport(FILE *outfile, FitbitData *data, double tolCals, double tolDis, unsigned int tolFls, unsigned int tolSteps, double avgHR, int maxStepIndex, int poorSleepS, int poorSleepE);
void putResultOnScreen(FitbitData *data, double tolCals, double tolDis, unsigned int tolFls, unsigned int tolSteps, double avgHR, int maxStepIndex, int poorSleepS, int poorSleepE);