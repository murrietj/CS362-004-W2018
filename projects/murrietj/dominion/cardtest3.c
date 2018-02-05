/* cardtest1.c - village
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "village"

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
    int newCards = 1;
	int discarded = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 1: correct number of cards in hand--------------
	printf("Testing for correct number of cards in hand:\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	// ----------- TEST 2: correct number of cards in deck --------------
	printf("Testing for correct number of cards in players deck:\n");
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

	// ----------- TEST 3: correct number of actions --------------
	printf("Testing for correct number of actions:\n");
	printf("numActions = %d, expected = %d\n", testG.numActions, G.numActions + 2);
	assertTrue(testG.numActions == G.numActions + 2);

	// ----------- TEST 4: verify that no changes occured to supply piles --------------
	printf("Testing for changes to supply cards:\n");
	assertTrue(memcmp(testG.supplyCount, G.supplyCount, treasure_map + 1) == 0);

	printf(">>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);

	return 0;
}