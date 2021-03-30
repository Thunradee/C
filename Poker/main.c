/*
Programmer: Thunradee Tangsupakij and Deitel & Deitel - C How to Program
Class: CptS 121
Programming Assignment 7: Poker (5-Card Draw)
Description: This program allows the user to play 5-Card Draw Poker against computer player
*/

#include "Poker.h"

int main(void)
{
	/* initialize suit array */
	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };

	/* initialize titles of players */
	char *player_title = "Player", *dealer_title = "Dealer";
	int round = 1;

	srand((unsigned)time(NULL)); /* seed random-number generator */

	print_welcome();
	while (round < 11) {
		/* initalize deck array and index*/
		int deck[4][13] = { 0 }, deck_index = 1;
		/* declare both players cards */
		Card player_cards[CARDS_NUM], dealer_cards[CARDS_NUM];
		int player_hand, dealer_hand, who_is_better = 0;
		int replaced_cards[REPLACED_CARDS_NUM] = { 0 }, replaced_cards_num = 0;
		
		printf("Round %d\n", round);
		shuffle(deck);
		/* deal cards to both players */
		deal(deck, &deck_index, face, suit, player_cards, CARDS_NUM);
		deal(deck, &deck_index, face, suit, dealer_cards, CARDS_NUM);
		printf("Dealer's cards are already dealt.\n");
		/* display player's card */
		display_cards(face, suit, player_cards, player_title);
		printf("\n");
		/* prompt the player for the cards that she/he wants to replace */
		prompt_cards_replacement(replaced_cards, &replaced_cards_num);
		if (replaced_cards_num != 0) {
			/* replace the old cards of the player with the new one from the deck */
			replace_cards(deck, &deck_index, face, suit, player_cards, replaced_cards_num, replaced_cards);
			printf("\n");
			/* display player's card */
			display_cards(face, suit, player_cards, player_title);
		}
		system("pause");
		system("cls");

		/* after the user done with his/her cards */
		/* evaluate the dealer's hand */
		dealer_hand = evaluate_hand(dealer_cards);
		/* display the dealer's card */
		display_cards(face, suit, dealer_cards, dealer_title);
		/* determine how many cards and which card should be replaced*/
		determine_card_replacement(dealer_hand, replaced_cards, &replaced_cards_num);
		/* if the card need to be replaced */
		if (replaced_cards_num != 0) {
			/* display how many cards and which card are replaced*/
			printf("\nDealer replaces %d cards.\n", replaced_cards_num);
			printf("Dealer replaces card number");
			for (int i = 0; i < replaced_cards_num - 1; ++i) {
				printf(" %d,", replaced_cards[i]);
			}
			printf(" %d\n\n", replaced_cards[replaced_cards_num - 1]);
			/* replace the old cards of the dealer with the new one from the deck */
			replace_cards(deck, &deck_index, face, suit, dealer_cards, replaced_cards_num, replaced_cards);
			/* display the dealer's card */
			display_cards(face, suit, dealer_cards, dealer_title);
		}
		/* if the cards don't need to be replaced print the message */
		else {
			printf("\nDealer doesn't replace any cards.\n");
		}
		system("pause");
		system("cls");
		/*determine whoes cards is better*/
		who_is_better = determine_the_better_hand(player_cards, dealer_cards, &player_hand, &dealer_hand);
		/* display the player's card */
		display_cards(face, suit, player_cards, player_title);
		/* print the message of what the player's hand contain */
		print_hand_contain(player_hand, player_title);
		/* display the dealer's card */
		display_cards(face, suit, dealer_cards, dealer_title);
		/* print the message of what the dealer's hand contain */
		print_hand_contain(dealer_hand, dealer_title);
		/* print the winner */
		print_winner(who_is_better);
		++round;
	}

	return 0;
}