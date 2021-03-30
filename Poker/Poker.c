/*
Programmer: Thunradee Tangsupakij and Deitel & Deitel - C How to Program
Class: CptS 121
Programming Assignment 7: Poker (5-Card Draw)
Description: This program allows the user to play 5-Card Draw Poker against computer player
*/

#include "Poker.h"

/* print the welcome message */
void print_welcome(void)
{
	printf("***** WELCOME TO POKER (5-CARD DRAW) *****\n\n");
}

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}

	printf("The desk is successfully shuffled!\n");
	printf("Press any key to start the game\n");
	system("pause");
	system("cls");
}

/* deal cards in deck */
void deal(const int wDeck[][13], int *deck_index, const char *wFace[], const char *wSuit[], Card cards[], int cards_num)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int index = 0;

	/* deal cards depend on the number cards_num */
	for (card = *deck_index; card <= *deck_index + cards_num - 1; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					cards[index].face_index = column;
					cards[index].suit_index = row;
					/*printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');*/
				}
			}
		}
		++index;
	}
	/* update the deck index */
	*deck_index += cards_num;
}

/* display cards on the player's hand */
void display_cards(const char *wFace[], const char *wSuit[], Card cards[], char *title)
{
	printf("%s's Cards\n", title);
	for (int i = 0; i < CARDS_NUM; ++i) {
		printf("Card%d: %5s of %-8s\n", i, wFace[cards[i].face_index], wSuit[cards[i].suit_index]);
	}
}

/* sort the card on the hand */
void sort_cards(Card cards[])
{
	Card temp;
	for (int i = 0; i < CARDS_NUM; ++i) {
		for (int j = 0; j < CARDS_NUM - i - 1; ++j) {
			if (cards[j].face_index > cards[j + 1].face_index) {
				temp = cards[j];
				cards[j] = cards[j + 1];
				cards[j + 1] = temp;
			}
		}
	}
}

/* determine if the hand contains one pair */
int is_one_pair(Card cards[])
{
	int one_pair = 0, index1 = 0, index2 = 0, j = 0;
	Card temp[CARDS_NUM], temp_val;
	sort_cards(cards);
	for (int i = 0; i < CARDS_NUM - 1; ++i) {
		if (cards[i].face_index == cards[i + 1].face_index) {
			index1 = i;
			index2 = i + 1;
			one_pair = 1;
			break;
		}
	}

	// if the hand contains one pair, move the pair to the most right
	if (one_pair) {
		for (int i = 0; i < 3; ++i) {
			while (j < CARDS_NUM) {
				if (j != index1 && j != index2) {
					temp[i] = cards[j];
					++j;
					break;
				}
				++j;
			}
		}
		temp[3] = cards[index1];
		temp[4] = cards[index2];
		//if the hands contain ace, move ace to be next to the pair
		if (temp[0].face_index == 0) {
			temp_val = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp_val;
		}
		// copy temp array to cards array
		for (int i = 0; i < CARDS_NUM; ++i) {
			cards[i] = temp[i];
		}
	}
	
	return one_pair;
}

/* determine if the hand contains two pairs */
int is_two_pairs(Card cards[])
{
	int two_pairs = 0, st_pair = 0, nd_pair = 0;
	int index1 = 0, index2 = 0, index3 = 0, index4 = 0;
	Card temp[CARDS_NUM];

	sort_cards(cards);
	for (int i = 0; i < CARDS_NUM - 1; ++i) {
		if (st_pair == 0) {
			if (cards[i].face_index == cards[i + 1].face_index) {
				st_pair = 1;
				index1 = i;
				index2 = i + 1;
				i += 1;
			}
		}
		else {
			if (cards[i].face_index == cards[i + 1].face_index) {
				nd_pair = 1;
				index3 = i;
				index4 = i + 1;
			}
		}
	}

	two_pairs = st_pair && nd_pair;
	/* if the hand contains two pairs, move two pair to the most right */
	if (two_pairs) {
		for (int i = 0; i < CARDS_NUM; ++i) {
			if (i != index1 && i != index2 && i != index3 && i != index4) {
				temp[0] = cards[i];
				break;
			}
		}
		// if the hand has pair ace, move the pair the the most right, followed by another pair
		if (cards[index1].face_index == 0) {
			temp[1] = cards[index3];
			temp[2] = cards[index4];
			temp[3] = cards[index1];
			temp[4] = cards[index2];
		}
		else {
			temp[1] = cards[index1];
			temp[2] = cards[index2];
			temp[3] = cards[index3];
			temp[4] = cards[index4];
		}
		// copy temp array to cards array
		for (int i = 0; i < CARDS_NUM; ++i) {
			cards[i] = temp[i];
		}
	}
	return two_pairs;
}

