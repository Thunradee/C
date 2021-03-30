/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 2: Digital Music Manager & Doubly Linked Lists                                      *
* Date: January 27, 2019                                                                                     *
* Description: This program download a music list from musicPlayList.csv and allow the user edit, play       *
*              and store the updated music list back to the same file.                                       *
*************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define INSERT 4
#define DELETE 5
#define EDIT 6
#define SORT 7
#define RATE 8
#define PLAY 9
#define SHUFFLE 10
#define EXIT 11
#define ARTIST 0
#define ALBUM 1
#define SONG 2
#define GENRE 3
#define LENGTH 4
#define MIN 4
#define SEC 5
#define TIMES 6
#define RATING 7

typedef struct duration {
	int minutes;
	int seconds;
}Duration;

typedef struct record {
	char artist[50];
	char album[50];
	char song[50];
	char genre[20];
	Duration length;
	int times;
	int rating;
}Record;

typedef struct node {
	Record data;
	struct node *pNext;
	struct node *pPrev;
}Node;


void driver(void);
void load(Node **pHead, int *record_num, char *fileName);
void displayMenu(void);
int getOption(void);
int checkOption(int option, int min, int max);
int getAndCheckInt(char *prompt, int min, int max);
char *myStrtok(char *str, char *delim);
void cleanData(char *temp[]);
int isDuplicated(Node *pHead, char *song);
void assignData(Node *pNode, char *temp[]);
Node *creatNode(char *temp[]);
int isEmpty(Node *pHead);
int insertAtBack(Node **pHead, char *temp[]);
int insertAtFront(Node **pHead, char *temp[]);
void deleteNode(Node **pHead, Node *target);
int storeRecord(FILE *outfile, Node *pHead);
void displaysMenu(void);
void printList(Node *pHead);
Node *searchArtist(Node *pHead, char *artist);
int displayArtistRecs(Node *pHead, char *artist, Node *resultList[100]);
void displayEditMenu(void);
void elimNewLine(char *str);
int haveComma(char *str);
int haveQuote(char *str);
void putDoubleQuote(char *str);
void delDoubleQuote(char *str);
Node *searchSong(Node *pHead, char *song);
int displaySong(Node *pHead, char *song, Node *resultList[100]);
Node *getTargetBySong(Node *pHead);
void playASong(Node *pTarget, int sec);
void getString(char *prompt, char *des);
void promptRecord(char temp[][50], int promptIndex[], int promptNum);
int isPositive(int num);
int checkRecInput(char temp[][50],int checkIndex[], int checkNum, int valid[]);
void updateCheckIndex(int checkIndex[], int *checkNum, int valid[], int validSize);
void moveStrArrDown(char strArr[][50], int from, int to);
void swapNode(Node **pHead, Node *pNode1, Node *pNode2);
void bubbleSortByArtist(Node **pHead, int record_num);
void bubbleSortByAlbum(Node **pHead, int record_num);
void bubbleSortByRating(Node **pHead, int record_num);
void bubbleSortByTimes(Node **pHead, int record_num);
int genRanNum(int bound);
int checkNumInArr(int *arr, int size, int num);
void playShuffle(Node *pHead, int *arr, int arr_size);