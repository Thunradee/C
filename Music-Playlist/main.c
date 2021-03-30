/*************************************************************************************************************
* Programmer: Thunradee Tangsupakij                                                                          *
* Class: CptS 122, Spring, 2019; Lab Section 2                                                               *
* Programming Assignment 2: Digital Music Manager & Doubly Linked Lists                                      *
* Date: January 27, 2019                                                                                     *
* Description: This program download a music list from musicPlayList.csv and allow the user edit, play       *
*              and store the updated music list back to the same file.                                       *
*************************************************************************************************************/

#include "PA2.h"

int main(int argc, const char *argv[]) {

	driver();
	testInsert();
	testDelete();
	testShuffle();

	return 0;
}