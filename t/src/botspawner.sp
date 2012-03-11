#pragma semicolon 1

#include <sourcemod>

public OnPluginStart() {
    RegServerCmd("spawn_bots", SpawnBots);
}

// When I tested this it appeared that bots would not spawn on the server after
// a map changed until a real person actually joined. The hackery below force
// spawns all the survivor bots.
public Action:SpawnBots(args) {
    SetConVarInt(FindConVar("sb_all_bot_game"), 1);
    SetConVarString(FindConVar("mp_gamemode"), "versus");
    
    for (new i = 0; i < 4; i++) {
        new iFakeClient = CreateFakeClient("Test Runner");
        ChangeClientTeam(iFakeClient, 2);
        KickClient(iFakeClient);
    }
}

