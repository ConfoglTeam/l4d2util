#if defined l4d2util_rounds_inc_
    #endinput
#endif
#define l4d2util_rounds_inc_

#include <sdktools>

/**
 * Is the second round of this map currently being played?
 *
 * @return bool
 */
bool:InSecondHalfOfRound() {
    return bool:GameRules_GetProp("m_bInSecondHalfOfRound");
}

