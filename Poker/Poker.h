/*
Programmer: Thunradee Tangsupakij and Deitel & Deitel - C How to Program
Class: CptS 121
Programming Assignment 7: Poker (5-Card Draw)
Description: This program allows the user to play 5-Card Draw Poker against computer player
*/

#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define CARDS_NUM 5
#define REPLACED_CARDS_NUM 3
#define NO_PAIR 0
#define ONE_PAIR 1
#define TWO_PAIRS 2
#define THREE_OF_A_KIND 3
#define STRAIGHT 4
#define FLUSH 5
#define FULL_HOUSE 6
#define FOUR_OF_A_KIND 7
#define STRAIGHT_FLUSH 8
#define ROYAL_FLUSH 9
#define PLAYER_WINS 1
#define DEALER_WINS -1
#define TIE 0

typedef struct card
{
	int face_index;
	int suit_index;
} Card;

void print_welcome(void);
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], int *deck_index, const char *wFace[], const char *wSuit[], Card cards[], int cards_num);
void display_cards(const char *wFace[], const char *wSuit[], Card cards[], char *title);
void sort_cards(Card cards[]);
int is_one_pair(Card cards[]);
int is_two_pairs(Card cards[]);
int is_three_of_a_kind(Card cards[]);
int is_straight(Card cards[]);
int is_flush(Card cards[]);
int is_full_house(Card cards[]);
int is_four_of_a_kind(Card cards[]);
int is_straight_flush(Card cards[]);
int is_royal_flush(Card cards[]);
int evaluate_hand(Card cards[]);
int determine_the_better_hand(Card player_cards[], Card dealer_cards[], int *player_hand, int *dealer_hand);
void sort_int(int arr[], int arr_num);
void prompt_cards_replacement(int replaced_cards[], int *replaced_cards_num);
void replace_cards(const int wDeck[][13], int *deck_index, const char *wFace[], const char *wSuit[], Card cards[], int replaced_cards_num, int replaced_cards[]);
void determine_card_replacement(int contain, int replaced_cards[], int *replaced_cards_num);
void print_hand_contain(int hand_contain, char *title);
void print_winner(int winner);

#endif