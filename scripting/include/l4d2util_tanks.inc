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
    if (IsClientInGame(client)
        && GetClientTeam(client) == L4D2Team_Infected
        && GetInfectedClass(client) == L4D2Infected_Tank) {
        return true;
    }
    return false;
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
 * @return frustration level
 */
stock GetTankFrustration() {
    new iTankClient = GetTankClient();
    
    if (iTankClient == -1) {
        return -1;
    }
    
    return (100 - GetEntProp(iTankClient, Prop_Send, "m_frustration"));
}

/**
 * Sets the tank's frustration level.
 *
 * @param iFrustration frustration level (0-100)
 * @noreturn
 */
stock SetTankFrustration(iFrustration) {
    new iTankClient = GetTankClient();
    
    if (iTankClient == -1 || iFrustration < 0 || iFrustation > 100) {
        return;
    }
    
    SetEntProp(iTankClient, Prop_Send, "m_frustration", 100-iFrustration);
}

/**
 * Returns true if the tank is on fire.
 *
 * @param bool
 */
stock bool:IsTankOnFire() {
    new iTankClient = GetTankClient();
    
    if (iTankClient == -1) {
        return false;
    }
    
    return bool:(GetEntityFlags(iTankClient) & FL_ONFIRE);
}

