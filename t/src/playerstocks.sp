#pragma semicolon 1

#define L4D2UTIL_STOCKS_ONLY

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

#include "src/test_stocks.inc"

public OnStartTests() {
    new iSurvivorCount;
    new iSurvivor;
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsSurvivor(i)) {
            iSurvivorCount += 1;
            iSurvivor = i;
        }
    }
    
    SMIS(iSurvivorCount, 4, "there are 4 survivors");
    
    RunCheatCommand(iSurvivor, "give", "health");
    SMOK(!IsIncapacitated(iSurvivor), "the survivor is fully able");
    SMOK(GetSurvivorPermanentHealth(iSurvivor) >= 100, "the survivor has >100 hp");
    
    SMIS(GetSurvivorIncapCount(iSurvivor), 0, "the survivor has not been incapacitated");
    
    IncapPlayer(iSurvivor);
    SMOK(IsIncapacitated(iSurvivor), "the survivor is incapacitated");
    
    // Use a weird bug when you give health to an incapped player to test temp health
    RunCheatCommand(iSurvivor, "give", "health");
    SMISNT(GetSurvivorTemporaryHealth(iSurvivor), 0, "the survivor has temp health");
    
    RunCheatCommand(iSurvivor, "z_spawn", "jockey");
    CreateTimer(0.1, FindJockeyTimer);
}

public Action:FindJockeyTimer(Handle:hTimer) {
    new iJockey;
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsInfected(i)) {
            iJockey = i;
            break;
        }
    }
    
    SMOK(iJockey != 0, "found an infected");
    SMIS(GetInfectedClass(iJockey), L4D2Infected_Jockey, "the infected is a hunter");
    SMIS(IsInfectedGhost(iJockey), false, "the hunter isn't in ghost mode");
    
    decl String:sBuffer[32];
    GetInfectedClassName(GetInfectedClass(iJockey), sBuffer, sizeof(sBuffer));
    SMOK(!strcmp(sBuffer, "Jockey"), "the hunter's class name is Jockey");
    
    new Float:timestamp;
    new Float:duration;
    SMOK(GetInfectedAbilityTimer(iJockey, timestamp, duration), "got jockey ability timer");
    SMIS(duration, 0.0, "jockey ability duration 0.0");
    SMOK(SetInfectedAbilityTimer(iJockey, GetGameTime()+0.5, 0.5), "set ability timer");
    SMOK(GetInfectedAbilityTimer(iJockey, timestamp, duration), "got jockey ability timer again");
    SMIS(duration, 0.5, "duration is 0.5");
}

IncapPlayer(client) {
    decl Float:fPos[3];
    decl String:sUser[256];
    
    GetClientAbsOrigin(client, fPos);
    
    IntToString(GetClientUserId(client)+25, sUser, sizeof(sUser));
    
    new Damage = CreateEntityByName("point_hurt");
    
    DispatchKeyValue(Damage, "Damage", "500");
    DispatchKeyValue(Damage, "DamageType", "128");
    DispatchKeyValue(client, "targetname", sUser);
    DispatchKeyValue(Damage, "DamageTarget", sUser);
    
    DispatchSpawn(Damage);
    TeleportEntity(Damage, fPos, NULL_VECTOR, NULL_VECTOR);
    AcceptEntityInput(Damage, "Hurt");
    AcceptEntityInput(Damage, "Kill");
}