/* determine does the hand contains three of a kind */
int is_three_of_a_kind(Card cards[])
{
	int three_of_a_kind = 0, i = 0, k = 0;
	Card temp[CARDS_NUM];

	sort_cards(cards);
	for (; i < CARDS_NUM - 2; ++i) {
		if ((cards[i].face_index == cards[i + 1].face_index) && (cards[i + 1].face_index == cards[i + 2].face_index)) {
			three_of_a_kind = 1;
			break;
		}
	}

	/* if the hand contains three of a kind, move them to the most right */
	if (three_of_a_kind) {
		for (int j = 0; j < 2; ++j) {
			while (k < CARDS_NUM) {
				if (k != i && k != (i + 1) && k != (i + 2)) {
					temp[j] = cards[k];
					++k;
					break;
				}
				++k;
			}
		}
		temp[2] = cards[i];
		temp[3] = cards[i + 1];
		temp[4] = cards[i + 2];
		// copy temp array to cards array
		for (int j = 0; j < CARDS_NUM; ++j) {
			cards[j] = temp[j];
		}
	}

	return three_of_a_kind;
}

/* determine does the hand contains a straight */
int is_straight(Card cards[])
{
	int straight = 0, count = 0;
	Card temp;
	sort_cards(cards);
	// if the hand have ace and king
	if (cards[0].face_index == 0 && cards[4].face_index == 12) {
		count = 1;
		for (int i = 1; i < CARDS_NUM - 1; ++i) {
			if (cards[i].face_index == cards[i + 1].face_index - 1) {
				++count;
			}
		}
		// if it a royal straight
		if (count == 4) {
			straight = 1;
			// arrange cards, move ace to the most right
			temp = cards[0];
			for (int i = 1; i < CARDS_NUM; ++i) {
				cards[i - 1] = cards[i];
			}
			cards[4] = temp;
		}
	}
	else {
		for (int i = 0; i < CARDS_NUM - 1; ++i) {
			if (cards[i].face_index == cards[i + 1].face_index - 1) {
				++count;
			}
		}
		// if it's a normal straight, the cards is already in order
		if (count == 4) {
			straight = 1;
		}
	}
	
	return straight;
}

/* determine does the hand contains a flush */
int is_flush(Card cards[])
{
	Card temp;
	sort_cards(cards);
	int flush = 0, suit = cards[0].suit_index, count = 0;
	for (int i = 1; i < CARDS_NUM; ++i) {
		if (cards[i].suit_index == suit) {
			++count;
		}
	}
	
	if (count == 4) {
		flush = 1;
		/* if the hand contains a flush and has ace, move the ace to the most right*/
		if (cards[0].face_index == 0) {
			temp = cards[0];
			for (int i = 1; i < CARDS_NUM; ++i) {
				cards[i - 1] = cards[i];
			}
			cards[4] = temp;
		}
	}
	return flush;
}

/* determine does the hand contains a full house */
int is_full_house(Card cards[])
{
	int full_house = 0, i = 0;
	Card temp[CARDS_NUM];
	sort_cards(cards);
	// one pair and three of a kind
	if ((cards[i].face_index == cards[i + 1].face_index) && ((cards[i + 2].face_index == cards[i + 3].face_index) &&
		(cards[i + 3].face_index == cards[i + 4].face_index))) {
		full_house = 1;
	}
	// three of a kind and one pair
	else if (((cards[i].face_index == cards[i + 1].face_index) && (cards[i + 1].face_index == cards[i + 2].face_index)) &&
		(cards[i + 3].face_index == cards[i + 4].face_index)) {
		full_house = 1;
		// switch the position of three of a kind and one pair 
		temp[0] = cards[i + 3];
		temp[1] = cards[i + 4];
		temp[2] = cards[i];
		temp[3] = cards[i + 1];
		temp[4] = cards[i + 2];

		// copy temp array to cards array
		for (int j = 0; j < CARDS_NUM; ++j) {
			cards[j] = temp[j];
		}
	}
	return full_house;
}

