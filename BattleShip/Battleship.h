/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Programming Assignment 6: Basic game of Battleship
Description: This program allows the user to play the game of Battleship with computer player
*/
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROW_NUMS 10
#define COL_NUMS 10
#define SHIP_NUMS 5
#define PLAYER1 0
#define PLAYER2 1
#define HORIZONTAL 0
#define VERTICAL 1

typedef struct stats {
	char name[8];
	int hits;
	int misses;
	int total;
	int ratio;
}Stats;

void driver(void);
void welcome_screen(void);
void initialize_game_board(char board[][COL_NUMS]);
void copy_board(char des[][COL_NUMS], char source[][COL_NUMS]);
int select_who_starts_first(void);
int select_way_to_place_ships(void);
void sort_arr(int arr[], int arr_size);
int is_same(int arr[], int arr_size);
int is_in_order(int arr[], int arr_size);
int is_valid_direction(int rows[], int cols[], int size);
int is_valid_cells(char board[][COL_NUMS], int rows[], int cols[], int size);
void manually_place_ships_on_board(char board[][COL_NUMS], char ship_symbols[], int ship_lengths[]);
int gen_direction(void);
void gen_start_point(int dir, int ship_length, int *row_ptr, int *col_ptr);
void randomly_place_ships_on_board(char board[][COL_NUMS], char ship_symbols[], int ship_lengths[]);
void prompt_target(char board[ROW_NUMS][COL_NUMS], int *row_target_ptr, int *col_target_ptr);
int check_shot(char board[ROW_NUMS][COL_NUMS], int row, int col, Stats *player);
int is_winner(Stats player);
void update_board(char board[ROW_NUMS][COL_NUMS], int row, int col, int is_shot);
void display_board(char board[][COL_NUMS], int player);
void output_current_move(FILE *outfile, Stats player, int row, int col, int is_shot, int is_sunk, char ship);
int check_if_sunk_ship(char board[ROW_NUMS][COL_NUMS], char board_to_display[ROW_NUMS][COL_NUMS], int row, int col, int is_shot, char *ship);
void output_stats(FILE *outfile, Stats p1, Stats p2);
void random_point(char board[ROW_NUMS][COL_NUMS], int *row, int *col);
void cal_stats(Stats *p1, Stats *p2);

#endif