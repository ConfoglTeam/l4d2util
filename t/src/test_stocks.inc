stock RunCheatCommand(client, String:sCmd[], String:sArgs[]) {
    decl String:sFullCmd[128];
    
    Format(sFullCmd, sizeof(sFullCmd), "%s %s", sCmd, sArgs);
    new flags = GetCommandFlags(sCmd);
    SetCommandFlags(sCmd, flags ^ FCVAR_CHEAT);
    FakeClientCommand(client, sFullCmd);
    SetCommandFlags(sCmd, flags);
}

