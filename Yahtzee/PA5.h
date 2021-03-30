/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Programming Assignment 5: The Game of Yahtzee
Description: This program allows the user to play the game of Yathzee
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIE_SIZE 5
#define SCORE_CARD_SIZE 19
#define COMBINATION_SCORE_CARD_SIZE 14

#define UPPER_SIZE 6
#define SCORE_TO_GET_BONUS 63
#define BONUS 35
#define TOTAL_INDEX 14
#define BONUS_INDEX 15
#define LOWER_TOTAL_INDEX 16
#define UPPER_TOTAL_INDEX 17
#define COMBINE_TOTAL_INDEX 18

void run_yahtzee(void);
void print_menu(void);
void get_option(int *option);
void print_game_rules();
void roll_die(int die[]);
void print_die_values(int die[]);
char get_use_combinations(void);
void print_combinations(void);
int get_combination(void);
int update_score_card(int combination, int score_card[], int score_card_tracker[], int die[]);
int cal_sum_of_aces(int die[]);
int cal_sum_of_twos(int die[]);
int cal_sum_of_threes(int die[]);
int cal_sum_of_fours(int die[]);
int cal_sum_of_fives(int die[]);
int cal_sum_of_sixes(int die[]);
int cal_three_of_a_kind(int die[]);
int cal_four_of_a_kind(int die[]);
int cal_full_house(int die[]);
int cal_small_straight(int die[]);
int cal_large_straight(int die[]);
int cal_yahtzee(int die[]);
int cal_chance(int die[]);
void sort_dice(int die[]);
void print_score_card(int score_card[], int score_card_tracker[], char user[]);
int get_reroll_die_amt(void);
void get_reroll_die(int reroll_die[], int reroll_die_amt);
void reroll_die(int reroll_die_amt, int reroll_die_arr[], int die[]);
void determine_winner(int p1_score_card[], int p2_score_card[]);