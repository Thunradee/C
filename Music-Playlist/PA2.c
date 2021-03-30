/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 2: Digital Music Manager & Doubly Linked Lists                                      *
* Date: January 27, 2019                                                                                     *
* Description: This program download a music list from musicPlayList.csv and allow the user edit, play       *
*              and store the updated music list back to the same file.                                       *
*************************************************************************************************************/

#include "PA2.h"

// driver
void driver(void)
{
	int option = 0, opValid = 0, record_num = 0;
	Node *pHead = NULL;

	srand((unsigned int)time(NULL));

	// do until the user choose to exit the program
	while (option != EXIT) {
		do {
			displayMenu();
			option = getOption();
			opValid = checkOption(option, LOAD, EXIT);
			system("cls");
		} while (!opValid);

		if (option == LOAD) {
			load(&pHead, &record_num, "musicPlayList.csv");
		}

		else if (option == STORE) {
			FILE *outfile = NULL;
			int success = 0;
			
			//outfile = fopen("output.csv", "w");
			outfile = fopen("musicPlayList.csv", "w");

			success = storeRecord(outfile, pHead);
			if (success) {
				printf("All the records have been written to the file successfully\n");
				system("pause");
				system("cls");
			}
			fclose(outfile);
		}
		else if (option == DISPLAY) {
			char artist[50];
			int dOption = 0, dOpValid = 0, num_found = 0;
			Node *resultList[100];
			do {
				displaysMenu();
				dOption = getOption();
				dOpValid = checkOption(dOption, 1, 2);
				system("cls");
			} while (!dOpValid);

			if (dOption == 1) {
				printList(pHead);
				system("pause");
				system("cls");
			}
			else if (dOption == 2) {
				puts("Enter the artist name: ");
				do {
					fgets(artist, 50, stdin);
				} while (strcmp(artist, "\n") == 0);
				num_found = displayArtistRecs(pHead, artist, resultList);
				system("pause");
				system("cls");
			}
		}
		else if (option == INSERT) {
			char temp[9][50], *pTemp[9];
			int success = 0, i = 0, num = 0, val = 0;
			int checkIndex[3] = { 4, 5, 6 }, checkNum = 3, valid[7] = { 1, 1, 1, 1, 1, 1, 1 };
			int promptIndex[7] = { 0, 1, 2, 3, 4, 5, 6 }, promptNum = 7;

			promptRecord(temp, promptIndex, promptNum);
			system("cls");

			val = checkRecInput(temp, checkIndex, checkNum, valid);
			while (!val) {
				updateCheckIndex(checkIndex, &checkNum, valid, 7);
				promptRecord(temp, checkIndex, checkNum);
				system("cls");
				val = checkRecInput(temp, checkIndex, checkNum, valid);
			}

			// adjust array
			moveStrArrDown(temp, 5, 7);

			//break length into min and sec and put into the array
			for (int i = 0; i < 8; ++i) {
				if (i == LENGTH) {
					pTemp[i] = myStrtok(temp[i], ":");
					while (pTemp[i]) {
						++i;
						pTemp[i] = myStrtok(NULL, ":");
					}
				}
				pTemp[i] = temp[i];
			}

			// insertAtFront
			success = insertAtFront(&pHead, pTemp);
			if (success) {
				// print the message of success
				++record_num;
				puts("The song was put in the list successfully");
				printList(pHead);
				system("pause");
				system("cls");
			}
		}
		else if (option == DELETE) {
			Node *targetNode = NULL;
			int rating = 0, targetVal = 0;
			if (!isEmpty(pHead)) {
				targetNode = getTargetBySong(pHead);
				if (targetNode) {
					deleteNode(&pHead, targetNode);
					--record_num;
					puts("The song was deleted from the list successfully");
					system("pause");
					system("cls");
				}
			}
			else {
				puts("The list is empty");
			}
		}
		else if (option == EDIT) {
			char artist[50] = "", temp[50] = "", *comma = NULL;
			int num_found = 0, target = 0, targetVal = 0, editOp = 0, opVal = 0, tempInt = 0;
			Node *targetList[100], *targetNode = NULL;

			// prompt user for the artist
			puts("Enter the artist name: ");
			do {
				fgets(artist, 50, stdin);
			} while (strcmp(artist, "\n") == 0);

			num_found = displayArtistRecs(pHead, artist, targetList);

			// if found the artist
			if (num_found) {
				// if found only one record
				if (num_found == 1) {
					targetNode = targetList[num_found - 1];
				}
				// if founded records of the artist are more than one, prompt for the number
				else if (num_found > 1) {
					do {
						puts("Enter the number of the record: ");
						scanf("%d", &target);
						targetVal = checkOption(target, 1, num_found);
					} while (!targetVal);
					system("cls");

					targetNode = targetList[target - 1];
				}
				while (editOp != 8) {
					do {
						displayEditMenu();
						editOp = getOption();
						opVal = checkOption(editOp, 1, 8);
						system("cls");
					} while (!opVal);

					// artist
					if (editOp == 1) {
						// prompt a new artist
						printf("The current artist: %s\n", targetNode->data.artist);
						puts("Enter a new artist: ");
						do {
							fgets(artist, 50, stdin);
						} while (strcmp(artist, "\n") == 0);
						elimNewLine(artist);
						comma = strpbrk(artist, ",");
						if (comma && !haveQuote(artist)) {
							putDoubleQuote(artist);
						}
						strcpy(targetNode->data.artist, artist);
					}
					// album
					else if (editOp == 2) {
						printf("The current album title: %s\n", targetNode->data.album);
						puts("Enter a new album title: ");
						do {
							fgets(temp, 50, stdin);
						} while (strcmp(temp, "\n") == 0);
						elimNewLine(temp);
						comma = strpbrk(temp, ",");
						if (comma && !haveQuote(temp)) {
							putDoubleQuote(temp);
						}
						strcpy(targetNode->data.album, temp);
					}
					// song
					else if (editOp == 3) {
						printf("The current song title: %s\n", targetNode->data.song);
						puts("Enter a new song title: ");
						do {
							fgets(temp, 50, stdin);
						} while (strcmp(temp, "\n") == 0);
						elimNewLine(temp);
						comma = strpbrk(temp, ",");
						if (comma && !haveQuote(temp)) {
							putDoubleQuote(temp);
						}
						strcpy(targetNode->data.song, temp);
					}
					// genre
					else if (editOp == 4) {
						printf("The current genre: %s\n", targetNode->data.genre);
						puts("Enter a new genre: ");
						do {
							fgets(temp, 50, stdin);
						} while (strcmp(temp, "\n") == 0);
						elimNewLine(temp);
						comma = strpbrk(temp, ",");
						if (comma && !haveQuote(temp)) {
							putDoubleQuote(temp);
						}
						strcpy(targetNode->data.genre, temp);
					}
					// length
					else if (editOp == 5) {
						puts("Enter a new minute length: ");
						scanf("%d", &tempInt);
						targetNode->data.length.minutes = tempInt;
						puts("Enter a new second lenght: ");
						scanf("%d", &tempInt);
						targetNode->data.length.seconds = tempInt;
					}
					// times
					else if (editOp == 6) {
						puts("Enter a new number times played: ");
						scanf("%d", &tempInt);
						targetNode->data.times = tempInt;
					}
					// rating
					else if (editOp == 7) {
						puts("Enter a new rating[1-5]: ");
						scanf("%d", &tempInt);
						targetNode->data.rating = tempInt;
					}
					system("cls");
				}
			}
			else {
				puts("No records are founded.");
				system("pause");
				system("cls");
			}


		}
		else if (option == SORT) {
			int sort_op = 0, sort_op_val = 0;
			do {
				puts("SORT MENU:");
				puts("1.\tSort by artist(A - Z)");
				puts("2.\tSort by album title(A - Z)");
				puts("3.\tSort by rating(1 - 5)");
				puts("4.\tSort by times played(largest - smallest)");
				puts("Enter the option number: ");
				sort_op = getOption();
				sort_op_val = checkOption(sort_op, 1, 4);
				system("cls");
			} while (!sort_op_val);
			if (!isEmpty(pHead)) {
				if (sort_op == 1) {
					puts("SORT BY ARTIST(A-Z)");
					bubbleSortByArtist(&pHead, record_num);
				}
				else if (sort_op == 2) {
					puts("SORT BY ALBUM TITLE(A-Z)");
					bubbleSortByAlbum(&pHead, record_num);
				}
				else if (sort_op == 3) {
					puts("SORT BY RATING(1-5)");
					bubbleSortByRating(&pHead, record_num);
				}
				else {
					puts("SORT BY TIMES PLAYED(L-S)");
					bubbleSortByTimes(&pHead, record_num);
				}
				printList(pHead);
			}
			else {
				puts("The list is empty");
			}

		}
		else if (option == RATE) {
			Node *targetNode = NULL;
			int rating = 0, targetVal = 0;
			targetNode = getTargetBySong(pHead);
			if (targetNode) {
				do {
					puts("Enter a new rating[1-5]: ");
					scanf("%d", &rating);
					targetVal = checkOption(rating, 1, 5);
				} while (!targetVal);
				targetNode->data.rating = rating;
			}
		}
		else if (option == PLAY) {
			Node *pCur = NULL;
			int play_sec = 5;
			pCur = getTargetBySong(pHead);
			while (pCur) {
				playASong(pCur, play_sec);
				system("cls");
				pCur = pCur->pNext;
			}
		}
		else if (option == SHUFFLE) {
			int ranNum = 0, shuf_arr[100000], arr_i = 0, num_dup = 0;

			// generate a shuffle order
			while (arr_i < record_num) {
				ranNum = genRanNum(record_num);
				num_dup = checkNumInArr(shuf_arr, arr_i, ranNum);
				if (!num_dup) {
					shuf_arr[arr_i] = ranNum;
					++arr_i;
				}
			}

			// play the shuffle
			playShuffle(pHead, shuf_arr, arr_i);
		}
		// exit
		else {
			FILE *outfile = NULL;
			int success = 0;
			
			//outfile = fopen("output.csv", "w");
			outfile = fopen("musicPlayList.csv", "w");

			success = storeRecord(outfile, pHead);
			if (success) {
				printf("All the records have been written to the file successfully\n");
				system("pause");
				system("cls");
			}
			fclose(outfile);
		}
	}
}

