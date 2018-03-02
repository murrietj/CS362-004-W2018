/* randomtestadventurer.c - adventurer
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

#define TESTCARD "adventurer"

int assertTrue(bool val)
{
	if(val)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int checkAdventurer(struct gameState *G, int thisPlayer, int handPos) {
    int newCards = 2;
	int discarded = 1;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int drawnCard1, drawnCard2;
	struct gameState testG;

	// copy the game state to a test case
	memcpy(&testG, G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	// ----------- TEST 1: correct number of cards in hand--------------
	if (assertTrue(testG.handCount[thisPlayer] == G->handCount[thisPlayer] + newCards - discarded) == -1) {
		printf("TEST FAILED!\n");
		printf("Testing for correct number of cards in hand:\n");
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G->handCount[thisPlayer] + newCards - discarded);
		printf("Inputs:\n");
		printf("Number of players = %d\n", G->numPlayers);
		printf("Player = %d\n", thisPlayer);
		printf("Number of cards in hand = %d\n", G->handCount[thisPlayer]);
		printf("Hand Position = %d\n", handPos);
		printf("Number of cards in deck = %d\n", G->deckCount[thisPlayer]);
		printf("Number of cards in discard = %d\n\n", G->discardCount[thisPlayer]);
	}

	// ----------- TEST 2: drawn cards are treasure cards--------------
	drawnCard1 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1];
	drawnCard2 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2];
	if (assertTrue((drawnCard1 == copper || drawnCard1 == silver || drawnCard1 == gold) &&
				(drawnCard2 == copper || drawnCard2 == silver || drawnCard2 == gold)) == -1) {
		printf("TEST FAILED!\n");
		printf("Testing if drawn cards are treasure cards:\n");
		printf("Inputs:\n");
		printf("Number of players = %d\n", G->numPlayers);
		printf("Player = %d\n", thisPlayer);
		printf("Number of cards in hand = %d\n", G->handCount[thisPlayer]);
		printf("Hand Position = %d\n", handPos);
		printf("Number of cards in deck = %d\n", G->deckCount[thisPlayer]);
		printf("Number of cards in discard = %d\n\n", G->discardCount[thisPlayer]);
	}

	// ----------- TEST 3: correct number of cards in deck and discard pile--------------
	if (assertTrue(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G->deckCount[thisPlayer] + G->discardCount[thisPlayer] - newCards + discarded) == -1) {
		printf("TEST FAILED!\n");
		printf("Testing for correct number of cards in players deck and discard pile:\n");
		printf("deck + discard count = %d, expected = %d\n", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G->deckCount[thisPlayer] + G->discardCount[thisPlayer] - newCards + discarded);
		printf("Inputs:\n");
		printf("Number of players = %d\n", G->numPlayers);
		printf("Player = %d\n", thisPlayer);
		printf("Number of cards in hand = %d\n", G->handCount[thisPlayer]);
		printf("Hand Position = %d\n", handPos);
		printf("Number of cards in deck = %d\n", G->deckCount[thisPlayer]);
		printf("Number of cards in discard = %d\n\n", G->discardCount[thisPlayer]);
	}

	// ----------- TEST 4: verify that no changes occured to supply piles --------------
	if (assertTrue(memcmp(testG.supplyCount, G->supplyCount, treasure_map + 1) == 0) == -1) {
		printf("TEST FAILED!\n");
		printf("Testing for changes to supply cards:\n");
		printf("Inputs:\n");
		printf("Number of players = %d\n", G->numPlayers);
		printf("Player = %d\n", thisPlayer);
		printf("Number of cards in hand = %d\n", G->handCount[thisPlayer]);
		printf("Hand Position = %d\n", handPos);
		printf("Number of cards in deck = %d\n", G->deckCount[thisPlayer]);
		printf("Number of cards in discard = %d\n\n", G->discardCount[thisPlayer]);
	}

	return 0;
}

int main () {

	int i, n, p, numPlayers, seed, handPos;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("RANDOM TESTS.\n");

	srand(time(NULL));

	for (n = 0; n < 200; n++)
	{
		numPlayers = rand() % (MAX_PLAYERS + 1 - 2) + 2;
		seed = rand() % 1024 + 1;
		initializeGame(numPlayers, k, seed, &G);
		p = rand() % numPlayers;
		G.whoseTurn = p;

		// randomize player's deck
		G.deckCount[p] = floor(Random() * MAX_DECK);
		//for (i = 0; i < G.deckCount[p]; i++)
		//{
		//	G.deck[p][i] = k[(int)floor(Random() * 9)];
		//}

		// randomize player's discard
		G.discardCount[p] = floor(Random() * MAX_DECK);
		//for (i = 0; i < G.discardCount[p]; i++)
		//{
		//G.discard[p][i] = k[(int)floor(Random() * 9)];
		//}

		// randomize player's hand
		G.handCount[p] = floor(Random() * MAX_HAND);
		//for (i = 0; i < G.handCount[p]; i++)
		//{
		//	G.hand[p][i] = k[(int)floor(Random() * 9)];
		//}

		// make sure player has adventurer in hand
		handPos = rand() % G.handCount[p];
		G.hand[p][handPos] = adventurer;

		checkAdventurer(&G, p, handPos);
	}

	printf(">>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);

	return 0;
}