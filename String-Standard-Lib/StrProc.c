/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Bonus Assignment: String Processor
Description: This program implements string functions in standard library <string.h>
*/

#include "StrProc.h"

/*
 * Reads at most one less than the number of characters specified by n, into the array pointed to by s, 
 * from the input pointed to by stream.  No more characters are read after a newline is encountered or end of file is encountered.
 * The newline if encountered is stored by the array pointed to by s. A null character is appended to the end of string s. 
 * If the function is successful in reading characters into s, then s is returned; otherwise a NULL pointer is returned.
*/
char *my_fgets(char *s, int n, FILE *stream)
{
	if (stream != NULL) {
		int i = 0;
		char temp = '\0';
		while (!feof(stream) && temp != '\n' && i < n - 1) {
			fscanf(stream, "%c", &temp);
			*(s + i) = temp;
			++i;
		}
		*(s + i) = '\0';
		return s;
	}
	else {
		return NULL;
	}
}

/*
 * Writes s to the output specified by stream. If the function is successful, 
 * then it returns the number of characters written to the output; otherwise it returns MY_EOF 
 * #define MY_EOF as -1.
 */
int my_fputs(const char *s, FILE *stream)
{
	if (stream != NULL) {
		int i = 0;
		while (*(s + i) != '\0') {
			fprintf(stream, "%c", *(s + i));
			++i;
		}
		return i;
	}
	else {
		return MY_EOF;
	}
}

/*
 * Reads the next character from the input pointed to by stream. 
 * If the input is at the end of file or a processing error occurs return MY_EOF; 
 * otherwise return the integer representation of the character read.
*/
int my_fgetc(FILE *stream)
{
	if (stream != NULL && !feof(stream)) {
		char temp;
		fscanf(stream, "%c", &temp);
		return (int)temp;
	}
	else {
		return MY_EOF;
	}
}

/*
 * Writes the character c (converted to a character) to the output specified by stream. 
 * If the write is successful the ascii value of the character is returned; otherwise MY_EOF is returned.
*/
int my_fputc(int c, FILE *stream)
{
	if (stream != NULL) {
		fprintf(stream, "%c", c);
		return c;
	}
	else {
		return MY_EOF;
	}
}

/*
 * Reads characters from stdin into the array pointed to by s until a newline is encountered. 
 * The newline character is NOT kept at the end of the array pointed to by s. 
 * A null character is written to the end of string s. The function returns s.
*/
char *my_gets(char *s)
{
	char temp = '\0';
	int i = 0;
	while (temp != '\n') {
		scanf("%c", &temp);
		*(s + i) = temp;
		++i;
	}
	*(s + i - 1) = '\0';
	return s;
}

/*
* Writes the string pointed to by s to stdout. The function appends a newline to the output. 
* The function returns the number of characters written to the output.
*/
int my_puts(const char *s)
{
	int i = 0;
	while (*(s + i) != '\0') {
		printf("%c", *(s + i));
		++i;
	}
	printf("\n");
	return i;
}

/*
* Returns the ascii value of the next character read from stdin.
*/
int my_getchar(void)
{
	char temp;
	scanf("%c", &temp);
	return (int)temp;
}

/*
 * The function writes character c to stdout. The character c is returned.
*/
int my_putchar(int c)
{
	printf("%c", c);
	return c;
}

/*
 * Copies all characters in the array pointed to by source into the array pointed to by destination. 
 * The null character is also copied. The function returns destination.
*/
char *my_strcpy(char *destination, const char *source)
{
	int i = 0;
	
	while (*(source + i) != '\0') {
		*(destination + i) = *(source + i);
		++i;
	}
	*(destination + i) = '\0';

	return destination;
}

/*
* Copies no more than n characters from the string pointed to by source into the array pointed to by destination. 
* The function does not copy any characters past a null character. If the string pointed to by source is less than n characters, 
* null characters are appended to the end of the array pointed to by destination until n characters have been written.
*/
char *my_strncpy(char *destination, const char *source, int n)
{
	int i = 0;

	while (*(source + i) != '\0' && i < n) {
		*(destination + i) = *(source + i);
		++i;
	}
	*(destination + i) = '\0';
	while (i < n) {
		*(destination + i) = '\0';
		++i;
	}

	return destination;
}

/*
 * This function appends a copy of the string pointed to by source (including the null character) 
 * to the end of the string pointed to by destination. The append overwrites the null character at the end of destination. 
 * The string pointed to by destination is returned.
*/
char *my_strcat(char *destination, const char *source)
{
	int i = 0, j = 0;
	while (*(destination + i) != '\0') {
		++i;
	}
	while (source[j] != '\0') {
		*(destination + i) = *(source + j);
		++i;
		++j;
	}
	*(destination + i) = '\0';
	return destination;
}

/*
 * This function appends no more than n characters from the string pointed to by source to the end of the array pointed to by destination. 
 * The null character is appended to the end of the result. The destination pointer is returned.
*/
char *my_strncat(char *destination, const char *source, int n)
{
	int i = 0, j = 0;
	while (*(destination + i) != '\0') {
		++i;
	}
	while (*(source + j) != '\0' && j < n) {
		*(destination + i) = *(source + j);
		++i;
		++j;
	}
	*(destination + i) = '\0';
	return destination;
}

/*
This function compares the string pointed to by s1 to the string pointed to by s2. 
If the string pointed to by s1 comes before the string pointed to by s2 in dictionary ordering, 
then -1 is returned. If the string pointed to by s1 is the same as the string pointed to by s2, 
then 0 is returned (the compare function is case sensitive). Otherwise 1 is returned.
*/
int my_strcmp(const char *s1, const char *s2)
{
	int i = 0;
	while (*(s1 + i) == *(s2 + i)) {
		if (*(s1 + i) == '\0') {
			return 0;
		}
		++i;
	}
	if (*(s1 + i) < *(s2 + i))
		return -1;
	else
		return 1;
}

/*
This function compares no more than n characters (characters following a null character are not compared) 
from the string pointed to by s1 to the string pointed to by s2. If the string pointed to by s1 comes before 
the string pointed to by s2 in dictionary ordering, then -1 is returned. If the string pointed to by s1 is the same as 
the string pointed to by s2, then 0 is returned (the compare function is case sensitive). Otherwise 1 is returned.
*/
int my_strncmp(const char *s1, const char *s2, int n)
{
	int i = 0;
	while (*(s1 + i) == *(s2 + i)) {
		if (i == (n - 1)) {
			return 0;
		}
		++i;
	}
	if (*(s1 + i) < *(s2 + i))
		return -1;
	else
		return 1;
}

/*
This function returns the length of the string pointed to by s. The computation of length does NOT include the null character.
*/
int my_strlen(const char *s)
{
	int i = 0;
	while (*(s + i) != '\0') {
		++i;
	}

	return i;
}