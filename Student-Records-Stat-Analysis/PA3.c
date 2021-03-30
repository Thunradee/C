// function definitions file
// includes the header file
#include "PA3.h"

// reads one double precision number from the input file
double read_double(FILE *infile) {
	double value = 0.0;

	fscanf(infile, "%lf", &value);

	return value;
}

// reads one integer number from the input file
int read_integer(FILE *infile) {
	int value = 0;

	fscanf(infile, "%d", &value);

	return value;
}

// finds the sum of number1, number2, number3, number4, and number5 and returns the result
double calculate_sum(double number1, double number2, double number3, double number4, double number5) {
	double sum = 0.0;

	sum = number1 + number2 + number3 + number4 + number5;

	return sum;
}

// determines the mean
double calculate_mean(double sum, int number) {
	double mean = 0.0;

	if (number != 0) {
		mean = sum / number;
		return mean;
	}
	else {
		return -1.0;
	}
}

// Determines the deviation of number from the mean
double calculate_deviation(double number, double mean) {
	double deviation = 0.0;

	deviation = number - mean;

	return deviation;
}

// Determines the variance
double calculate_variance(double deviation1, double deviation2, double deviation3, double deviation4, double deviation5, int number) {
	double variance = 0.0;

	variance = (pow(deviation1, 2) + pow(deviation2, 2) + pow(deviation3, 2) + pow(deviation4, 2) + pow(deviation5, 2)) / number;

	return variance;
}

//Calculates the standard deviation
double calculate_standard_deviation(double variance) {
	double std_deviation = 0.0;

	std_deviation = sqrt(variance);

	return std_deviation;
}

//Determines the maximum number out of the five input parameters
double find_max(double number1, double number2, double number3, double number4, double number5) {
	double max = number1;

	if (number2 > max) {
		max = number2;
	}
	if (number3 > max) {
		max = number3;
	}
	if (number4 > max) {
		max = number4;
	}
	if (number5 > max) {
		max = number5;
	}

	return max;
}

//Determines the minimum number out of the five input parameters
double find_min(double number1, double number2, double number3, double number4, double number5) {
	double min = number1;

	if (number2 < min) {
		min = number2;
	}
	if (number3 < min) {
		min = number3;
	}
	if (number4 < min) {
		min = number4;
	}
	if (number5 < min) {
		min = number5;
	}

	return min;
}

//Prints a double precision number (to the hundredths place) to an output file
void print_double(FILE *outfile, double number) {
	fprintf(outfile, "%.2lf\n", number);
}