// load record from the given file
void load(Node **pHead, int *record_num, char *fileName)
{
	FILE *infile = NULL;
	char line[100] = "", *temp[9], *delim = ",";
	int i = 0, success = 0, track = 1, dup = 0;
	// open the input file in reading mode
	infile = fopen(fileName, "r");

	// if file was opened succesfully
	if (infile) {
		while (!feof(infile) && fgets(line, 100, infile)) {
			i = 0;
			temp[i] = myStrtok(line, delim);
			while (temp[i]) {
				++i;
				temp[i] = myStrtok(NULL, delim);
			}
			cleanData(temp);
			if (isEmpty(*pHead)) {
				success = insertAtBack(pHead, temp);
			}
			else if(!isDuplicated(*pHead, temp[SONG])){
				success = insertAtBack(pHead, temp);
			}

			if (!success) {
				printf("Track %d failed loading\n", track);
			}
			else {
				*record_num += 1;
			}
			++track;
		}
	}
	else {
		printf("The file %s failed to open\n", fileName);
	}

	fclose(infile);
}

void displayMenu(void)
{
	printf("MAIN MENU:\n");
	printf("(1)\tload\n");
	printf("(2)\tstore\n");
	printf("(3)\tdisplay\n");
	printf("(4)\tinsert\n");
	printf("(5)\tdelete\n");
	printf("(6)\tedit\n");
	printf("(7)\tsort\n");
	printf("(8)\trate\n");
	printf("(9)\tplay\n");
	printf("(10)\tshuffle\n");
	printf("(11)\texit\n");
	printf("Enter the option[1-11]: ");
}

