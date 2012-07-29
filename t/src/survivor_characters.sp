#pragma semicolon 1

#define L4D2UTIL_STOCKS_ONLY

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

#include "src/test_stocks.inc"

new g_iSurvivor;

public OnStartTests() {
    decl String:testName[128];
    decl String:clientName[MAX_NAME_LENGTH];
    decl String:charName[MAX_NAME_LENGTH];

    for (new client = 1; client < MaxClients+1; ++client) {
        if (IsSurvivor(client)) {
            GetClientName(client, clientName, MAX_NAME_LENGTH);
            Format(testName, sizeof(testName), "Identified %s", clientName);
            SMIS(NameToCharacter(clientName), IdentifySurvivor(client), testName);
            SMOK(GetSurvivorName(IdentifySurvivor(client), charName, sizeof(charName)), "Got %s's character name", clientName);
            SMSTREQ(clientName, charName, "%s's character name is correct", clientName);
            g_iSurvivor = client;
        }
    }

    SMOK(! GetSurvivorName(SC_NONE, charName, sizeof(charName)), "SC_NONE has no survivor name");

    RunCheatCommand(g_iSurvivor, "z_spawn", "hunter");
    CreateTimer(0.1, GetSiTimer);
}

public Action:GetSiTimer(Handle:hTimer) {
    new iHunter;
    for (new client = 1; client < MaxClients+1; ++client) {
        if (IsInfected(client)) {
            iHunter = client;
            break;
        }
    }
    decl String:testName[128];
    Format(testName, sizeof(testName), "%N's survivor character is SC_NONE", iHunter);
    SMIS(SC_NONE, IdentifySurvivor(iHunter), testName);
}

static SurvivorCharacter:NameToCharacter(const String:name[]) {
    if (StrEqual(name, "Zoey"))
        return SC_ZOEY;

    if (StrEqual(name, "Coach"))
        return SC_COACH;

    if (StrEqual(name, "Bill"))
        return SC_BILL;

    if (StrEqual(name, "Francis"))
        return SC_FRANCIS;

    if (StrEqual(name, "Rochelle"))
        return SC_ROCHELLE;

    if (StrEqual(name, "Louis"))
        return SC_LOUIS;

    if (StrEqual(name, "Ellis"))
        return SC_ELLIS;

    if (StrEqual(name, "Nick"))
        return SC_NICK;

    return SC_NONE;
}

