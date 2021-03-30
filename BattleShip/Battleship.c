/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Programming Assignment 6: Basic game of Battleship
Description: This program allows the user to play the game of Battleship with computer player
*/
#include "Battleship.h"

// driver
void driver(void) {
	// declare variables
	FILE *outfile = NULL;
	char board_p1[ROW_NUMS][COL_NUMS] = { { '\0' } }, board_p2[ROW_NUMS][COL_NUMS] = { { '\0' } };
	char board_p1_to_display[ROW_NUMS][COL_NUMS] = { { '\0' } }, board_p2_to_display[ROW_NUMS][COL_NUMS] = { { '\0' } };
	char ship_symbols[SHIP_NUMS] = { 'c', 'b', 'r', 's', 'd' }, ship = '\0';
	int ship_lengths[SHIP_NUMS] = { 5, 4, 3, 3, 2 };
	int starter = 0, place_ships = 0, row_target = 0, col_target = 0, is_shot = 0, is_p1_win = 0, is_p2_win = 0, round = 0, is_sunk = 0;
	Stats p1 = { "Player1", 0, 0, 0, 0 }, p2 = { "Player2", 0, 0, 0, 0 };

	srand((unsigned int)time(NULL));
	// open file to write
	outfile = fopen("battleship.log", "w");

	welcome_screen();
	initialize_game_board(board_p1);
	initialize_game_board(board_p2);

	// prompt the user the way to place ships
	place_ships = select_way_to_place_ships();
	if (place_ships == 1) {
		manually_place_ships_on_board(board_p1, ship_symbols, ship_lengths); // manually
	}
	else {
		randomly_place_ships_on_board(board_p1, ship_symbols, ship_lengths); // randomly
	}
	// make another board of player 1 for display
	copy_board(board_p1_to_display, board_p1);
	// generate computer's board
	randomly_place_ships_on_board(board_p2, ship_symbols, ship_lengths);
	// create board for display of player 2
	initialize_game_board(board_p2_to_display);
	printf("Player2 (Computer's) board has been generated.\n");

	// randomly select the starter
	starter = select_who_starts_first();
	// user starts first
	if (starter == PLAYER1) {
		printf("Player1 has been randomly selected to go first.\n");
		display_board(board_p1_to_display, PLAYER1);
		display_board(board_p2_to_display, PLAYER2);
		do {
			// player 1's round
			if (round % 2 == 0) {
				do {
					prompt_target(board_p2_to_display, &row_target, &col_target); // prompt, check same position and clear screen
					is_shot = check_shot(board_p2, row_target, col_target, &p1); // check and print the result of shot
					update_board(board_p2_to_display, row_target, col_target, is_shot);
					is_sunk = check_if_sunk_ship(board_p2, board_p2_to_display, row_target, col_target, is_shot, &ship); // check and print the result of sunk
					display_board(board_p1_to_display, PLAYER1);
					display_board(board_p2_to_display, PLAYER2);
					output_current_move(outfile, p1, row_target, col_target, is_shot, is_sunk, ship); // write to logfile
					is_p1_win = is_winner(p1); // check and print the result if win
				} while (is_shot && !is_p1_win); // player 1 keep playing until miss or win
			}
			else // player 2's round
			{
				do {
					random_point(board_p1_to_display, &row_target, &col_target);
					is_shot = check_shot(board_p1, row_target, col_target, &p2);
					update_board(board_p1_to_display, row_target, col_target, is_shot);
					is_sunk = check_if_sunk_ship(board_p1, board_p1_to_display, row_target, col_target, is_shot, &ship);
					display_board(board_p1_to_display, PLAYER1);
					display_board(board_p2_to_display, PLAYER2);
					output_current_move(outfile, p2, row_target, col_target, is_shot, is_sunk, ship);
					is_p2_win = is_winner(p2); // check and print the result
				} while (is_shot && !is_p2_win);// player 2 keep playing until miss or win
			}
			++round;
		} while (!is_p1_win && !is_p2_win); // keep playing game until someone win
	}
	else { // computer starts first
		printf("Player2 has been randomly selected to go first.\n");
		display_board(board_p1_to_display, PLAYER1);
		display_board(board_p2_to_display, PLAYER2);
		do {
			// player 2's round
			if (round % 2 == 0) {
				do {
					random_point(board_p1_to_display, &row_target, &col_target);
					is_shot = check_shot(board_p1, row_target, col_target, &p2);
					update_board(board_p1_to_display, row_target, col_target, is_shot);
					is_sunk = check_if_sunk_ship(board_p1, board_p1_to_display, row_target, col_target, is_shot, &ship);
					display_board(board_p1_to_display, PLAYER1);
					display_board(board_p2_to_display, PLAYER2);
					output_current_move(outfile, p2, row_target, col_target, is_shot, is_sunk, ship);
					is_p2_win = is_winner(p2); // check and print the result
				} while (is_shot && !is_p2_win);
			}
			else { // player 1's round
				do {
					prompt_target(board_p2_to_display, &row_target, &col_target); // prompt, check same position and clear screen
					is_shot = check_shot(board_p2, row_target, col_target, &p1); // check and print the result
					update_board(board_p2_to_display, row_target, col_target, is_shot);
					is_sunk = check_if_sunk_ship(board_p2, board_p2_to_display, row_target, col_target, is_shot, &ship);
					display_board(board_p1_to_display, PLAYER1);
					display_board(board_p2_to_display, PLAYER2);
					output_current_move(outfile, p1, row_target, col_target, is_shot, is_sunk, ship);
					is_p1_win = is_winner(p1); // check and print the result
				} while (is_shot && !is_p1_win);
			}
			++round;
		} while (!is_p1_win && !is_p2_win);
	}
	cal_stats(&p1, &p2); // calculate stats
	output_stats(outfile, p1, p2); // write the stats to logfile
	fclose(outfile); // close file
}

