/*
Programmer: Thunradee Tangsupakij
Class: CptS 121, Fall 2018, section 1
Programming Assignment 4: A Game of Chance "Craps"
Date: 9/27/18
Description: This program implements a crap game.
*/
// include the header file
#include "PA4.h"

int main(void) {
	// declairs and initializes the variables
	int menu_option = 0, die1 = 0, die2 = 0, wager_valid = 0, wager_option = 0, sum_dice = 0, result = 0;
	int number_rolls = 0, point_value = 0, continue_play = 0;
	double bank_balance = 0.0, wager = 0.0, add_money = 0.0, initial_bank_balance = 0.0;
	

	
	do {
		// print the game menu
		print_menu();
		// promt the option from the users
		menu_option = get_menu_option();

		// 1. Display the rules
		if (menu_option == 1) {
			print_game_rules();
			
		}

		// 2. Start the game
		if (menu_option == 2) {
			// prompts the bank balance
			bank_balance = get_bank_balance();
			initial_bank_balance = bank_balance;

			do {
				// prompts the wager
				wager = get_wager_amount();
				// check the wager validity
				wager_valid = check_wager_amount(wager, bank_balance);
				// if the wager is not valid, user can add more money to account or change the wager
				while (wager_valid == 0) {
					wager_option = get_wager_option();
					// add more money to account
					if (wager_option == 1) {
						printf("How much do you want to add?: $");
						scanf("%lf", &add_money);
						while (add_money < 0) {
							printf("The money can't be a negative amount! Please enter a new amount: $");
							scanf("%lf", &add_money);
						}
						bank_balance = adjust_bank_balance(bank_balance, add_money, 1);
						show_bank_balance(bank_balance);
					}
					// change the wager
					else {
						wager = get_wager_amount();
					}
					// check the wager validity
					wager_valid = check_wager_amount(wager, bank_balance);
				}

				// roll the dice
				srand((unsigned int)time(NULL));
				die1 = roll_die();
				die2 = roll_die();
				// print the result of rolling the dice
				printf("Die1: %d\n", die1);
				printf("Die2: %d\n", die2);
				// calculate sum dice
				sum_dice = calculate_sum_dice(die1, die2);
				// print the sum of rolling the dice
				printf("Sum dice: %d\n", sum_dice);
				// check if the player wins or loses at the first round
				result = is_win_loss_or_point(sum_dice);
				// if the player wins
				if (result == 1) {
					chatter_messages(number_rolls, result, initial_bank_balance, bank_balance);
					bank_balance = adjust_bank_balance(bank_balance, wager, 1);
					show_bank_balance(bank_balance);
				}
				// if the player loses
				else if (result == 0) {
					chatter_messages(number_rolls, result, initial_bank_balance, bank_balance);
					bank_balance = adjust_bank_balance(bank_balance, wager, 0);
					show_bank_balance(bank_balance);
				}
				// if on one win at the first round
				else {
					// sum of dice becomes the point_value
					point_value = sum_dice;

					// roll dice until someone win
					do {
						die1 = roll_die();
						die2 = roll_die();
						printf("Die1: %d\n", die1);
						printf("Die2: %d\n", die2);
						sum_dice = calculate_sum_dice(die1, die2);
						printf("Sum dice: %d\n", sum_dice);
						result = is_point_loss_or_neither(sum_dice, point_value);
					} while (result == -1);

					// if the play wins
					if (result == 1) {
						chatter_messages(number_rolls, result, initial_bank_balance, bank_balance);
						bank_balance = adjust_bank_balance(bank_balance, wager, 1);
						show_bank_balance(bank_balance);
					}
					// if the play loses
					else {
						chatter_messages(number_rolls, result, initial_bank_balance, bank_balance);
						bank_balance = adjust_bank_balance(bank_balance, wager, 0);
						show_bank_balance(bank_balance);
					}
				}
				// ask the player if he or she still wants to continue playing
				continue_play = is_continue_play();
			} while (continue_play == 1); // keep the game going 

		}

		// 3. Exit
		if (menu_option == 3) {
			printf("Good Bye!\n");
		}

	} while (menu_option != 3); // prompt the player for menu option until he or she wants to exit

	return 0;
}