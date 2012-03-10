#if defined l4d2util_constants_inc_
    #endinput
#endif
#define l4d2util_constants_inc_

enum L4D2_Team {
    L4D2Team_Spectator = 1,
    L4D2Team_Survivors,
    L4D2Team_Infected
};

enum L4D2_Infected {
    L4D2Infected_Smoker = 1,
    L4D2Infected_Boomer,
    L4D2Infected_Hunter,
    L4D2Infected_Spitter,
    L4D2Infected_Jockey,
    L4D2Infected_Charger,
    L4D2Infected_Witch,
    L4D2Infected_Tank
};

enum L4D2_Survivors {
    L4D2Survivor_Coach,
    L4D2Survivor_Ellis,
    L4D2Survivor_Nick,
    L4D2Survivor_Rochelle,
    L4D1Survivor_Francis,
    L4D1Survivor_Louis,
    L4D1Survivor_Bill,
    L4D1Survivor_Zoey,
};

new const:String[L4D2_Team][] = {
    "Spectator",
    "Survivors",
    "Infected"
};

new const:String[L4D2_Infected][] = {
    "Smoker",
    "Boomer",
    "Hunter",
    "Spitter",
    "Jockey",
    "Charger",
    "Witch",
    "Tank"
};

new const:String[L4D2_Survivors][] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};
