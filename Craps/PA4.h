#include <stdio.h> // standard includes
#include <stdlib.h>
#include <time.h>

// function prototypes
void print_menu(void);
int get_menu_option(void);
void print_game_rules(void);
double get_bank_balance(void);
double get_wager_amount(void);
int check_wager_amount(double wager, double balance);
int get_wager_option(void);
int roll_die(void);
int calculate_sum_dice(int die1_value, int die2_value);
int is_win_loss_or_point(int sum_dice);
int is_point_loss_or_neither(int sum_dice, int point_value);
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);
void show_bank_balance(double bank_balance);
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);
int is_continue_play(void);