int getOption(void)
{
	int option = 0;

	scanf("%d", &option);

	return option;
}

int checkOption(int option, int min, int max)
{
	if (option >= min && option <= max)
		return 1;

	return 0;
}

int getAndCheckInt(char *prompt, int min, int max)
{
	int num = 0, val = 0;
	while (!val) {
		printf(prompt);
		num = getOption();
		val = checkOption(num, min, max);
	}
	
	return num;
}

char *myStrtok(char *str, char *delim)
{
	static char *start = NULL;
	char *token = NULL;

	if (str)
		start = str;
	if (!start)
		return NULL;

	token = start;
	start = strpbrk(start, delim);

	if (start) {
		*start = '\0';
		start++;
	}

	return token;
}

void cleanData(char *temp[])
{
	char *delim = ":";
	int move = 0, j = 0;
	// if the artist has a comma, it will be put in ""
	if (temp[0][0] == '\"') {
		move = 1;
		while (temp[0][j]) {
			++j;
		}
		temp[0][j] = ',';
		
		for (int i = 1; i <= 4; ++i) {
			temp[i] = temp[i + 1];
		}
	}

	// duration
	if (temp[4]) {
		if (!move) {
			for (int i = 8; i >= 6; --i) {
				temp[i] = temp[i - 1];
			}
		}
		temp[4] = myStrtok(temp[4], delim);
		temp[5] = myStrtok(NULL, delim);
	}
}

