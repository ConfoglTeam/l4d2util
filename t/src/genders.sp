#pragma semicolon 1

#define L4D2UTIL_STOCKS_ONLY

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

#include "src/test_stocks.inc"

public OnStartTests() {
    new iSurvivor;

    decl String:testName[128];
    decl String:name[MAX_NAME_LENGTH];
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsSurvivor(i)) {
            iSurvivor = i;
            GetClientName(i, name, MAX_NAME_LENGTH);
            Format(testName, sizeof(testName), "%s's gender is %d", name, GetGender(i));
            SMIS(NameToGender(name), GetGender(i), testName);
        }
    }

    RunCheatCommand(iSurvivor, "z_spawn", "hunter");
    RunCheatCommand(iSurvivor, "z_spawn", "jockey");
    RunCheatCommand(iSurvivor, "z_spawn", "witch");
    CreateTimer(0.1, GenderTimer);

    // Unfortunately there is no easy way to spawn uncommon infected to test
    // their gender values. 
}

public Action:GenderTimer(Handle:hTimer) {
    new iHunter = -1;
    new iJockey = -1;
    new iWitch = -1;
    for (new client = 1; client < MaxClients+1; ++client) {
        if (IsInfected(client)) {
            if (GetInfectedClass(client) == L4D2Infected_Hunter) {
                iHunter = client;
            }
            else if (GetInfectedClass(client) == L4D2Infected_Jockey) {
                iJockey = client;
            }
        }
    }

    iWitch = FindEntityByClassname(-1, "witch");

    SMISNT(-1, iHunter, "Found a hunter");
    SMISNT(-1, iJockey, "Found a jockey");
    SMISNT(-1, iWitch, "Found a witch");
    SMIS(L4D2Gender_Male, GetGender(iHunter), "Hunter is male");
    // Interestingly the jockey is of neutral gender and so is the spitter
    SMIS(L4D2Gender_Neutral, GetGender(iJockey), "Jockey is neutral");
    SMIS(L4D2Gender_Female, GetGender(iWitch), "Witch is female");
}

static L4D2_Gender:NameToGender(const String:name[]) {
    if (StrEqual(name, "Zoey"))
        return L4D2Gender_Zoey;

    if (StrEqual(name, "Coach"))
        return L4D2Gender_Coach;

    if (StrEqual(name, "Bill"))
        return L4D2Gender_Bill;

    if (StrEqual(name, "Francis"))
        return L4D2Gender_Francis;

    if (StrEqual(name, "Rochelle"))
        return L4D2Gender_Rochelle;

    if (StrEqual(name, "Louis"))
        return L4D2Gender_Louis;

    if (StrEqual(name, "Ellis"))
        return L4D2Gender_Ellis;

    if (StrEqual(name, "Nick"))
        return L4D2Gender_Nick;

    return L4D2Gender_Neutral;
}