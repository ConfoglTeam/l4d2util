#pragma semicolon 1

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

#include "src/test_stocks.inc"

new bool:bTankSpawnFwdClient = false;
new bool:bTankDeathFwdClient = false;
new bool:bTankSpawnFwdFired = false;
new bool:bTankDeathFwdFired = false;

public OnStartTests() {
    new iHittableCount;
    new iHittable;
    
    new iMaxEnts = GetMaxEntities();
    for (new i = 0; i < iMaxEnts; i++) {
        if (IsValidEntity(i) && IsValidEdict(i) && IsTankHittable(i)) {
            iHittableCount++;
            iHittable = i;
        }
    }
    
    SMIS(iHittableCount, 5, "there are 5 hittables on parish 1");
    
    new client;
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsSurvivor(i)) {
            client = i;
            break;
        }
    }
    
    SMISNT(client, 0, "found a survivor");
    RunCheatCommand(client, "z_spawn", "tank");
    CreateTimer(0.1, FindTankTimer);
    
    // Give the tank some time to die
    CreateTimer(10.0, CheckForwardsTimer);
}

public OnTankSpawn(iTankClient) {
    bTankSpawnFwdFired = true;
    bTankSpawnFwdClient = IsTank(iTankClient);
}

public OnTankDeath(iTankClient) {
    bTankDeathFwdFired = true;
    bTankDeathFwdClient = IsTank(iTankClient);
}

public Action:FindTankTimer(Handle:hTimer) {
    new iTheTank;
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsTank(i)) {
            iTheTank = i;
            break;
        }
    }
    
    SMISNT(iTheTank, 0, "found the tank");
    SMOK(IsTankInPlay(), "the tank is in play");
    SMIS(GetInfectedClass(iTheTank), L4D2Infected_Tank, "tank's infected class");
    SMIS(iTheTank, FindTankClient(-1), "the tank's client matches GetTankClient()");
    SMIS(GetTankFrustration(iTheTank), 100, "newly spawned tank's frustration is 100");
    SMOK(!IsTankOnFire(iTheTank), "tank is not on fire");
    SMIS(NumTanksInPlay(), 1, "there is only one tank in play");
    
    decl String:sBuffer[32];
    GetInfectedClassName(GetInfectedClass(iTheTank), sBuffer, sizeof(sBuffer));
    SMOK(!strcmp(sBuffer, "Tank"), "the tank's class name is Tank");
    
    RunCheatCommand(iTheTank, "kill", "");
}

public Action:CheckForwardsTimer(Handle:hTimer) {
    SMOK(bTankSpawnFwdFired, "OnTankSpawn() was fired");
    SMOK(bTankSpawnFwdClient, "OnTankSpawn() was passed the tank client");
    SMOK(bTankDeathFwdFired, "OnTankDeath() was fired");
    SMOK(bTankDeathFwdClient, "OnTankDeath() was passed the tank client");   
}

