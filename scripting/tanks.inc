#include <sourcemod>
#include <sdktools>

#include "l4d2util_constants.inc"
#include "l4d2util_infected.inc"
#include "l4d2util_tanks.inc"

new iTankClient = -1;

new bool:bTankInPlay = false;

new Handle:hFwdOnTankPunchHittable;
new Handle:hFwdOnTankSpawn;
new Handle:hFwdOnTankPass;
new Handle:hFwdOnTankDeath;

L4D2Util_Tanks_OnRoundStart() {
    iTankClient = -1;
    bTankInPlay = false;
    CreateTimer(0.1, L4D2Util_Tanks_HookCars);
}

public Action:L4D2Util_Tanks_HookCars(Handle:hTimer) {
     new iEntity = -1;
     
     while ((iEntity = FindEntityByClassname(iEntity, "prop_physics")) != -1) {
         if (IsTankHittable(iEntity)) {
             HookSingleEntityOutput(iEntity, "OnHitByTank", TankHittablePunched);
         }
     }
     
     iEntity = -1;
     
     while ((iEntity = FindEntityByClassname(iEntity, "prop_alarm_car")) != -1) {
         HookSingleEntityOutput(iEntity, "OnHitByTank", TankHittablePunched);
     }
}

public TankHittablePunched( const String:output[], caller, activator, Float:delay ) {
    Call_StartForward(hFwdOnTankPunchHittable);
    Call_PushCell(GetTankClient());
    Call_PushCell(caller);
    Call_Finish();
}

L4D2Util_Tanks_TankSpawn(client) {
    new iOldTankClient = iTankClient;
    iTankClient = client;
    
    if (!bTankInPlay) {
        bTankInPlay = true;
        Call_StartForward(hFwdOnTankSpawn);
        Call_PushCell(client);
        Call_Finish();
    }
    else {
        Call_StartForward(hFwdOnTankPass);
        Call_PushCell(client);
        Call_PushCell(iOldTankClient);
        Call_Finish();
    }
}

L4D2Util_Tanks_PlayerDeath(client) {
    if (!bTankInPlay) {
        return;
    }
    
    if (client == iTankClient) {
        CreateTimer(0.5, L4D2Util_Tanks_TankDeathDelay, iTankClient);
    }
}

public Action:L4D2Util_Tanks_TankDeathDelay(Handle:hTimer, any:iOldTankClient) {
    if (iOldTankClient != iTankClient) {
        return;
    }
    
    iTankClient = FindTankClient();
    
    if (iTankClient == -1) {
        bTankInPlay = false;
        Call_StartForward(hFwdOnTankDeath);
        Call_PushCell(iOldTankClient);
        Call_Finish();
    }
    else if (iTankClient != iOldTankClient) {
        Call_StartForward(hFwdOnTankPass);
        Call_PushCell(iTankClient);
        Call_PushCell(iOldTankClient);
        Call_Finish();
    }
}

L4D2Util_Tanks_CreateForwards() {
    hFwdOnTankPunchHittable = CreateGlobalForward("OnTankPunchHittable", ET_Ignore, Param_Cell, Param_Cell);
    hFwdOnTankSpawn = CreateGlobalForward("OnTankSpawn", ET_Ignore, Param_Cell);
    hFwdOnTankPass = CreateGlobalForward("OnTankPass", ET_Ignore, Param_Cell, Param_Cell);
    hFwdOnTankDeath = CreateGlobalForward("OnTankDeath", ET_Ignore, Param_Cell);
}

L4D2Util_Tanks_CreateNatives() {
    CreateNative("IsTankInPlay", _native_L4D2Util_IsTankInPlay);
    CreateNative("GetTankClient", _native_L4D2Util_GetTankClient);
}

public _native_L4D2Util_IsTankInPlay(Handle:hPlugin, iNumParams) {
    return _:bTankInPlay;
}

FindTankClient() {
    for (new i = 0; i < MaxClients+1; i++) {
        if (IsTank(i)) {
            return i;
        }
    }
    
    return -1;
}

GetTankClient() {
    if (iTankClient == -1)
        return -1;
    
    if (!IsTank(iTankClient)) {
        iTankClient = FindTankClient();
    }
    
    return iTankClient;
}

public _native_L4D2Util_GetTankClient(Handle:hPlugin, iNumParams) {
    return GetTankClient();
}

