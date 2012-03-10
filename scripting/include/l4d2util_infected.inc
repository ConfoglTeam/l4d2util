#if defined l4d2util_infected_inc_
    #endinput
#endif
#define l4d2util_infected_inc_

stock bool:IsInfected(client) {
    if (!IsClientInGame(client) || GetClientTeam(client) != L4D2Team_Infected) {
        return false;
    }
    return true;
}

stock L4D2_Infected:GetInfectedClass(client) {
    return L4D2_Infected:GetEntProp(client, Prop_Send, "m_zombieClass");
}

stock bool:IsInfectedGhost(client) {
    return bool:GetEntProp(client, Prop_Send, "m_isGhost");
}