/* determine does the hand contains four of a kind */
int is_four_of_a_kind(Card cards[])
{
	int four_of_a_kind = 0, i = 0;
	Card temp;
	sort_cards(cards);
	for (; i < CARDS_NUM - 3; ++i) {
		if ((cards[i].face_index == cards[i + 1].face_index) && (cards[i + 1].face_index == cards[i + 2].face_index)
			&& (cards[i + 2].face_index == cards[i + 3].face_index)) {
			four_of_a_kind = 1;
			break;
		}
	}
	// if the hand contains four of a kind and its position is on the left, swich it to the right
	if (four_of_a_kind && i == 0) {
		temp = cards[4];
		for (int j = 3; j >= 0; --j) {
			cards[j + 1] = cards[j];
		}
		cards[0] = temp;
	}

	return four_of_a_kind;
}

/* determine does the hand contains straight flush */
int is_straight_flush(Card cards[])
{
	int straight_flush = 0, straight = 0, flush = 0;
	straight = is_straight(cards);
	flush = is_flush(cards);
	straight_flush = straight && flush;
	/*if the hand contains a straight_flush and ace, sort the cards because is_flush move ace to the most right*/
	if (straight_flush && cards[4].face_index == 0) {
		sort_cards(cards);
	}
	return straight_flush;
}

/* determine does the hand contains royal flush */
int is_royal_flush(Card cards[])
{
	int royal_flush = 0, straight = 0, flush = 0, royal = 0;
	straight = is_straight(cards); 
	flush = is_flush(cards); // if the hand contains a flush and ace, the ace is moved to the most right
	if (cards[0].face_index == 9 && cards[4].face_index == 0) {
		royal = 1;
	}
	royal_flush = straight && flush && royal;

	return royal_flush;
}

/* evaluate the hand what does it contain and return the result */
int evaluate_hand(Card cards[])
{ 
	Card temp;
	
	if (is_royal_flush(cards)) {
		return ROYAL_FLUSH;
	}
	else if (is_straight_flush(cards)) {
		return STRAIGHT_FLUSH;
	}
	else if (is_four_of_a_kind(cards)) {

		return FOUR_OF_A_KIND;
	}
	else if (is_full_house(cards)) {
		return FULL_HOUSE;
	}
	else if (is_flush(cards)) {
		return FLUSH;
	}
	else if (is_straight(cards)) {
		return STRAIGHT;
	}
	else if (is_three_of_a_kind(cards)) {
		return THREE_OF_A_KIND;
	}
	else if (is_two_pairs(cards)) {
		return TWO_PAIRS;
	}
	else if (is_one_pair(cards)) {
		return ONE_PAIR;
	}
	else {
		// if the hand contain an ace, move it the most right
		if (cards[0].face_index == 0) {
			temp = cards[0];
			for (int i = 1; i < CARDS_NUM; ++i) {
				cards[i - 1] = cards[i];
			}
			cards[4] = temp;
		}
		return NO_PAIR;
	}
}

/* determine the player's hand or the dealer's hand is better and return the result */
int determine_the_better_hand(Card player_cards[], Card dealer_cards[], int *player_hand, int *dealer_hand)
{
	int better_hand = 0;

	*player_hand = evaluate_hand(player_cards);
	*dealer_hand = evaluate_hand(dealer_cards);

	if (*player_hand > *dealer_hand) {
		better_hand = 1; // player
		return better_hand;
	}
	else if (*dealer_hand > *player_hand) {
		better_hand = -1; // dealer
		return better_hand;
	}
	/* player_hand == dealer_hand */
	else {
		for (int i = 4; i >= 0; --i) {
			// in case that ace is ace not one
			if (i != 0) {
				if (player_cards[i].face_index == 0 && dealer_cards[i].face_index != 0) {
					better_hand = 1; // player
					return better_hand;
				}
				else if (player_cards[i].face_index != 0 && dealer_cards[i].face_index == 0) {
					better_hand = -1; // dealer
					return better_hand;
				}
			}
			// in case that two pairs are equal and one or both hands have ace as a kicker
			if (*player_hand == 2 && i == 0) {
				if (player_cards[i].face_index == 0 && dealer_cards[i].face_index != 0) {
					better_hand = 1; // player
					return better_hand;
				}
				else if (player_cards[i].face_index != 0 && dealer_cards[i].face_index == 0) {
					better_hand = -1; // dealer
					return better_hand;
				}
			}
			if (player_cards[i].face_index > dealer_cards[i].face_index) {
				better_hand = 1; // player
				return better_hand;
			}
			else if (dealer_cards[i].face_index > player_cards[i].face_index) {
				better_hand = -1; // dealer
				return better_hand;
			}
		}
		// tie
		better_hand = 0;
		return better_hand;
	}
}

