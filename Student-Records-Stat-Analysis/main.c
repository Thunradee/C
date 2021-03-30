/*
Programmer: Thunradee Tangsupakij
Class: CptS 121, Fall 2018, section 1
Programming Assignment 3: Statistical Analysis of Student Records
Date: 9/19/18
Description: This program reads data from an input file, evaluates the data and writes the result on an output file.
*/
// include the header file
#include"PA3.h"

int main(void) {

	// declairs and initializes the variables
	FILE *infile = NULL, *outfile = NULL;
	int id = 0, class_standing1 = 0, class_standing2 = 0, class_standing3 = 0, class_standing4 = 0, class_standing5 = 0, number = 5;
	double gpa1 = 0.0, gpa2 = 0.0, gpa3 = 0.0, gpa4 = 0.0, gpa5 = 0.0, age1 = 0.0, age2 = 0.0, age3 = 0.0, age4 = 0.0, age5 = 0.0;
	double sum_gpa = 0.0, mean_gpa = 0.0, sum_class_standing = 0.0, mean_class_standing = 0.0, sum_age = 0.0, mean_age = 0.0;
	double deviation1 = 0.0, deviation2 = 0.0, deviation3 = 0.0, deviation4 = 0.0, deviation5 = 0.0, variance = 0.0, std_deviation = 0.0;
	double min = 0.0, max = 0.0;

	infile = fopen("input.dat", "r"); // opens file for read
	outfile = fopen("output.dat", "w"); // open file for write

	// read the first student data
	id = read_integer(infile);
	gpa1 = read_double(infile);
	class_standing1 = read_integer(infile);
	age1 = read_double(infile);

	// read the second student data
	id = read_integer(infile);
	gpa2 = read_double(infile);
	class_standing2 = read_integer(infile);
	age2 = read_double(infile);

	// read the third student data
	id = read_integer(infile);
	gpa3 = read_double(infile);
	class_standing3 = read_integer(infile);
	age3 = read_double(infile);

	// read the fourth student data
	id = read_integer(infile);
	gpa4 = read_double(infile);
	class_standing4 = read_integer(infile);
	age4 = read_double(infile);

	// read the fifth student data
	id = read_integer(infile);
	gpa5 = read_double(infile);
	class_standing5 = read_integer(infile);
	age5 = read_double(infile);

	// calculate the sum of the GPAs
	sum_gpa = calculate_sum(gpa1, gpa2, gpa3, gpa4, gpa5);
	//calculate the sum of the class standings
	sum_class_standing = calculate_sum(class_standing1, class_standing2, class_standing3, class_standing4, class_standing5);
	//calculate the sum of the age
	sum_age = calculate_sum(age1, age2, age3, age4, age5);

	// calculate the mean of the GPAs
	mean_gpa = calculate_mean(sum_gpa, number);
	// write the result to the output file
	print_double(outfile, mean_gpa);
	// calculate the mean of the class standings
	mean_class_standing = calculate_mean(sum_class_standing, number);
	// write the result to the output file
	print_double(outfile, mean_class_standing);
	// calculate the mean of the ages
	mean_age = calculate_mean(sum_age, number);
	// write the result to the output file
	print_double(outfile, mean_age);
	fprintf(outfile, "\n");

	// calculate the deviation of each GPA
	deviation1 = calculate_deviation(gpa1, mean_gpa);
	deviation2 = calculate_deviation(gpa2, mean_gpa);
	deviation3 = calculate_deviation(gpa3, mean_gpa);
	deviation4 = calculate_deviation(gpa4, mean_gpa);
	deviation5 = calculate_deviation(gpa5, mean_gpa);
	// calculate the variance of the GPAs
	variance = calculate_variance(deviation1, deviation2, deviation3, deviation4, deviation5, number);
	// calculate the standard deviation of the GPAs
	std_deviation = calculate_standard_deviation(variance);
	// write the result to the output file
	print_double(outfile, std_deviation);

	// determines the min of the GPAs
	min = find_min(gpa1, gpa2, gpa3, gpa4, gpa5);
	// write the result to the output file
	print_double(outfile, min);
	// determines the max of the GPAs
	max = find_max(gpa1, gpa2, gpa3, gpa4, gpa5);
	// write the result to the output file
	print_double(outfile, max);

	// close the file
	fclose(infile);
	fclose(outfile);

	return 0;
}