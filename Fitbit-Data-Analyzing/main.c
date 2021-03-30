/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 1: Analyzing Fitbit Data                                                            *
* Date: January 19, 2019                                                                                     *
* Description: This program cleans, analyzes Fitbit Data and reports the results and cleaned data set        *
*              to the report file and screen                                                                 *
*************************************************************************************************************/

#include "PA1.h"

int main(int argc, char *argv[])
{
	FILE *infile = NULL, *outfile = NULL;
	char line[100] = "", *delim = ",";
	char patient[10] = "", *temp[9];
	FitbitData data[1440];
	int i = 0;
	double tolCals = 0.0, tolDis = 0.0, avgHR = 0.0;
	unsigned int tolFls = 0, tolSteps = 0;
	int maxStepIndex = 0, poorSleepS = 0, poorSleepE = 0;

	infile = fopen("FitbitData.csv", "r");

	// opened file succesfully
	if (infile != NULL) {
		int j = 0;
		// read the first line from the file
		fgets(line, 100, infile);
		// store the patient ID
		temp[j] = strtok(line, delim);
		temp[j] = strtok(NULL, delim);
		strcpy(patient, temp[j]);
		// read the second line from the file
		fgets(line, 100, infile);
		

		// read all the transection and store to data array
		while ((!feof(infile)) && fgets(line, 100, infile)) {
			j = 0;
			temp[j] = myStrtok(line, delim);
			// if the patient ID is the same as the target ID
			if (strcmp(temp[j], patient) == 0) {
				// seperate the rest of the line
				while (temp[j] != NULL) {
					++j;
					temp[j] = myStrtok(NULL, delim);
				}
				if (i > 0) {
					// check the duplicated minite
					if (strcmp(temp[1], data[i - 1].minute) != 0) {
						cleanData(temp);
						putTempToData(data, i++, temp);
					}
				}
				else {
					cleanData(temp);
					putTempToData(data, i++, temp);
				}
			}
		}
		calData(data, &tolCals, &tolDis, &tolFls, &tolSteps, &avgHR, &maxStepIndex, &poorSleepS, &poorSleepE);
		// open the file in writing mode for the report
		outfile = fopen("Results.csv", "w");
		// write the report to the file
		writeReport(outfile, data, tolCals, tolDis, tolFls, tolSteps, avgHR, maxStepIndex, poorSleepS, poorSleepE);
		// output the report to the screen
		putResultOnScreen(data, tolCals, tolDis, tolFls, tolSteps, avgHR, maxStepIndex, poorSleepS, poorSleepE);
	}

	// close all files
	fclose(infile);
	fclose(outfile);

	return 0;
}