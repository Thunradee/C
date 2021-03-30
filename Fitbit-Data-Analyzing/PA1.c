/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 1: Analyzing Fitbit Data                                                            *
* Date: January 19, 2019                                                                                     *
* Description: This program cleans, analyzes Fitbit Data and reports the results and cleaned data set        *
*              to the report file and screen                                                                 *
*************************************************************************************************************/

#include "PA1.h"

/*************************************************************************************************************
* Method: myStrtok                                                                                           *
* Description: This method finds the delimiter, replaces it by null charecter                                *
*              and returns the pointer to the start                                                          *
*************************************************************************************************************/
char *myStrtok(char *str, char* delim)
{
	static char *start = NULL;
	char *token = NULL;
	// assign new string to the start point
	if (str)
		start = str;
	// if the string has no more token
	if (!start)
		return NULL;

	token = start;
	start = strpbrk(start, delim);

	if (start) {
		*start = '\0';
		++start;
	}

	return token;
}

/*************************************************************************************************************
* Method: cleanData                                                                                          *
* Description: This method replaces missing value by the error values                                        *
*************************************************************************************************************/
void cleanData(char *temp[])
{
	for (int i = 2; i < 7; ++i) {
		if (strcmp(temp[i], "") == 0) {
			temp[i] = &ERROR;
		}
	}
	if (strcmp(temp[7], "\n") == 0)
		temp[7] = &ZERO;
}

/*************************************************************************************************************
* Method: putTempToData                                                                                      *
* Description: This method stores data in the data array                                                     *
*************************************************************************************************************/
void putTempToData(FitbitData *data, int i, char *temp[])
{
	int j = 0;
	strcpy(data[i].patient, temp[j++]);
	strcpy(data[i].minute, temp[j++]);
	data[i].calories = atof(temp[j++]);
	data[i].distance = atof(temp[j++]);
	data[i].floors = atoi(temp[j++]);
	data[i].heartRate = atoi(temp[j++]);
	data[i].steps = atoi(temp[j++]);
	data[i].sleepLevel = atoi(temp[j++]);
}

/*************************************************************************************************************
* Method: findLongestPoorSleep                                                                               *
* Description: This method finds the longest consecutive poor sleep                                          *
*************************************************************************************************************/
void findLongestPoorSleep(FitbitData *data, int *poorSleepS, int *poorSleepE)
{
	int max = 0, curTotal = 0, start = 0, stop = 0, round = 0;
	for (int i = 0; i < 1440; ++i) {
		if (data[i].sleepLevel > 1) {
			curTotal += data[i].sleepLevel;
			++round;
			if (round == 1) {
				start = i;
			}
		}
		else {
			if (curTotal > max) {
				max = curTotal;
				*poorSleepS = start;
				*poorSleepE = start + round - 1;
			}
			round = 0;
		}
	}
}

/*************************************************************************************************************
* Method: calData                                                                                            *
* Description: This method analyze the Fitbit data                                                           *
* Precondition: cleaned data set                                                                             *
*************************************************************************************************************/
void calData(FitbitData *data, double *tolCals, double *tolDis, unsigned int *tolFls, unsigned int *tolSteps, double *avgHR, int *maxStepIndex, int *poorSleepS, int *poorSleepE)
{
	unsigned int tolHR = 0;
	int HRI = 0;
	unsigned int maxStep = data[0].steps;

	for (int i = 0; i < 1440; ++i) {
		if (data[i].calories < INTERROR) {
			// calculate the total calories
			*tolCals += data[i].calories;
		}
		if (data[i].distance < INTERROR) {
			// calculate the total distance
			*tolDis += data[i].distance;
		}
		if (data[i].floors < INTERROR) {
			// calculate the total floors
			*tolFls += data[i].floors;
		}
		if (data[i].steps < INTERROR) {
			// calculte the total steps
			*tolSteps += data[i].steps;
			// find max step
			if (data[i].steps >= maxStep) {
				maxStep = data[i].steps;
				*maxStepIndex = i;
			}
		}
		if (data[i].heartRate < INTERROR) {
			tolHR += data[i].heartRate;
			++HRI;
		}
		
	}
	// calculate the average of heart rate
	*avgHR = ((double)tolHR) / HRI;
	
	// find the longest consecutive range of poor sleep
	findLongestPoorSleep(data, poorSleepS, poorSleepE);
}

/*************************************************************************************************************
* Method: writeReport                                                                                        *
* Description: This method writes the result and the cleaned data set to the report file                     *
*************************************************************************************************************/
void writeReport(FILE *outfile, FitbitData *data, double tolCals, double tolDis, unsigned int tolFls, unsigned int tolSteps, double avgHR, int maxStepIndex, int poorSleepS, int poorSleepE)
{
	fprintf(outfile, "Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n");
	fprintf(outfile, "%lf,%lf,%d,%d,%lf,%d,%s:%s\n\n", tolCals, tolCals, tolFls, tolSteps, avgHR, data[maxStepIndex].steps, data[poorSleepS].minute, data[poorSleepE].minute);
	fprintf(outfile, "Target: ,%s,,,,,,\n", data[0].patient);
	fprintf(outfile, "Patient,minute,calories,distance,floors,heart,steps,sleep_level\n");
	for (int i = 0; i < 1440; ++i) {
		fprintf(outfile, "%s,%s,%lf,%lf,%d,%d,%d,%d\n", data[i].patient, data[i].minute, data[i].calories, data[i].distance, data[i].floors, data[i].heartRate, data[i].steps, data[i].sleepLevel);
	}
}

/*************************************************************************************************************
* Method: putResultOnScreen                                                                                  *
* Description: This method puts the results and the cleaned data set on the screen                           *
*************************************************************************************************************/
void putResultOnScreen(FitbitData *data, double tolCals, double tolDis, unsigned int tolFls, unsigned int tolSteps, double avgHR, int maxStepIndex, int poorSleepS, int poorSleepE)
{
	printf("Total Calories\tTotal Distance\tTotal Floors\tTotal Steps\tAvg Heartrate\tMax Steps\tSleep\n");
	printf("%lf\t%lf\t%d\t\t%d\t\t%lf\t%d\t\t%s:%s\n\n", tolCals, tolCals, tolFls, tolSteps, avgHR, data[maxStepIndex].steps, data[poorSleepS].minute, data[poorSleepE].minute);
	printf("Target: %s\n", data[0].patient);
	printf("Patient\tminute\tcalories\tdistance\tfloors\theart\tsteps\tsleep_level\n");
	for (int i = 0; i < 1440; ++i) {
		printf("%s\t%s\t%lf\t%lf\t%d\t%d\t%d\t%d\n", data[i].patient, data[i].minute, data[i].calories, data[i].distance, data[i].floors, data[i].heartRate, data[i].steps, data[i].sleepLevel);
	}
}