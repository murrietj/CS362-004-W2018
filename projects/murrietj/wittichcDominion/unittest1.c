/* -----------------------------------------------------------------------
 * Test for gainCard()
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int oldDeckCount, oldDiscardCount, oldSupplyCount;
    int testSupplyPos = baron;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING gainCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
#if (NOISY_TEST == 1)
            printf("Test player %d with %d card(s).\n", p, handCount);
#endif
            memset(&G, 23, sizeof(struct gameState));            // clear the game state
            r = initializeGame(numPlayer, k, seed, &G);          // initialize a new game
            G.handCount[p] = handCount;                          // set the number of cards on hand

            oldDiscardCount = G.discardCount[p];
            oldSupplyCount = G.supplyCount[testSupplyPos];
            gainCard(testSupplyPos, &G, 0, p);  // gain card to discard pile
#if (NOISY_TEST == 1)
            printf("G.discardCount[%d] = %d, expected = %d\n", p, G.discardCount[p], oldDiscardCount + 1);
#endif
            assert(G.discardCount[p] == oldDiscardCount + 1); // check if the number of cards is correct
            assert(G.discard[p][G.discardCount[p] - 1] == testSupplyPos); // check if the card gained is correct
            assert(G.supplyCount[testSupplyPos] == oldSupplyCount - 1); // check if card was removed from supply

            oldDeckCount = G.deckCount[p];
            oldSupplyCount = G.supplyCount[testSupplyPos];
            gainCard(testSupplyPos, &G, 1, p);  // gain card to deck
#if (NOISY_TEST == 1)
            printf("G.deckCount[%d] = %d, expected = %d\n", p, G.deckCount[p], oldDeckCount + 1);
#endif
            assert(G.deckCount[p] == oldDeckCount + 1); // check if the number of cards is correct
            assert(G.deck[p][G.deckCount[p] - 1] == testSupplyPos); // check if the card gained is correct
            assert(G.supplyCount[testSupplyPos] == oldSupplyCount - 1); // check if card was removed from supply

            oldSupplyCount = G.supplyCount[testSupplyPos];
            gainCard(testSupplyPos, &G, 2, p);  // gain card to hand
#if (NOISY_TEST == 1)
            printf("G.handCount[%d] = %d, expected = %d\n", p, G.handCount[p], handCount + 1);
#endif
            assert(G.handCount[p] == handCount + 1); // check if the number of cards is correct
            assert(G.hand[p][G.handCount[p] - 1] == testSupplyPos); // check if the card gained is correct
            assert(G.supplyCount[testSupplyPos] == oldSupplyCount - 1); // check if card was removed from supply
        }
    }

    // test for card not originally in supply
    assert(gainCard(ambassador, &G, 1, 0) == -1);

    // test card originally in supply but all drawn out
    G.supplyCount[testSupplyPos] = 0;
    assert(gainCard(testSupplyPos, &G, 1, 0) == -1);

    printf("All tests passed!\n");

    return 0;
}