// print welcome screen
void welcome_screen(void)
{
	printf("***** Welcome to Battleship! *****\n\n");
	printf("Rules of the Game:\n");
	printf("1. This is a two player game.\n");
	printf("2. Player1 is you and Player2 is the computer.\n");
	printf("3. You have two options to place five ships, manually or randomly by the program.\n");
	printf("4. The five ships are:\n");
	printf("\t- Carrier: with five cells\n");
	printf("\t- Batttleship: with four cells\n");
	printf("\t- Cruiser: with three cells\n");
	printf("\t- Submarine: with three cells\n");
	printf("\t- Destroyer: with two cells\n");
	printf("5. Each ship must be placed horizontally or vertically, not diagonally.\n");
	printf("6. Ships can touch each other, but they can't occupy the same cell space.\n");
	printf("7. The program will randomly pick the first player.\n");
	printf("8. On your turn, you need to guess a row and column number on your target board to fire a shot.\n");
	printf("9. If you have correctly guessed a space that is occupied by one of the computer's ships, it's a hit.\n");
	printf("   Otherwise, it's a miss.\n");
	printf("9. Each hit will be specified with '*' and each miss will be specified with 'm'.\n");
	printf("10. You keep continuing shoot until you miss, then the computer takes turn and do the same.\n");
	printf("11. Alternate back and forth in this manner until one player sinks all the opposing ships and wins the game.\n\n");
	printf("Hit enter to start the game!\n");
	system("pause");
	system("cls");
}

// initialise game board to '-'
void initialize_game_board(char board[][COL_NUMS])
{
	for (int row_index = 0; row_index < ROW_NUMS; ++row_index) {
		for (int col_index = 0; col_index < COL_NUMS; ++col_index) {
			board[row_index][col_index] = '-';
		}
	}
}

// copy game board
void copy_board(char des[][COL_NUMS], char source[][COL_NUMS])
{
	for (int row_index = 0; row_index < ROW_NUMS; ++row_index) {
		for (int col_index = 0; col_index < COL_NUMS; ++col_index) {
			des[row_index][col_index] = source[row_index][col_index];
		}
	}
}

// randomly select the starter
int select_who_starts_first(void)
{
	int starter;
	starter = rand() % 2;
	return starter;
}

// prompt the user for the wat to place ships
int select_way_to_place_ships(void)
{
	int place_ships = 0;
	printf("Please select from the following menu:\n");
	printf("1. Enter positions of ships manually.\n");
	printf("2. Allow the program to randomly select positions of ships.\n");
	scanf("%d", &place_ships);
	system("cls");
	return place_ships;
}

