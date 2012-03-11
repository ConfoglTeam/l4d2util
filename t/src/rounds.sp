#pragma semicolon 1

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

#include "src/test_stocks.inc"

new iRoundStartFired;
new iRoundEndFired;

public OnStartTests() {
    SMIS(iRoundStartFired, 1, "round has started started once");
    
    for (new i = 1; i < MaxClients+1; i++) {
        if (IsSurvivor(i)) {
            RunCheatCommand(i, "kill", "");
        }
    }
    
    CreateTimer(20.0, RoundEndTimer);
}

public OnRoundStart() {
    iRoundStartFired++;
}

public OnRoundEnd() {
    iRoundEndFired++;
}

public Action:RoundEndTimer(Handle:hTimer) {
    SMIS(iRoundEndFired, 1, "round has ended once");
    SMIS(iRoundStartFired, 2, "round has started twice");
    SMOK(InSecondHalfOfRound(), "in the second half of the round");
}

