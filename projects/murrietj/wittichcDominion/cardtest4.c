/* cardtest1.c - council_room
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <stdbool.h>

#define TESTCARD "council room"

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
    int newCards = 4;
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
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	for(thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++)
	{
		if(thisPlayer > 0){ newCards = 1; discarded = 0; }

		// ----------- TEST 1: correct number of cards in hand--------------
		printf("Testing player %d for correct number of cards in hand:\n", thisPlayer);
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

		// ----------- TEST 2: correct number of cards in deck --------------
		printf("Testing player %d for correct number of cards in players deck:\n", thisPlayer);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
		assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

		if(thisPlayer == 0)
		{
			// ----------- TEST 3: correct number of buys --------------
			printf("Testing player %d for correct number of buys:\n", thisPlayer);
			printf("numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
			assertTrue(testG.numBuys == G.numBuys + 1);
		}

	}

	// ----------- TEST 4: verify that no changes occured to supply piles --------------
	printf("Testing for changes to supply cards:\n");
	assertTrue(memcmp(testG.supplyCount, G.supplyCount, treasure_map + 1) == 0);

	printf(">>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);

	return 0;
}