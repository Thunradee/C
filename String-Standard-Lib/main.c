/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Bonus Assignment: String Processor
Description: This program implements string functions in standard library <string.h>
*/

#include "StrProc.h"

int main(void) {

	int n = 20;
	char str1[50], *str2 = "Thunradee", str3[30], des1[30], des2[30], des3[30] = "HARIBO", des4[30] = "Gift";
	FILE *infile = NULL, *outfile = NULL;
	infile = fopen("data.txt", "r");
	outfile = fopen("output.txt", "w");
	printf("my_fgets(str, n = 20, infile = fopen(\"data.txt\", \"r\"))\n");
	printf("%s\n", my_fgets(str1, n, infile));
	printf("%d\n", my_fputs(str2, outfile));
	fprintf(outfile, "\n");
	printf("%c\n", my_fgetc(infile));
	printf("%d\n", my_fputc(65, outfile));
	printf("%s\n", my_gets(str3));
	printf("%d\n", my_puts("Washington State University"));
	printf("%d\n", my_getchar());
	printf("\n%d\n", my_putchar(65));
	printf("%s\n", my_strcpy(des1, "Goldbears"));
	printf("%s\n", my_strncpy(des2, "Blah Blah", 10));
	printf("%s\n", my_strcat(des3, " Goldbears"));
	printf("%s\n", my_strncat(des4, " Thunradee", 5));
	printf("%d\n", my_strcmp("gift", "gift"));
	printf("%d\n", my_strncmp("gift", "gifted", 4));
	printf("%d\n", my_strlen("Gift"));

	return 0;
}