int isDuplicated(Node *pHead, char *song)
{
	int dup = 0;
	Node *pCur = pHead;
	while (pCur) {
		if (strcmp(pCur->data.song, song) == 0) {
			dup = 1;
			return dup;
		}
		pCur = pCur->pNext;
	}

	return dup;
}

void assignData(Node *pNode, char *temp[])
{
	int i = 0;
	strcpy(pNode->data.artist, temp[i++]);
	strcpy(pNode->data.album, temp[i++]);
	strcpy(pNode->data.song, temp[i++]);
	strcpy(pNode->data.genre, temp[i++]);
	pNode->data.length.minutes = atoi(temp[i++]);
	pNode->data.length.seconds = atoi(temp[i++]);
	pNode->data.times = atoi(temp[i++]);
	pNode->data.rating = atoi(temp[i++]);
}

Node *creatNode(char *temp[])
{
	Node *pMem = NULL;
	int i = 0;
	pMem = (Node *)malloc(sizeof(Node));

	if (pMem) {
		assignData(pMem, temp);
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

int isEmpty(Node *pHead)
{
	return (pHead == NULL);
}

int insertAtBack(Node **pHead, char *temp[])
{
	Node *pMem = NULL, *pCur = *pHead;
	int success = 0;
	pMem = creatNode(temp);
	if (pMem) {
		success = 1;
		if (!(*pHead)) {
			*pHead = pMem;
		}
		else {
			while (pCur->pNext) {
				pCur = pCur->pNext;
			}
			pCur->pNext = pMem;
			pMem->pPrev = pCur;
		}
		
		/*pMem->pNext = *pHead;
		if (!isEmpty(*pHead)) {
			(*pHead)->pPrev = pMem;
		}
		*pHead = pMem;*/
	}

	return success;
}

int insertAtFront(Node **pHead, char *temp[])
{
	Node *pMem = NULL, *pCur = *pHead;
	int success = 0;
	pMem = creatNode(temp);
	if (pMem) {
		success = 1;
		
		pMem->pNext = *pHead;
		if (!isEmpty(*pHead)) {
		(*pHead)->pPrev = pMem;
		}
		*pHead = pMem;
	}

	return success;
}

// precondition: the list is not empty
void deleteNode(Node **pHead, Node *target)
{
	Node *pCur = target, *pPrev = target->pPrev;
	if (target == *pHead) {
		*pHead = pCur->pNext;
		if(*pHead)
			(*pHead)->pPrev = NULL;
	}
	else {
		if (pCur->pNext) {
			pPrev->pNext = pCur->pNext;
			pCur->pNext->pPrev = pPrev;
		}
		else {
			pPrev->pNext = NULL;
		}
	}
	free(pCur);
}

int storeRecord(FILE *outfile, Node *pHead)
{
	Node *pCur = pHead;
	int success = 0;
	while (pCur) {
		fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.album, pCur->data.song, pCur->data.genre, pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.times, pCur->data.rating);
		pCur = pCur->pNext;
	}
	if (!pCur) {
		success = 1;
	}

	return success;
}

void displaysMenu(void)
{
	printf("1.\tPrint all records.\n");
	printf("2.\tPrint all records that match an artist.\n");
	printf("Enter the option number: ");
}

void printList(Node *pHead)
{
	Node *pCur = pHead;
	int i = 1;
	printf("%-5s%-20s%-25s%-20s%-10s%-10s%15s%10s\n", "NO", "ARTIST", "ALBUM", "SONG", "GENRE", "LENGTH", "TIMES PLAYED", "RATING");
	while (pCur) {
		printf("%-5d%-20s%-25s%-20s%-10s%02d:%-02d%15d%10d\n", i, pCur->data.artist, pCur->data.album, pCur->data.song, pCur->data.genre, pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.times, pCur->data.rating);
		pCur = pCur->pNext;
		++i;
	}
}

Node *searchArtist(Node *pHead, char *artist)
{
	Node *pCur = pHead;
	char temp[50] = "", tempC = '\0';
	int length = 0;

	// take the artist to lower case
	/*while (artist[i] != '\n') {
		tempC = tolower(artist[i]);
		artist[i] = tempC;
		++i;
	}
	artist[i] = '\0';*/
	strtok(artist, "\n");
	length = strlen(artist);
	for (int i = 0; i < length; ++i) {
		tempC = tolower(artist[i]);
		artist[i] = tempC;
	}

	while (pCur) {
		int j = 0;
		// copy the artist to the temp variable
		strcpy(temp, pCur->data.artist);
		// take the artist to lower case
		while (temp[j]) {
			tempC = tolower(temp[j]);
			temp[j++] = tempC;
		}
		// if found the target, return the node
		if (strstr(temp, artist)) {
			return pCur;
		}
		pCur = pCur->pNext;
	}
	return pCur;
}

int displayArtistRecs(Node *pHead, char *artist, Node *resultList[100])
{
	Node *pTarget = NULL;
	int record_num = 0;

	// print the title
	printf("%-5s%-20s%-25s%-20s%-10s%-10s%15s%10s\n", "NO", "ARTIST", "ALBUM", "SONG", "GENRE", "LENGTH", "TIMES PLAYED", "RATING");
	
	if (pTarget = searchArtist(pHead, artist)) {
		while (pTarget) {
			resultList[record_num++] = pTarget;
			printf("%-5d%-20s%-25s%-20s%-10s%02d:%-02d%15d%10d\n",record_num, pTarget->data.artist, pTarget->data.album, pTarget->data.song, pTarget->data.genre, pTarget->data.length.minutes, pTarget->data.length.seconds, pTarget->data.times, pTarget->data.rating);
			pTarget = pTarget->pNext;
			pTarget = searchArtist(pTarget, artist);
		}
	}

	return record_num;
}

void displayEditMenu(void)
{
	puts("What would you like to edit?");
	puts("1.\tArtist");
	puts("2.\tAlbum title");
	puts("3.\tSong title");
	puts("4.\tGenre");
	puts("5.\tSong length");
	puts("6.\tNumber times played");
	puts("7.\tRating");
	puts("8.\tExit");
	puts("Enter the option number[1-8]: ");
}

// replace '\n' with '\0'
void elimNewLine(char *str)
{
	int i = 0;
	while (str[i]) {
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

int haveComma(char *str)
{
	char *token;
	token = strpbrk(str, ",");
	if (token)
		return 1;
	return 0;
}

int haveQuote(char *str)
{
	int len = 0;
	len = strlen(str);
	return ((str[0] == '\"') && (str[len - 1] == '\"'));
}

void putDoubleQuote(char *str)
{
	int i = 0;
	while (str[i]) {
		++i;
	}

	str[i + 2] = str[i];
	str[i + 1] = '\"';

	for (; i > 0; i--) {
		str[i] = str[i - 1];
	}

	str[i] = '\"';
}

void delDoubleQuote(char *str)
{
	int len = 0, i = 0;
	len = strlen(str);
	str[len - 1] = '\0';
	while (str[i]) {
		str[i] = str[i + 1];
		++i;
	}
}

Node *searchSong(Node *pHead, char *song)
{
	Node *pCur = pHead;
	char temp[50] = "", tempC = '\0';
	int len = 0;

	strtok(song, "\n");

	// take the artist to lower case
	len = strlen(song);
	for (int i = 0; i < len; ++i) {
		tempC = tolower(song[i]);
		song[i] = tempC;
	}

	while (pCur) {
		int j = 0;
		// copy the artist to the temp variable
		strcpy(temp, pCur->data.song);
		// take the artist to lower case
		while (temp[j]) {
			tempC = tolower(temp[j]);
			temp[j++] = tempC;
		}
		// if found the target, return the node
		if (strstr(temp, song)) {
			return pCur;
		}
		pCur = pCur->pNext;
	}
	return pCur;
}

int displaySong(Node *pHead, char *song, Node *resultList[100])
{
	Node *pTarget = NULL;
	int record_num = 0;

	// print the title
	printf("%-5s%-20s%-25s%-20s%-10s%-10s%15s%10s\n", "NO", "ARTIST", "ALBUM", "SONG", "GENRE", "LENGTH", "TIMES PLAYED", "RATING");

	if (pTarget = searchSong(pHead, song)) {
		while (pTarget) {
			resultList[record_num++] = pTarget;
			printf("%-5d%-20s%-25s%-20s%-10s%02d:%-02d%15d%10d\n", record_num, pTarget->data.artist, pTarget->data.album, pTarget->data.song, pTarget->data.genre, pTarget->data.length.minutes, pTarget->data.length.seconds, pTarget->data.times, pTarget->data.rating);
			pTarget = pTarget->pNext;
			pTarget = searchArtist(pTarget, song);
		}
	}

	return record_num;
}

Node *getTargetBySong(Node *pHead)
{
	char song[50] = "";
	int rating = 0, record_num = 0, target = 0, targetVal = 0;
	Node *resultList[100], *targetNode = NULL;

	printf("Enter the song: ");
	do {
		fgets(song, 50, stdin);
	} while (strcmp(song, "\n") == 0);

	record_num = displaySong(pHead, song, resultList);
	if (record_num) {
		if (record_num == 1) {
			targetNode = resultList[0];
		}
		// found more than one song
		else {
			do {
				puts("Enter the number of the record: ");
				scanf("%d", &target);
				targetVal = checkOption(target, 1, record_num);
			} while (!targetVal);
			system("cls");

			targetNode = resultList[target - 1];
		}
	}
	else {
		puts("No records are founded.");
		system("pause");
		system("cls");
	}
	
	return targetNode;
}

void playASong(Node *pTarget, int sec)
{
	puts(pTarget->data.song);
	Sleep(sec * 1000);
}

void getString(char *prompt, char *des)
{
	puts(prompt);
	do {
		fgets(des, 50, stdin);
	} while (strcmp(des, "\n") == 0);
	strtok(des, "\n");
}

void promptRecord(char temp[][50], int promptIndex[], int promptNum)
{
	int index = 0;
	char prompts[7][50] = {"Enter the artist: ", 
		"Enter the album title: ", 
		"Enter the song title: ", 
		"Enter the genre: ", 
		"Enter the song length[min:sec]: ", 
		"Enter the number of times played: ", 
		"Enter the rating[1-5]: " };
		
	for (int i = 0; i < promptNum; ++i) {
		index = promptIndex[i];
		getString(prompts[index], temp[index]);
		if (haveComma(temp[index])) {
			putDoubleQuote(temp[index]);
		}
	}
}

int isPositive(int num)
{
	return (num >= 0);
}

int checkRecInput(char temp[][50], int checkIndex[], int checkNum, int valid[])
{
	int val = 1, min = 0, sec = 0, times = 0, rating = 0, index = 0;
	char *temp_char, cop_len[50];

	for (int i = 0; i < checkNum; ++i) {
		index = checkIndex[i];
		// length
		if (index == 4) {
			strcpy(cop_len, temp[index]);
			temp_char = myStrtok(cop_len, ":");
			min = atoi(temp_char);
			temp_char = myStrtok(NULL, ":");
			sec = atoi(temp_char);

			if (!isPositive(min) || !checkOption(sec, 0, 60)) {
				printf("The length %s is invalid\n", temp[index]);
				valid[index] = 0;
				val *= 0;
			}
			else {
				valid[index] = 1;
			}
		}

		// times played
		if (index == 5) {
			times = atoi(temp[index]);
			if (!isPositive(times)) {
				printf("The times played %s is invalid\n", temp[index]);
				valid[index] = 0;
				val *= 0;
			}
			else {
				valid[index] = 1;
			}
		}

		// rating
		if (index == 6) {
			rating = atoi(temp[index]);
			if (!checkOption(rating, 1, 5)) {
				printf("The rating %s is invalid\n", temp[index]);
				valid[index] = 0;
				val *= 0;
			}
			else {
				valid[index] = 1;
			}
		}
	}

	return val;
}

void updateCheckIndex(int checkIndex[], int *checkNum, int valid[], int validSize)
{
	*checkNum = 0;
	for (int i = 4; i < validSize; ++i) {
		if (!valid[i]) {
			checkIndex[*checkNum] = i;
			*checkNum += 1;
		}
	}
}

void moveStrArrDown(char strArr[][50], int from, int to)
{
	for (int i = to; i > from; --i) {
		strcpy(strArr[i], strArr[i - 1]);
	}
}

void swapNode(Node **pHead, Node *pNode1, Node *pNode2)
{
	Node *pPrev = pNode1->pPrev, *pNext = pNode2->pNext;

	if (pPrev) {
		pPrev->pNext = pNode2;
	}
	else {
		*pHead = pNode2;
	}
	pNode1->pPrev = pNode2;
	pNode1->pNext = pNext;
	pNode2->pPrev = pPrev;
	pNode2->pNext = pNode1;
	if (pNext) {
		pNext->pPrev = pNode1;
	}



	/*if (pNode1 == *pHead) {
		pNode1->pPrev = pNode2;
		pNode1->pNext = pNext;
		pNode2->pPrev = pPrev;
		pNode2->pNext = pNode1;
		pNext->pPrev = pNode1;
		*pHead = pNode2;
	}
	else {
		if (pNode2->pNext) {
			pPrev->pNext = pNode2;
			pNode1->pPrev = pNode2;
			pNode1->pNext = pNext;
			pNode2->pPrev = pPrev;
			pNode2->pNext = pNode1;
			pNext->pPrev = pNode1;
		}
		else {
			pPrev->pNext = pNode2;
			pNode1->pPrev = pNode2;
			pNode1->pNext = pNext;
			pNode2->pPrev = pPrev;
			pNode2->pNext = pNode1;
		}
	}*/
}

void bubbleSortByArtist(Node **pHead, int record_num)
{
	Node *pNode1, *pNode2;
	char data1[50] = "", data2[50] = "";
	for (int i = 0; i < record_num; ++i) {
		pNode1 = *pHead;
		pNode2 = (*pHead)->pNext;
		for (int j = 0; j < record_num - i - 1; ++j) {
			strcpy(data1, pNode1->data.artist);
			strcpy(data2, pNode2->data.artist);
			if (haveQuote(pNode1->data.artist)) {
				delDoubleQuote(data1);
			}
			if (haveQuote(pNode2->data.artist)) {
				delDoubleQuote(data2);
			}
			if (strcmp(data1, data2) > 0) {
				swapNode(pHead, pNode1, pNode2);
				pNode2 = pNode1->pNext;
			}
			else {
				pNode1 = pNode2;
				pNode2 = pNode2->pNext;
			}
		}
	}
}

void bubbleSortByAlbum(Node **pHead, int record_num)
{
	Node *pNode1, *pNode2;
	char data1[50] = "", data2[50] = "";
	for (int i = 0; i < record_num; ++i) {
		pNode1 = *pHead;
		pNode2 = (*pHead)->pNext;
		for (int j = 0; j < record_num - i - 1; ++j) {
			strcpy(data1, pNode1->data.album);
			strcpy(data2, pNode2->data.album);
			if (haveQuote(pNode1->data.album)) {
				delDoubleQuote(data1);
			}
			if (haveQuote(pNode2->data.album)) {
				delDoubleQuote(data2);
			}
			if (strcmp(data1, data2) > 0) {
				swapNode(pHead, pNode1, pNode2);
				pNode2 = pNode1->pNext;
			}
			else {
				pNode1 = pNode2;
				pNode2 = pNode2->pNext;
			}
		}
	}
}

void bubbleSortByRating(Node **pHead, int record_num)
{
	Node *pNode1, *pNode2;
	
	for (int i = 0; i < record_num; ++i) {
		pNode1 = *pHead;
		pNode2 = (*pHead)->pNext;
		for (int j = 0; j < record_num - i - 1; ++j) {
			
			if (pNode1->data.rating > pNode2->data.rating) {
				swapNode(pHead, pNode1, pNode2);
				pNode2 = pNode1->pNext;
			}
			else {
				pNode1 = pNode2;
				pNode2 = pNode2->pNext;
			}
		}
	}
}

void bubbleSortByTimes(Node **pHead, int record_num)
{
	Node *pNode1, *pNode2;

	for (int i = 0; i < record_num; ++i) {
		pNode1 = *pHead;
		pNode2 = (*pHead)->pNext;
		for (int j = 0; j < record_num - i - 1; ++j) {

			if (pNode1->data.times < pNode2->data.times) {
				swapNode(pHead, pNode1, pNode2);
				pNode2 = pNode1->pNext;
			}
			else {
				pNode1 = pNode2;
				pNode2 = pNode2->pNext;
			}
		}
	}
}

// generate number from 0 to bound-1
int genRanNum(int bound)
{
	int ranNum = 0;
	ranNum = rand() % bound;
	return ranNum;
}

int checkNumInArr(int *arr, int size, int num)
{
	int found = 0;
	for (int i = 0; i < size; ++i) {
		if (arr[i] == num) {
			found = 1;
			return found;
		}
	}
	return found;
}

void playShuffle(Node *pHead, int *arr, int arr_size)
{
	Node *pCur = pHead;
	int move = 0, play_sec = 5, cur_index = 0; 

	for (int i = 0; i < arr_size; ++i) {
		move = cur_index - arr[i];
		cur_index = arr[i];
		// move to the right
		if (move < 0) {
			move *= -1;
			for (int j = 0; j < move; ++j) {
				pCur = pCur->pNext;
			}
		}
		// move to the left
		else {
			for (int j = 0; j < move; ++j) {
				pCur = pCur->pPrev;
			}
		}
		playASong(pCur, play_sec);
		system("cls");
	}
}