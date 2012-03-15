#if defined l4d2_tanks_inc_
    #endinput
#endif
#define l4d2_tanks_inc_

/**
 * Is the player the tank? 
 *
 * @param client client ID
 * @return bool
 */
stock bool:IsTank(client) {
    return IsClientInGame(client)
        && L4D2_Team:GetClientTeam(client) == L4D2Team_Infected
        && GetInfectedClass(client) == L4D2Infected_Tank;
}

/**
 * Is the tank able to punch the entity with the tank for instant incaps? 
 *
 * @param iEntity entity ID
 * @return bool
 */
stock bool:IsTankHittable(iEntity) {
    if (!IsValidEntity(iEntity)) {
        return false;
    }
    
    decl String:className[64];
    
    GetEdictClassname(iEntity, className, sizeof(className));
    if ( StrEqual(className, "prop_physics") ) {
        if ( GetEntProp(iEntity, Prop_Send, "m_hasTankGlow", 1) ) {
            return true;
        }
    }
    else if ( StrEqual(className, "prop_car_alarm") ) {
        return true;
    }
    
    return false;
}

/**
 * Tanks frustation level in the range 0-100, where 100 is when the rage meter
 * is full.
 *
 * @param iTankClient tank's client ID
 * @return frustration level
 */
stock GetTankFrustration(iTankClient) {
    return (100 - GetEntProp(iTankClient, Prop_Send, "m_frustration"));
}

/**
 * Sets the tank's frustration level.
 *
 * @param iTankClient tank's client ID
 * @param iFrustration frustration level (0-100)
 * @noreturn
 */
stock SetTankFrustration(iTankClient, iFrustration) {
    if (iFrustration < 0 || iFrustation > 100) {
        return;
    }
    
    SetEntProp(iTankClient, Prop_Send, "m_frustration", 100-iFrustration);
}

/**
 * Returns true if the tank is on fire.
 * @remarks This should work for any client ID, even if they are not the tank 
 *
 * @param iTankClient tank's client ID
 * @param bool
 */
stock bool:IsTankOnFire(iTankClient) {
    return bool:(GetEntityFlags(iTankClient) & FL_ONFIRE);
}

/**
 * Searches for a player who is in control of a tank.
 *
 * @param iTankClient client index to begin searching from
 * @return client ID or -1 if not found
 */
stock FindTankClient(iTankClient) {
    for (new i = iTankClient < 0 ? 1 : iTankClient+1; i < MaxClients+1; i++) {
        if (IsTank(i)) {
            return i;
        }
    }
    
    return -1;
}

/**
 * Is there a tank currently in play?
 *
 * @return bool
 */
stock bool:IsTankInPlay() {
    return bool:(FindTankClient(-1) != -1);
}

/**
 * Counts the number of tanks currently in play.
 *
 * @return number of tanks in play
 */
stock NumTanksInPlay() {
    new count = 0;
    new client = -1;
    
    while ((client = FindTankClient(client)) != -1) {
        ++count;
    }
    
    return count;
}