// sort array
void sort_arr(int arr[], int arr_size)
{
	int temp_val = 0;
	for (int i = 0; i < arr_size; ++i) {
		for (int j = i + 1; j < arr_size; ++j) {
			if (arr[j] < arr[i]) {
				temp_val = arr[i];
				arr[i] = arr[j];
				arr[j] = temp_val;
			}
		}
	}
}

// check if all element in an array are equal
int is_same(int arr[], int arr_size)
{
	int same = 0, dif = 0;

	for (int i = 0; i < arr_size - 1; ++i) {
		if (arr[i] != arr[i + 1]) {
			dif += 1;
		}
	}
	
	if (dif == 0) {
		same = 1;
	}
	else {
		same = 0;
	}

	return same;
}

// check if all elements in an array are in order
// an array need to be sorted
int is_in_order(int arr[], int arr_size)
{
	int is_ordered = 0, inorder = 0;
	for (int i = 0; i < arr_size - 1; ++i) {
		if (arr[i] != (arr[i + 1] - 1)) {
			inorder += 1;
		}
	}
	if (inorder == 0) {
		is_ordered = 1;
	}
	else {
		is_ordered = 0;
	}

	return is_ordered;
}

// check if the ship was place horizontally or vertically
int is_valid_direction(int rows[], int cols[], int size)
{
	int valid_dir = 0;
	if ((is_same(rows, size) && is_in_order(cols, size) ||
		is_same(cols, size) && is_in_order(rows, size))) {
		valid_dir = 1;
	}
	else {
		valid_dir = 0;
	}
	return valid_dir;
}

// check if the cell already has a ship
int is_valid_cells(char board[][COL_NUMS], int rows[], int cols[], int size)
{
	int valid_cells = 0, check = 0; 
	for (int i = 0; i < size; ++i) {
		if (board[rows[i]][cols[i]] != '-') {
			check += 1;
		}
	}
	if (check == 0) {
		valid_cells = 1;
	}
	else {
		valid_cells = 0;
	}

	return valid_cells;
}

/* prompt the user for the location of the ships
 * check the validation
 * and put the ships on the board
*/
void manually_place_ships_on_board(char board[][COL_NUMS], char ship_symbols[], int ship_lengths[])
{
	int rows[5] = { 0 }, cols[5] = { 0 };
	char ship_sizes[SHIP_NUMS][6] = { {"five"}, {"four"}, {"three"}, {"three"}, {"two"} };
	char ship_names[SHIP_NUMS][12] = { {"Carrier"}, {"Battleship"}, {"Cruiser"}, {"Submarine"}, {"Destroyer"} };

	for (int ship_index = 0; ship_index < SHIP_NUMS; ++ship_index) {
		// prompt cells to place the battleship
		printf("Please enter the %s cells to place the %s across:\n", ship_sizes[ship_index], ship_names[ship_index]);
		for (int i = 0; i < ship_lengths[ship_index]; ++i) {
			scanf("%d%d", (rows + i), (cols + i));
		}
		// sort the arrays
		sort_arr(rows, ship_lengths[ship_index]);
		sort_arr(cols, ship_lengths[ship_index]);
		// check direction validation
		while (!(is_valid_direction(rows, cols, ship_lengths[ship_index]) && is_valid_cells(board, rows, cols, ship_lengths[ship_index]))) {
			if (!is_valid_direction(rows, cols, ship_lengths[ship_index])) {
				printf("Each ship must be placed horizontally or vertically only!\n");
			}
			if (!is_valid_cells(board, rows, cols, ship_lengths[ship_index])) {
				printf("Ships can't occupy the same cell space\n");
			}
			printf("Please enter the %s cells to place the %s across:\n", ship_sizes[ship_index], ship_names[ship_index]);
			for (int i = 0; i < ship_lengths[ship_index]; ++i) {
				scanf("%d%d", (rows + i), (cols + i));
			}
			sort_arr(rows, ship_lengths[ship_index]);
			sort_arr(cols, ship_lengths[ship_index]);
		}

		// place the battleship on the board
		for (int i = 0; i < ship_lengths[ship_index]; ++i) {
			board[rows[i]][cols[i]] = ship_symbols[ship_index];
		}
	}

	system("cls");
}

// generate direction
int gen_direction(void)
{
	int dir = 0;
	dir = rand() % 2;
	return dir;
}