/* sort integer array */
void sort_int(int arr[], int arr_num)
{
	int temp;
	for (int i = 0; i < arr_num; ++i) {
		for (int j = 0; j < arr_num - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/* prompt the player how many cards and which card she/he wants to replace */
void prompt_cards_replacement(int replaced_cards[], int *replaced_cards_num)
{
	printf("How many cards do you want to replace? (0 - %d): ", REPLACED_CARDS_NUM);
	scanf("%d", replaced_cards_num);

	while(*replaced_cards_num < 0 || *replaced_cards_num > REPLACED_CARDS_NUM) {
		printf("The number of cards is out of length.\n");
		printf("How many cards do you want to replace? (0 - %d): ", REPLACED_CARDS_NUM);
		scanf("%d", replaced_cards_num);
	}

	if (*replaced_cards_num != 0) {
		for (int i = 0; i < *replaced_cards_num; ++i) {
			printf("Enter the number of card %d: ", i + 1);
			scanf("%d", (replaced_cards + i));
		}
		sort_int(replaced_cards, *replaced_cards_num);
	}
}

/* replace the old card on the player's hand with the new one from the deck */
void replace_cards(const int wDeck[][13], int *deck_index, const char *wFace[], const char *wSuit[], Card cards[], int replaced_cards_num, int replaced_cards[])
{
	Card temp[REPLACED_CARDS_NUM];
	deal(wDeck, deck_index, wFace, wSuit, temp, replaced_cards_num);

	for (int i = 0; i < replaced_cards_num; ++i) {
		cards[replaced_cards[i]] = temp[i];
	}
	
}

/* determine how many cards and which card on the dealer's hand need to be replaced */
void determine_card_replacement(int contain, int replaced_cards[], int *replaced_cards_num)
{
	if (contain == NO_PAIR || contain == ONE_PAIR) {
		*replaced_cards_num = REPLACED_CARDS_NUM;
		for (int i = 0; i < *replaced_cards_num; ++i) {
			replaced_cards[i] = i;
		}
	}
	else if (contain == TWO_PAIRS || contain == FOUR_OF_A_KIND) {
		*replaced_cards_num = 1;
		replaced_cards[0] = 0;
	}
	else if (contain == THREE_OF_A_KIND) {
		*replaced_cards_num = 2;
		replaced_cards[0] = 0;
		replaced_cards[1] = 1;
	}
	else {
		*replaced_cards_num = 0;
	}
}

/* print the message tell the players what is their hand contain */
void print_hand_contain(int hand_contain, char *title)
{
	char contain[1][20];
	switch (hand_contain) {
	case NO_PAIR: 
		strcpy(contain, "no pair");
		break;
	case ONE_PAIR:
		strcpy(contain, "one pair");
		break;
	case TWO_PAIRS:
		strcpy(contain, "two pairs");
		break;
	case THREE_OF_A_KIND:
		strcpy(contain, "three of a kind");
		break;
	case STRAIGHT:
		strcpy(contain, "straight");
		break;
	case FLUSH:
		strcpy(contain, "flush");
		break;
	case FULL_HOUSE:
		strcpy(contain, "full house");
		break;
	case FOUR_OF_A_KIND:
		strcpy(contain, "four of a kind");
		break;
	case STRAIGHT_FLUSH:
		strcpy(contain, "straight flush");
		break;
	case ROYAL_FLUSH:
		strcpy(contain, "royal flush");
		break;
	}
	printf("%s's hand contains %s\n\n", title, contain);
}

/* print the winner of each round */
void print_winner(int winner)
{
	if (winner == PLAYER_WINS) {
		printf("Player is the winner!\n");
	}
	else if (winner == DEALER_WINS) {
		printf("Dealer is the winner!\n");
	}
	else {
		printf("Player and dealer tie!\n");
	}
	system("pause");
	system("cls");
}