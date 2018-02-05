/* cardtest2.c - adventurer
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "adventurer"

void assertTrue(bool val)
{
	if(val)
	{
		printf("TEST PASSED!\n\n");
	}
	else
	{
		printf("TEST FAILED!\n\n");
	}
}

int main() {
    int newCards = 2;
	int discarded = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 4336;
    int numPlayers = 2;
    int thisPlayer = 0;
	int drawnCard1, drawnCard2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 1: correct number of cards in hand--------------
	printf("Testing for correct number of cards in hand:\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	// ----------- TEST 2: drawn cards are treasure cards--------------
	printf("Testing if drawn cards are treasure cards:\n");
	drawnCard1 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1];
	drawnCard2 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2];
	assertTrue((drawnCard1 == copper || drawnCard1 == silver || drawnCard1 == gold) &&
				(drawnCard2 == copper || drawnCard2 == silver || drawnCard2 == gold));

	// ----------- TEST 3: correct number of cards in deck and discard pile--------------
	printf("Testing for correct number of cards in players deck and discard pile:\n");
	printf("deck + discard count = %d, expected = %d\n", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards + discarded);
	assertTrue(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards + discarded);

	// ----------- TEST 4: verify that no changes occured to supply piles --------------
	printf("Testing for changes to supply cards:\n");
	assertTrue(memcmp(testG.supplyCount, G.supplyCount, treasure_map + 1) == 0);

	printf(">>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);

	return 0;
}