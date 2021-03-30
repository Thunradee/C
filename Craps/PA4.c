// function definitions file
// includes the header file
#include "PA4.h"

void print_menu(void)
{
	printf("MENU:\n");
	printf("1. Display the rules.\n");
	printf("2. Start the game.\n");
	printf("3. Exit.\n");
}

int get_menu_option(void) {
	int option = 0;
	printf("Select the menu [1 to 3]: ");
	scanf("%d", &option);
	// check the validity
	while (option < 1 || option > 3) {
		printf("Your option is not valid. Please choose a new one! [1 to 3]: ");
		scanf("%d", &option);
	}
	
	return option;
}

void print_game_rules(void)
{
	printf("Rules of Craps:\n");
	printf("1. A player rolls two dice.\n");
	printf("2. If the sum is 7 or 11 on the first throw, the player wins.\n");
	printf("3. If the sum is 2, 3, or 12 on the first throw (called \"craps\"), the player loses.\n");
	printf("4. If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's point.\n");
	printf("5. To win, you must continue rolling the dice until you make your point.\n");
	printf("6. The player loses by rolling a 7 before making the point.\n");
}

double get_bank_balance(void)
{
	double balance = 0.0;
	printf("Enter your initial bank balance: $");
	scanf("%lf", &balance);
	return balance;
}

double get_wager_amount(void)
{
	double wager = 0.0;
	printf("How much do you want to bet?: $");
	scanf("%lf", &wager);

	// check the validity
	while (wager <= 0.0) {
		printf("The wager can't be a negative amount or zero! Please enter a new amount: $");
		scanf("%lf", &wager);
	}
	
	return wager;
	
}

int check_wager_amount(double wager, double balance)
{
	if (wager > balance) {
		return 0;
	}
	else {
		return 1;
	}
}

int get_wager_option(void)
{
	int option = 0;
	printf("Sorry, you don't have enough money (T^T).\n");
	printf("If you want to add more money to your account, press 1.\n");
	printf("If you want to change the wager, press 2.\n");
	scanf("%d", &option);
	
	// check the valid
	while (option < 1 || option > 2) {
		printf("Your option is not valid. Please choose a new one! [1 or 2]: ");
		scanf("%d", &option);
	}
	
	return option;
}

int roll_die(void)
{
	int die_value = 0;
	die_value = rand() % 6 + 1;
	return die_value;
}

int calculate_sum_dice(int die1_value, int die2_value)
{
	int sum = 0;
	sum = die1_value + die2_value;
	return sum;
}

int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice == 7 || sum_dice == 11) {
		return 1; // the player wins
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12) {
		return 0; // craps! the player loses
	}
	else {
		return -1; // the sum becomes the player's "point"
	}
}

int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == point_value)
	{
		return 1;
	}
	else if (sum_dice == 7)
	{
		return 0;
	}
	else {
		return -1;
	}
}

double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	if (add_or_subtract == 1) {
		bank_balance += wager_amount;
	}
	if (add_or_subtract == 0) {
		bank_balance -= wager_amount;
	}
	
	return bank_balance;
}

void show_bank_balance(double bank_balance)
{
	printf("You account have $%.2lf\n", bank_balance);
}


void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{
	if (win_loss_neither == 1) {
		printf("You're up big, now's the time to cash in your chips!\n");

	}
	if (win_loss_neither == 0) {
		printf("Sorry, you busted!\n");

		if (current_bank_balance <= (1 / 4 * initial_bank_balance)) {
			printf("Oh, you're going for broke, huh?\n");
		}
		else {
			printf("Aw cmon, take a chance!\n");
		}
	}
}

int is_continue_play(void)
{
	int answer = '\0';
	printf("Do you want to continue playing? [Press 1 for yes/0 for no]: ");
	scanf("%d", &answer);
	return answer;
}