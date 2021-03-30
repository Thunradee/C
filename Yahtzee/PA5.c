/*
Programmer: Thunradee Tangsupakij
Class: CptS 121
Programming Assignment 5: The Game of Yahtzee
Description: This program allows the user to play the game of Yathzee
*/

#include "PA5.h"

// the driver
void run_yahtzee(void)
{
	int option = 0, roll_num = 0, reroll_die_amt = 0, combination = 0, update_score_card_status = 0, round_num = 1;
	char use_combinations_option = '\0', p1[3] = { 'P', '1', '\0' }, p2[3] = { 'P', '2', '\0' };
	int die[DIE_SIZE] = { 0 }, reroll_die_arr[DIE_SIZE] = { 0 };

	srand((unsigned int)time(NULL));

	do {
		round_num = 1; 
		int p1_score_card[SCORE_CARD_SIZE] = { 0 }, p1_score_card_tracker[SCORE_CARD_SIZE] = { 0 };
		int p2_score_card[SCORE_CARD_SIZE] = { 0 }, p2_score_card_tracker[SCORE_CARD_SIZE] = { 0 };
		// print the menu
		print_menu();
		//get option
		get_option(&option);
		// keep getting the option if the option is invalid
		while (option <= 1 && option >= 3) {
			get_option(&option);
		}

		// print the game rules
		if (option == 1) {
			print_game_rules();
			print_menu();
			get_option(&option);
		}
		// start the game
		if (option == 2) {
			while (round_num < 27) {
				// Player 1
				if (round_num % 2 == 1) {
					printf("Player 1 get ready\n");
					roll_num = 0;
					update_score_card_status = 0;
					roll_die(die);
					roll_num += 1;
					print_die_values(die);
					// ask player 1 if she/he wants to use the roll for combination
					while (roll_num < 3) {
						print_combinations();
						use_combinations_option = get_use_combinations();
						if (use_combinations_option == 'Y' || use_combinations_option == 'y') {
							roll_num = 3;
							}
						// if not
						else {
							// ask how mant die she/he wants to roll again
							reroll_die_amt = get_reroll_die_amt();
							get_reroll_die(reroll_die_arr, reroll_die_amt);
							reroll_die(reroll_die_amt, reroll_die_arr, die);
							print_die_values(die);
							roll_num += 1;
						}
						
					}
					system("cls");
					print_die_values(die);
					print_combinations();
					// prompt the combination
					while (update_score_card_status == 0) {
						combination = get_combination();
						update_score_card_status = update_score_card(combination, p1_score_card, p1_score_card_tracker, die);
					}
					print_score_card(p1_score_card, p1_score_card_tracker, p1);
					system("pause");
					system("cls");
					round_num += 1;
				}
				// P2
				else {
					printf("Player 2 get ready\n");
					roll_num = 0;
					update_score_card_status = 0;
					roll_die(die);
					roll_num += 1;
					print_die_values(die);

					while (roll_num < 3) {
						print_combinations();
						use_combinations_option = get_use_combinations();
						if (use_combinations_option == 'Y' || use_combinations_option == 'y') {
							roll_num = 3;
						}
						else {
							reroll_die_amt = get_reroll_die_amt();
							get_reroll_die(reroll_die_arr, reroll_die_amt);
							reroll_die(reroll_die_amt, reroll_die_arr, die);
							print_die_values(die);
							roll_num += 1;
						}

					}
					system("cls");
					print_die_values(die);
					print_combinations();
					while (update_score_card_status == 0) {
						combination = get_combination();
						update_score_card_status = update_score_card(combination, p2_score_card, p2_score_card_tracker, die);
					}
					print_score_card(p2_score_card, p2_score_card_tracker, p2);
					system("pause");
					system("cls");
					round_num += 1;
				}
			}
			// print scores of both players and the winner
			printf("Player 1's scores: %d\n", p1_score_card[COMBINE_TOTAL_INDEX]);
			printf("PLayer 2's scores: %d\n", p2_score_card[COMBINE_TOTAL_INDEX]);
			determine_winner(p1_score_card, p2_score_card);
			system("pause");
		}

		// the option is "Exit", print good bye message
		if (option == 3) {
			printf("Good Bye!\n");
		}

	} while (option != 3);
}
	
	void print_menu(void)
	{
		system("cls");
		printf("********* Welcome to the Game of Yathzee! *********\n\n");
		printf("Menu:\n");
		printf("1. Print game rules\n");
		printf("2. Start a game of Yahtzee\n");
		printf("3. Exit\n");
	}

	// get menu option
	void get_option(int *option)
	{
		printf("Enter the option: ");
		scanf("%d", option);

		system("cls");
	}

	void print_game_rules()
	{
		printf("The Rules of Yahtzee:\n\n");
		printf("The scorecard used for Yahtzee is composed of two sections.\n");
		printf("A upper section and a lower section.\n");
		printf("A total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\n");
		printf("The upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\n");
		printf("If a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\n");
		printf("Once a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\n");
		printf("If the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\n");
		printf("The lower section contains a number of poker like combinations. See the table provided below:\n\n");
		printf("Name\t\t\tCombination\t\t\t\tScore\n");
		printf("Three-of-a-kind\t\tThree dice with the same face\t\tSum of all face values on the 5 dice\n");
		printf("Four-of-a-kind\t\tFour dice with the same face\t\tSum of all face values on the 5 dice\n");
		printf("Full house\t\tOne pair and a three-of-a-kind\t\t25\n");
		printf("Small straight\t\tA sequence of four dice\t\t\t30\n");
		printf("Large straight\t\tA sequence of five dice\t\t\t40\n");
		printf("Yahtzee\t\t\tFive dice with the same face\t\t50\n");
		printf("Chance\t\t\tMay be used for any sequence of dice\tSum of all face values on the 5 dice\n");

		system("pause");
	}

	void roll_die(int die[])
	{
		printf("Press any key to roll dice\n");
		system("pause");
		for (int i = 0; i < 5; ++i) {
			die[i] = (rand() % 6) + 1;
		}
		system("cls");
	}

	void print_die_values(int die[])
	{
		for (int i = 0; i < 5; ++i) {
			printf("die%d: %d\n", i + 1, die[i]);
		}
	}

	// ask users if they want to use the roll for one of the game combination
	char get_use_combinations(void)
	{
		char option = '\0';
		printf("Do you wants to use the roll for one of the game combinations (Y/N): ");
		scanf(" %c", &option);
		while (option != 'Y' && option != 'N' && option != 'y' && option != 'n') {
			printf("This option is invalid.\n");
			printf("Do you wants to use the roll for one of the game combinations (Y/N): ");
			scanf(" %c", &option);
		}
		return option;
	}

	void print_combinations(void)
	{
		/*char *combination_arr[] = {" ",  
			"1. Sum of 1's\n",
			"2. Sum of 2's\n",
			"3. Sum of 3's\n",
			"4. Sum of 4's\n",
			"5. Sum of 5's\n",
			"6. Sum of 6's\n",
			"7. Three-of-a-kind\t\tThree dice with the same face\t\tSum of all face values on the 5 dice\n",
			"8. Four - of - a - kind\t\tFour dice with the same face\t\tSum of all face values on the 5 dice\n",
			"9. Full house\t\t\tOne pair and a three-of-a-kind\t\t25\n",
			"10. Small straight\t\tA sequence of four dice\t\t\t30\n",
			"11. Large straight\t\tA sequence of five dice\t\t\t40\n",
			"12. Yahtzee\t\t\tFive dice with the same face\t\t50\n",
			"13. Chance\t\t\tMay be used for any sequence of dice\tSum of all face values on the 5 dice\n"
		};

		printf("\n");
		printf("UPPER SECTION\n");
		for (int i = 0; i <= UPPER_SIZE; ++i) {
			if (score_card_tracker[i] == 0) {
				printf("%s", combination_arr[i]);
			}
		}
		printf("\n");
		printf("LOWER SECTION\n");
		for (int i = 7; i < COMBINATION_SCORE_CARD_SIZE - UPPER_SIZE; ++i) {
			if (score_card_tracker[i] == 0) {
				printf("%s", combination_arr[i]);
			}
		}*/

		
		printf("\n");
		printf("UPPER SECTION\n");
		printf("1. Sum of 1's\n");
		printf("2. Sum of 2's\n");
		printf("3. Sum of 3's\n");
		printf("4. Sum of 4's\n");
		printf("5. Sum of 5's\n");
		printf("6. Sum of 6's\n");
		printf("\n");
		printf("LOWER SECTION\n");
		printf("7. Three-of-a-kind\t\tThree dice with the same face\t\tSum of all face values on the 5 dice\n");
		printf("8. Four-of-a-kind\t\tFour dice with the same face\t\tSum of all face values on the 5 dice\n");
		printf("9. Full house\t\t\tOne pair and a three-of-a-kind\t\t25\n");
		printf("10. Small straight\t\tA sequence of four dice\t\t\t30\n");
		printf("11. Large straight\t\tA sequence of five dice\t\t\t40\n");
		printf("12. Yahtzee\t\t\tFive dice with the same face\t\t50\n");
		printf("13. Chance\t\t\tMay be used for any sequence of dice\tSum of all face values on the 5 dice\n");
	}

	int get_combination(void)
	{
		int combination = 0;
		while (combination < 1 || combination > 13) {
			printf("Enter the number of combination you want to use: ");
			scanf("%d", &combination);
		}
		system("cls");
		return combination;
	}

	int update_score_card(int combination, int score_card[], int score_card_tracker[], int die[])
	{
		int score = 0, status = 0, total = 0, lower_total = 0, combine_total = 0;
		if (score_card_tracker[combination] == 0) {
			if (combination == 1) {
				score = cal_sum_of_aces(die);
			}
			else if (combination == 2) {
				score = cal_sum_of_twos(die);
			}
			else if (combination == 3) {
				score = cal_sum_of_threes(die);
			}
			else if (combination == 4) {
				score = cal_sum_of_fours(die);
			}
			else if (combination == 5) {
				score = cal_sum_of_fives(die);
			}
			else if (combination == 6) {
				score = cal_sum_of_sixes(die);
			}
			else if (combination == 7) {
				score = cal_three_of_a_kind(die);
			}
			else if (combination == 8) {
				score = cal_four_of_a_kind(die);
			}
			else if (combination == 9) {
				score = cal_full_house(die);
			}
			else if (combination == 10) {
				score = cal_small_straight(die);
			}
			else if (combination == 11) {
				score = cal_large_straight(die);
			}
			else if (combination == 12) {
				score = cal_yahtzee(die);
			}
			else if (combination == 13) {
				score = cal_chance(die);
			}
			score_card[combination] = score;
			score_card_tracker[combination] = 1;
			status = 1;

			// update total score
			for (int i = 1; i <= UPPER_SIZE; ++i) {
				total += score_card[i];
			}
			score_card[TOTAL_INDEX] = total;

			// update bonus score
			if (score_card[TOTAL_INDEX] >= SCORE_TO_GET_BONUS) {
				score_card[BONUS_INDEX] = BONUS;
			}

			//update upper total score
			score_card[UPPER_TOTAL_INDEX] = score_card[TOTAL_INDEX] + score_card[BONUS_INDEX];

			//update lower total score
			for (int i = 7; i < COMBINATION_SCORE_CARD_SIZE; ++i) {
				lower_total += score_card[i];
			}
			score_card[LOWER_TOTAL_INDEX] = lower_total;

			// update combine total
			score_card[COMBINE_TOTAL_INDEX] = score_card[UPPER_TOTAL_INDEX] + score_card[LOWER_TOTAL_INDEX];
		} 
		else {
			printf("This combination was used!\n");
			print_die_values(die);
			print_combinations();
		}
		return status;
	}

	int cal_sum_of_aces(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 1) {
				score += 1;
			}
		}
		return score;
	}

	int cal_sum_of_twos(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 2) {
				score += 2;
			}
		}
		return score;
	}

	int cal_sum_of_threes(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 3) {
				score += 3;
			}
		}
		return score;
	}

	int cal_sum_of_fours(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 4) {
				score += 4;
			}
		}
		return score;
	}

	int cal_sum_of_fives(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 5) {
				score += 5;
			}
		}
		return score;
	}

	int cal_sum_of_sixes(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			if (die[i] == 6) {
				score += 6;
			}
		}
		return score;
	}

	int cal_three_of_a_kind(int die[])
	{
		int score = 0, count = 0;
		for (int i = 1; i <= 6 ; ++i) {
			count = 0;
			for (int j = 0; j < DIE_SIZE; ++j) {
				if (die[j] == i) {
					count += 1;
				}
				if (count == 3) {
					for (int k = 0; k < DIE_SIZE; ++k) {
						score += die[k];
					}
					j = DIE_SIZE;
					i = 7;
				}
			}
		}
		return score;
	}

	int cal_four_of_a_kind(int die[])
	{
		int score = 0, count = 0;
		for (int i = 1; i <= 6; ++i) {
			count = 0;
			for (int j = 0; j < DIE_SIZE; ++j) {
				if (die[j] == i) {
					count += 1;
				}
				if (count == 4) {
					for (int k = 0; k < DIE_SIZE; ++k) {
						score += die[k];
					}
				}
			}
		}
		return score;
	}

	int cal_full_house(int die[])
	{
		int score = 0, index = 0;
		sort_dice(die);
		
		if ((die[index] == die[index + 1]) && ((die[index + 2] == die[index + 3]) && (die[index + 3] == die[index + 4]))) {
			score = 25;
		}
		else if (((die[index] == die[index + 1]) && (die[index + 1] == die[index + 2])) && (die[index + 3] == die[index + 4])) {
			score = 25;
		}
		return score;
	}

	int cal_small_straight(int die[])
	{
		int score = 0, index = 1;
		sort_dice(die);
		for (int i = 0; i < DIE_SIZE - 1; ++i) {
			if (die[i] == ((die[i + 1]) - 1)) {
				index += 1;
			}
			else {
				index -= 1;
			}
			if (index >= 3) {
				score = 30;
			}
		}
		return score;
	}

	int cal_large_straight(int die[])
	{
		int score = 0, index = 1;
		sort_dice(die);
		for (int i = 0; i < DIE_SIZE - 1; ++i) {
			if (die[i] == ((die[i + 1]) - 1)) {
				index += 1;
			}
			else {
				index = -1;
			}
			if (index == 5) {
				score = 40;
			}
		}
		return score;
	}

	int cal_yahtzee(int die[])
	{
		int score = 0, count = 0;
		for (int i = 1; i <= 6; ++i) {
			count = 0;
			for (int j = 0; j < DIE_SIZE; ++j) {
				if (die[j] == i) {
					count += 1;
				}
				if (count == 5) {
					score = 50;
				}
			}
		}
		return score;
	}

	int cal_chance(int die[])
	{
		int score = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			score += die[i];
		}
		return score;
	}

	void sort_dice(int die[])
	{
		int temp_val = 0;
		for (int i = 0; i < DIE_SIZE; ++i) {
			for (int j = i + 1; j < DIE_SIZE; ++j) {
				if (die[j] < die[i]) {
					temp_val = die[i];
					die[i] = die[j];
					die[j] = temp_val;
				}
			}
		}
	}

	void print_score_card(int score_card[], int score_card_tracker[], char user[])
	{
		int i = 1;
			printf("_______________________________________\n");
			printf("        %s's YAHTZEE SCORE CARD        \n", user);
			printf("_______________________________________\n");
			printf(" UPPER SECTION    | SCORES            \n");
			printf("__________________|____________________\n");
			if (score_card_tracker[i] == 0) {
				printf(" Aces             |                 \n");
			}
			else {
				printf(" Aces             | %d                \n", score_card[i]);
			}
			if (score_card_tracker[i + 1] == 0) {
				printf(" Twos             |                 \n");
			}
			else {
				printf(" Twos             | %d                \n", score_card[i + 1]);
			}
			if (score_card_tracker[i + 2] == 0) {
				printf(" Threes           |                 \n");
			}
			else {
				printf(" Threes           | %d                \n", score_card[i + 2]);
			}
			if (score_card_tracker[i + 3] == 0) {
				printf(" Fours            |                 \n");
			}
			else {
				printf(" Fours            | %d                \n", score_card[i + 3]);
			}
			if (score_card_tracker[i + 4] == 0) {
				printf(" Fives            |                 \n");
			}
			else {
				printf(" Fives            | %d                \n", score_card[i + 4]);
			}
			if (score_card_tracker[i + 5] == 0) {
				printf(" Sixes            |                 \n");
			}
			else {
				printf(" Sixes            | %d                \n", score_card[i + 5]);
			}
			printf("__________________|____________________\n");
			printf(" TOTAL            | %d            \n", score_card[TOTAL_INDEX]);
			printf("__________________|____________________\n");
			printf(" BONUS            | %d            \n", score_card[BONUS_INDEX]);
			printf("__________________|____________________\n");
			printf(" UPPER TOTAL      | %d            \n", score_card[UPPER_TOTAL_INDEX]);
			printf("__________________|____________________\n");
			printf(" LOWER SECTION    | SCORES            \n");
			printf("__________________|____________________\n");
			if (score_card_tracker[i + 6] == 0) {
				printf(" 3 of a kind      |                 \n");
			}
			else {
				printf(" 3 of a kind      | %d                \n", score_card[i + 6]);
			}
			if (score_card_tracker[i + 7] == 0) {
				printf(" 4 of a kind      |                 \n");
			}
			else {
				printf(" 4 of a kind      | %d                \n", score_card[i + 7]);
			}
			if (score_card_tracker[i + 8] == 0) {
				printf(" Full House       |                 \n");
			}
			else {
				printf(" Full House       | %d                \n", score_card[i + 8]);
			}
			if (score_card_tracker[i + 9] == 0) {
				printf(" Small Straight   |                 \n");
			}
			else {
				printf(" Small Straight   | %d                \n", score_card[i + 9]);
			}
			if (score_card_tracker[i + 10] == 0) {
				printf(" Large Straight   |                 \n");
			}
			else {
				printf(" Large Straight   | %d                \n", score_card[i + 10]);
			}
			if (score_card_tracker[i + 11] == 0) {
				printf(" Yahtzee          |                 \n");
			}
			else {
				printf(" Yahtzee          | %d                \n", score_card[i + 11]);
			}
			if (score_card_tracker[i + 12] == 0) {
				printf(" Chance           |                 \n");
			}
			else {
				printf(" Chance           | %d                \n", score_card[i + 12]);
			}
			printf("__________________|____________________\n");
			printf(" LOWER TOTAL      | %d            \n", score_card[LOWER_TOTAL_INDEX]);
			printf("__________________|____________________\n");
			printf(" COMBINE TOTAL    | %d            \n", score_card[COMBINE_TOTAL_INDEX]);
			printf("__________________|____________________\n");
		
	}

	int get_reroll_die_amt(void)
	{
		int reroll_die_amt = 0;
		printf("How many die do you want to roll again[1-5]? ");
		scanf("%d", &reroll_die_amt);
		while (reroll_die_amt < 1 || reroll_die_amt > 5) {
			printf("Sorry, the number that you put is invalid.\n");
			printf("How many die do you want to roll again[1-5]? ");
			scanf("%d", &reroll_die_amt);
		}
		return reroll_die_amt;
	}

	void get_reroll_die(int reroll_die[], int reroll_die_amt)
	{
		int die = 0, check = 1;

		for (int i = 0; i < reroll_die_amt; ++i) {
			do {
				check = 1;
				printf("Enter die number %d that you want to roll again: ", i + 1);
				scanf("%d", &die);
				if (die > 0 && die <= DIE_SIZE) {
					if (i > 0) {
						for (int j = 0; j < i; ++j) {
							if (die == reroll_die[j]) {
								printf("This die has been selected!\n");
								check = 0;
							}
						}
						if (check == 1) {
							reroll_die[i] = die;
							check = 1;
						}
					}
					else {
						reroll_die[i] = die;
						check = 1;
					}
				}
				else {
					printf("%d is a invalid die number\n", die);
					check = 0;
				}
				
			} while (check != 1);
		}
		system("cls");
	}

	void reroll_die(int reroll_die_amt, int reroll_die_arr[], int die[])
	{
		for (int i = 0; i < reroll_die_amt; ++i) {
			die[reroll_die_arr[i] - 1] = rand() % 6 + 1;
		}
	}

	void determine_winner(int p1_score_card[], int p2_score_card[])
	{
		if (p1_score_card[COMBINE_TOTAL_INDEX] == p2_score_card[COMBINE_TOTAL_INDEX]) {
			printf("Player 1 ties Player 2\n");
		}
		else if (p1_score_card[COMBINE_TOTAL_INDEX] >= p2_score_card[COMBINE_TOTAL_INDEX]) {
			printf("Player 1 is the winner!\n");
		}
		else {
			printf("Player 2 is the winner!\n");
		}
	}