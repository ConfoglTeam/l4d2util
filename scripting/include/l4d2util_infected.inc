#if defined l4d2util_infected_inc_
    #endinput
#endif
#define l4d2util_infected_inc_

/**
 * Return true if the client is on the infected team.
 *
 * @param client client ID
 * @return bool
 */
stock bool:IsInfected(client) {
    if (!IsClientInGame(client) || GetClientTeam(client) != L4D2Team_Infected) {
        return false;
    }
    return true;
}

/**
 * Returns the ID of the client's infected class. Use GetInfectedClassName()
 * to convert it to a string.
 *
 * @param client client ID
 * @return class ID
 */
stock L4D2_Infected:GetInfectedClass(client) {
    return L4D2_Infected:GetEntProp(client, Prop_Send, "m_zombieClass");
}

/**
 * Return true if the infected is in ghost (spawn) mode.
 *
 * @param client client ID
 * @return bool
 */
stock bool:IsInfectedGhost(client) {
    return bool:GetEntProp(client, Prop_Send, "m_isGhost");
}

/**
 * Converts an infected type ID to a string.
 *
 * @param iClass infected class ID
 * @param sBuffer buffer to store the class name in
 * @param iBufLen size of sBuffer
 * @noreturn
 */
stock GetInfectedClassName(L4D2_Infected:iClass, String:sBuffer[], iBufLen) {
    strcopy(sBuffer, iBufLen, L4D2_InfectedNames[iClass-1]); 
}

