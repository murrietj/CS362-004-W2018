/* -----------------------------------------------------------------------
 * Test for discardCard()
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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
    int p, r, handCount, handPos;
    int oldCard, oldPlayedCardCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING discardCard():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (handPos = 0; handPos < handCount; handPos++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d card(s).\n", p, handCount);
#endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand

                oldCard = G.hand[p][handPos];
                oldPlayedCardCount = G.playedCardCount;
                discardCard(handPos, p, &G, 0); // discard card
#if (NOISY_TEST == 1)
                printf("G.handCount[%d] = %d, expected = %d\n", p, G.handCount[p], handCount - 1);
                printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, oldPlayedCardCount + 1);
#endif
                assert(G.handCount[p] == handCount - 1);             // check if number of cards in hand is correct
                assert(G.playedCardCount == oldPlayedCardCount + 1);   //check if number of cards in played cards is correct
                assert(G.playedCards[G.playedCardCount - 1] == oldCard); // check if card added to played cards
            }
        }
    }

    // test trashed card
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    p = 0;
    handCount = 4;
    handPos = 3;
    G.handCount[p] = handCount;                 // set the number of cards on hand
    oldCard = G.hand[p][handCount];
    oldPlayedCardCount = G.playedCardCount;
    discardCard(handPos, p, &G, 1); // discard card
#if (NOISY_TEST == 1)
    printf("Test player %d with %d card(s); Trashed card.\n", p, handCount);
    printf("G.handCount[%d] = %d, expected = %d\n", p, G.handCount[p], handCount - 1);
    printf("G.playedCardCount = %d, expected = %d\n", G.playedCardCount, oldPlayedCardCount);
#endif
    assert(G.handCount[p] == handCount - 1); // check if number of cards in hand is correct
    assert(G.playedCardCount == oldPlayedCardCount); //check if number of cards in played cards pile is correct

    printf("All tests passed!\n");

    return 0;
}