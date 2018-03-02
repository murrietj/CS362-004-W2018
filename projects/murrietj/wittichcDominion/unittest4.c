/* -----------------------------------------------------------------------
 * Test for supplyCount()
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
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
    int i, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING supplyCount():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // Test for all cards in our game
    for(i = 0; i < 10; i++)
    {
#if (NOISY_TEST == 1)
        printf("supplyCount(%d, &G) = %d, expected = %d\n", k[i], supplyCount(k[i], &G), G.supplyCount[k[i]]);
#endif
        assert(supplyCount(k[i], &G) == G.supplyCount[k[i]]);
    }

    // Test for card not in our game
#if (NOISY_TEST == 1)
    printf("supplyCount(%d, &G) = %d, expected = %d\n", ambassador, supplyCount(ambassador, &G), G.supplyCount[ambassador]);
#endif
    assert(supplyCount(ambassador, &G) == G.supplyCount[ambassador]);

    printf("All tests passed!\n");

    return 0;
}