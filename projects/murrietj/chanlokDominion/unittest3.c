/* -----------------------------------------------------------------------
 * Test for getCost()
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    printf("TESTING getCost():\n");

    // Test each existing card in our game
    assert(getCost(copper) == COPPER_COST);
    assert(getCost(silver) == SILVER_COST);
    assert(getCost(gold) == GOLD_COST);
    assert(getCost(estate) == ESTATE_COST);
    assert(getCost(duchy) == DUCHY_COST);
    assert(getCost(province) == PROVINCE_COST);
    assert(getCost(curse) == CURSE_COST);
    assert(getCost(adventurer) == ADVENTURER_COST);
    assert(getCost(council_room) == COUNCIL_ROOM_COST);
    assert(getCost(feast) == FEAST_COST);
    assert(getCost(gardens) == GARDEN_COST);
    assert(getCost(mine) == MINE_COST);
    assert(getCost(remodel) == REMODEL_COST);
    assert(getCost(smithy) == SMITHY_COST);
    assert(getCost(village) == VILLAGE_COST);
    assert(getCost(baron) == BARON_COST);
    assert(getCost(great_hall) == GREAT_HALL_COST);
    assert(getCost(minion) == MINION_COST);
    assert(getCost(steward) == STEWARD_COST);
    assert(getCost(tribute) == TRIBUTE_COST);
    assert(getCost(ambassador) == AMBASSADOR_COST);
    assert(getCost(cutpurse) == CUTPURSE_COST);
    assert(getCost(embargo) == EMBARGO_COST);
    assert(getCost(outpost) == OUTPOST_COST);
    assert(getCost(salvager) == SALVAGER_COST);
    assert(getCost(sea_hag) == SEA_HAG_COST);
    assert(getCost(treasure_map) == TREASURE_MAP_COST);

    // Test an integer (56) that doesn't represent an existing card in our game
    assert(getCost(56) == -1);

    printf("All tests passed!\n");
    return 0;
}