// generate the starting point
void gen_start_point(int dir, int ship_length, int *row_ptr, int *col_ptr)
{
	if (dir == HORIZONTAL) // horizontal
	{
		*row_ptr = rand() % ROW_NUMS;
		*col_ptr = rand() % (COL_NUMS - ship_length + 1);
	}
	else // vertical
	{
		*row_ptr = rand() % (ROW_NUMS - ship_length + 1);
		*col_ptr = rand() % COL_NUMS;
	}
}

/*
 * check for the validation of the cell that is going to be put ship on
 * if no ships at the cell,
 * put the ship on the board with direction and starting point
*/
void randomly_place_ships_on_board(char board[][COL_NUMS], char ship_symbols[], int ship_lengths[])
{
	int index = 0, dir = 0, row_str_pt = 0, col_str_pt = 0, has_ship = 0;
	for (int i = 0; i < SHIP_NUMS; ++i) {
		do {
			has_ship = 0;
			dir = gen_direction();
			gen_start_point(dir, ship_lengths[i], &row_str_pt, &col_str_pt);
			// check if there is ship  on the cell that the ship is going to be put
			if (dir == HORIZONTAL) {
				for (int j = 0; j < ship_lengths[i]; ++j) {
					if (board[row_str_pt][col_str_pt + j] != '-') {
						has_ship += 1;
					}
				}
			}
			else { // vertical
for (int j = 0; j < ship_lengths[i]; ++j) {
	if (board[row_str_pt + j][col_str_pt] != '-') {
		has_ship += 1;
	}
}
			}
		} while (has_ship);

		if (dir == HORIZONTAL) {
			for (int j = 0; j < ship_lengths[i]; ++j) {
				board[row_str_pt][col_str_pt + j] = ship_symbols[i];
			}
		}
		else { // vertical
			for (int j = 0; j < ship_lengths[i]; ++j) {
				board[row_str_pt + j][col_str_pt] = ship_symbols[i];
			}
		}
	}
}

// display a board
void display_board(char board[][COL_NUMS], int player)
{
	if (player == PLAYER1) {
		printf("Player1's Board:\n");
	}
	else { // player2
		printf("Player2's Board:\n");
	}
	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for (int row_index = 0; row_index < ROW_NUMS; ++row_index) {
		printf("%d ", row_index);
		for (int col_index = 0; col_index < COL_NUMS; ++col_index) {
			printf("%c ", board[row_index][col_index]);
		}
		putchar('\n');
	}
}

/*
 * prompt user for the target and check if it has been selected
 * if it is already selected keep prompting until the valid one is put
 */
void prompt_target(char board[ROW_NUMS][COL_NUMS], int *row_target_ptr, int *col_target_ptr)
{
	int valid = 0;
	printf("Enter a target: ");
	scanf("%d%d", row_target_ptr, col_target_ptr);
	// check if the position has been selected
	if ((board[*row_target_ptr][*col_target_ptr] == '*') || (board[*row_target_ptr][*col_target_ptr] == 'm')) {
		valid = 0;
	}
	else {
		valid = 1;
	}
	while (!valid) {
		printf("The target was selected! Please Enter a new one: ");
		scanf("%d%d", row_target_ptr, col_target_ptr);
		if ((board[*row_target_ptr][*col_target_ptr] == '*') || (board[*row_target_ptr][*col_target_ptr] == 'm')) {
			valid = 0;
		}
		else {
			valid = 1;
		}
	}
	system("cls");
}

/*
* check if the shot hit the ships and return the result
*/
int check_shot(char board[ROW_NUMS][COL_NUMS], int row, int col, Stats *player)
{
	int is_shot = 0;
	if (board[row][col] != '-') {
		is_shot = 1;
		player -> hits += 1;
		printf("%d,%d is a hit!\n", row, col);
	}
	else {
		player-> misses += 1;
		printf("%d,%d is a miss!\n", row, col);
		system("pause");
		system("cls");
	}
	return is_shot;
}

/*
* check if the player win
*/
int is_winner(Stats player)
{
	int win = 0;
	if (player.hits == 17) {
		win = 1;
		printf("%s Wins!\n", player.name);
		printf("Statistics outputted to logfile successfully!\n");
	}
	return win;
}

