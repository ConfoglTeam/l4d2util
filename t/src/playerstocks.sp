#pragma semicolon 1

#undef REQUIRE_PLUGIN
#include <l4d2util>
#define REQUIRE_PLUGIN
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
    
    IncapPlayer(iSurvivor);
    SMOK(IsIncapacitated(iSurvivor), "the survivor is incapacitated");
    
    // Use a weird bug when you give health to an incapped player to test temp health
    RunCheatCommand(iSurvivor, "give", "health");
    SMISNT(GetSurvivorTemporaryHealth(iSurvivor), 0, "the survivor has temp health");
    
    RunCheatCommand(iSurvivor, "z_spawn", "hunter");
    CreateTimer(0.1, FindHunterTimer);
}

public Action:FindHunterTimer(Handle:hTimer) {
    new iHunter;
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsInfected(i)) {
            iHunter = i;
            break;
        }
    }
    
    SMOK(iHunter != 0, "found an infected");
    SMIS(GetInfectedClass(iHunter), L4D2Infected_Hunter, "the infected is an hunter");
    SMIS(IsInfectedGhost(iHunter), false, "the hunter isn't in ghost mode");
    
    decl String:sBuffer[32];
    GetInfectedClassName(GetInfectedClass(iHunter), sBuffer, sizeof(sBuffer));
    SMOK(!strcmp(sBuffer, "Hunter"), "the hunter's class name is Hunter");
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

