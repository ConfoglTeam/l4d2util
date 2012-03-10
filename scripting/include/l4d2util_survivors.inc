#if defined l4d2util_survivors_inc_
    #endinput
#endif
#define l4d2util_survivors_inc_

stock bool:IsSurvivor(client) {
    if (!IsClientInGame(client) || GetClientTeam(client) != L4D2Team_Survivor) {
        return false;
    }
    return true;
}

stock bool:IsIncapacitated(client) {
    return bool:GetEntProp(client, Prop_Send, "m_isIncapacitated");
}

stock GetSurvivorPermanentHealth(client) {
    return GetEntProp(client, Prop_Send, m_iHealth);
}

stock GetSurvivorTemporaryHealth(client) {
    new Float:fDecayRate = GetConVarFloat(FindConVar("pain_pills_decay_rate"));
    new Float:fHealthBuffer = GetEntPropFloat(client, Prop_send, "m_healthBuffer");
    new Float:fHealthBufferTime = GetEntPropFloat(client, Prop_Send, "m_healthBufferTime"));
    new iTempHp = RoundToCeil(fHealthBuffer - ((GetGameTime() - fHealthBufferTime) * fDecayRate)) - 1;
    return iTempHp > 0 ? iTempHp : 0;
}