/*
* update the board
* if the shot hit, change to '*'
* if the shot miss, change to 'm'
*/
void update_board(char board[ROW_NUMS][COL_NUMS], int row, int col, int is_shot)
{
	if (is_shot) {
		board[row][col] = '*';
	}
	else {
		board[row][col] = 'm';
	}
}
/*
* write the report of each round to the logfile
*/
void output_current_move(FILE *outfile, Stats player, int row, int col, int is_shot, int is_sunk, char ship)
{
	if (is_shot) {
		fprintf(outfile, "%s: %d,%d \"%s", player.name, row, col, "hit");
		if (is_sunk) {
			switch (ship) {
			case 'c': fprintf(outfile, " Sunk Carrier!\n");
				break;
			case 'b': fprintf(outfile, " Sunk Battleship!\n");
				break;
			case 'r': fprintf(outfile, " Sunk Cruiser!\n");
				break;
			case 's': fprintf(outfile, " Sunk Submarine!\n");
				break;
			case 'd': fprintf(outfile, " Sunk Destroyer!\n");
				break;
			}
		}
		else {
			fprintf(outfile, "\n");
			}
	}
	else {
		fprintf(outfile, "%s: %d,%d \"%s\"\n", player.name, row, col, "miss");
	}
}

/*
* check if the ship is sunk, report if any ship is sunk and return the result
*/
int check_if_sunk_ship(char board[ROW_NUMS][COL_NUMS], char board_to_display[ROW_NUMS][COL_NUMS], int row, int col, int is_shot, char *ship)
{
	int is_sunk = 0;
	

	if (is_shot) {
		*ship = board[row][col];


		for (int row_index = 0; row_index < ROW_NUMS; ++row_index) {
			for (int col_index = 0; col_index < COL_NUMS; ++col_index) {
				if ((board[row_index][col_index] == *ship) && (board_to_display[row_index][col_index] != '*')) {
					is_sunk = 0;
					return is_sunk;
				}
			}
		}

		is_sunk = 1;
		switch (*ship) {
		case 'c': printf("Sunk Carrier!\n");
			break;
		case 'b': printf("Sunk Battleship!\n");
			break;
		case 'r': printf("Sunk Cruiser!\n");
			break;
		case 's': printf("Sunk Submarine!\n");
			break;
		case 'd': printf("Sunk Destroyer!\n");
			break;
		}
		
	}
	return is_sunk;
}

// write the stats of two player to the logfile
void output_stats(FILE *outfile, Stats p1, Stats p2)
{
	fprintf(outfile, "\n");
	if (p1.hits == 17) {
		fprintf(outfile, "%s wins, %s loses\n", p1.name, p2.name);
	}
	else {
		fprintf(outfile, "%s wins, %s loses\n", p2.name, p1.name);
	}
	fprintf(outfile, "\n");
	
	fprintf(outfile, "*** %s Stats ***\n", p1.name);
	fprintf(outfile, "Number Hits: %d\n", p1.hits);
	fprintf(outfile, "Number Misses: %d\n", p1.misses);
	fprintf(outfile, "Total Shots: %d\n", p1.total);
	fprintf(outfile, "Hit/Miss Ratio: %d%%\n", p1.ratio);
	fprintf(outfile, "\n");
	fprintf(outfile, "*** %s Stats ***\n", p2.name);
	fprintf(outfile, "Number Hits: %d\n", p2.hits);
	fprintf(outfile, "Number Misses: %d\n", p2.misses);
	fprintf(outfile, "Total Shots: %d\n", p2.total);
	fprintf(outfile, "Hit/Miss Ratio: %d%%\n", p2.ratio);
}

// generate random target for computer player
void random_point(char board[ROW_NUMS][COL_NUMS], int *row, int *col)
{
	int valid = 0;
	do {
		*row = rand() % 10;
		*col = rand() % 10;
		if (board[*row][*col] == '*' || board[*row][*col] == 'm') {
			valid = 0;
		}
		else {
			valid = 1;
		}
	} while (!valid);
	printf("Player 2 select a target %d,%d\n", *row, *col);
	system("pause");
	system("cls");
}

// calculate the stats of two players
void cal_stats(Stats *p1, Stats *p2)
{
	p1->total = p1->hits + p1->misses;
	p1->ratio = ((double)p1->hits / (double)p1->misses) * 100;
	p2->total = p2->hits + p2->misses;
	p2->ratio = ((double)p2->hits / (double)p2->misses) * 100;
}