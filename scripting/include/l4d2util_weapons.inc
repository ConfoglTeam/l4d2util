#if defined l4d2_weapons_inc_
    #endinput
#endif
#define l4d2_weapons_inc_

// Weapon ID enumerations.
// These values are *NOT* arbitrary! 
// They are used in game as the weaponid for weapon_spawn entities
enum WeaponId
{
    WEPID_NONE,             // 0
    WEPID_PISTOL,           // 1
    WEPID_SMG,              // 2
    WEPID_PUMPSHOTGUN,      // 3
    WEPID_AUTOSHOTGUN,      // 4
    WEPID_RIFLE,            // 5
    WEPID_HUNTING_RIFLE,    // 6
    WEPID_SMG_SILENCED,     // 7
    WEPID_SHOTGUN_CHROME,   // 8
    WEPID_RIFLE_DESERT,     // 9
    WEPID_SNIPER_MILITARY,  // 10
    WEPID_SHOTGUN_SPAS,     // 11
    WEPID_FIRST_AID_KIT,    // 12
    WEPID_MOLOTOV,          // 13
    WEPID_PIPE_BOMB,        // 14
    WEPID_PAIN_PILLS,       // 15
    WEPID_GASCAN,           // 16
    WEPID_PROPANE_TANK,     // 17
    WEPID_OXYGEN_TANK,      // 18
    WEPID_MELEE,            // 19
    WEPID_CHAINSAW,         // 20
    WEPID_GRENADE_LAUNCHER, // 21
    WEPID_AMMO_PACK,        // 22
    WEPID_ADRENALINE,       // 23
    WEPID_DEFIBRILLATOR,    // 24
    WEPID_VOMITJAR,         // 25
    WEPID_RIFLE_AK47,       // 26
    WEPID_GNOME_CHOMPSKI,   // 27
    WEPID_COLA_BOTTLES,     // 28
    WEPID_FIREWORKS_BOX,    // 29
    WEPID_INCENDIARY_AMMO,  // 30
    WEPID_FRAG_AMMO,        // 31
    WEPID_PISTOL_MAGNUM,    // 32
    WEPID_SMG_MP5,          // 33
    WEPID_RIFLE_SG552,      // 34
    WEPID_SNIPER_AWP,       // 35
    WEPID_SNIPER_SCOUT,     // 36
    WEPID_RIFLE_M60,        // 37
    WEPID_TANK_CLAW,        // 38
    WEPID_HUNTER_CLAW,      // 39
    WEPID_CHARGER_CLAW,     // 40
    WEPID_BOOMER_CLAW,      // 41
    WEPID_SMOKER_CLAW,      // 42
    WEPID_SPITTER_CLAW,     // 43
    WEPID_JOCKEY_CLAW,      // 44
    WEPID_MACHINEGUN,       // 45
    WEPID_VOMIT,            // 46
    WEPID_SPLAT,            // 47
    WEPID_POUNCE,           // 48
    WEPID_LOUNGE,           // 49
    WEPID_PULL,             // 50
    WEPID_CHOKE,            // 51
    WEPID_ROCK,             // 52
    WEPID_PHYSICS,          // 53
    WEPID_AMMO,             // 54
    WEPID_UPGRADE_ITEM      // 55
};

/**
 * Performs bounds checking to determine if a WeaponId is valid
 * @remark Simple check to see if wepid has a garbage value
 *
 * @param wepid        WeaponId to check for validity
 * @return True if wepid is valid, false otherwise.
 */
stock bool:IsValidWeaponId(WeaponId:wepid)
{
    return wepid >= WEPID_NONE && wepid < WeaponId;
}

#if !defined __IN_L4D2UTIL__

/**
 * Get the player weapon slot used by the given WeaponId.
 * 
 * @param wepid     WeaponId to get the slot for.
 * @return Slot number (0-4) or -1 for invalid WeaponId or no slot
 */
native GetSlotFromWeaponId(WeaponId:wepid);

/**
 * Checks to see if a given weaponid has a known WeaponModel in this file's model array
 * @remark Some weapons (like weapon_melee) have multiple valid models, and this will report false for them.
 *
 * @param wepid        WeaponId to check for a known weapon model for.
 * @return True if a valid weapon model exists for wepid, false otherwise.
 */
native bool:HasValidWeaponModel(WeaponId:wepid);

/**
 * Tries to look up a WeaponId for a given Weapon Name.
 *
 * @param weaponName    Weapon name string to look up Id from
 * @return                The corresponding WeaponId if found, else WEPID_NONE
 */
native WeaponId:WeaponNameToId(const String:weaponName[]);

/**
 * Tries to look up L4D2's internal weapon name for a given WeaponId.
 *
 * @param wepid            WeaponId To get name of.
 * @param nameBuffer    String buffer to write the weapon name to.
 * @param length        Max length which can be written to the buffer.
 * @return                Number of bytes written to buffer, or 0 for invalid weaponId.
 */
native GetWeaponName(WeaponId:wepid, String:nameBuffer[], length);

/**
 * Tries to look up the weapon model for a given WeaponId.
 * @remarks You should use HasValidWeaponModel to make sure the WeaponId you're looking up has a valid model associated with it.
 *
 * @param wepid            WeaponId To get name of.
 * @param nameBuffer    String buffer to write the weapon name to.
 * @param length        Max length which can be written to the buffer.
 * @return                Number of bytes written to buffer, or 0 for invalid weaponid or no weapon model available.
 */
native GetWeaponModel(WeaponId:wepid, String:modelBuffer[], length);

#endif

/**
 * Identifies a weapon spawn or weapon entity as a WeaponID
 * @remark Should work on most weapon ents--even spawns, singles, held, etc.
 *
 * @param entity        Index of entity to identify
 * @return WeaponID for the entity if it is a weapon, WEPID_NONE otherwise
 */
static stock WeaponId:IdentifyWeapon(entity)
{
    if(!entity || !IsValidEntity(entity) || !IsValidEdict(entity))
    {
        return WEPID_NONE;
    }
    decl String:class[64];
    if(!GetEdictClassname(entity, class, sizeof(class)))
    {
        return WEPID_NONE;
    }

    if(StrEqual(class, "weapon_spawn"))
    {
        return WeaponId:GetEntProp(entity,Prop_Send,"m_weaponID");
    }

    new len = strlen(class);
    if(len-6 > 0 && StrEqual(class[len-6], "_spawn"))
    {
        class[len-6]='\0';
        return WeaponNameToId(class);
    }
    
    return WeaponNameToId(class);
}

/**
 * Attempts to convert a weapon spawn entity to a given weapon spawn
 * @remark Truthfully, this will work on any entity with origin/rotation.
 *        Also, requires the weapon to either have a Valid weapon model or have one provided
 *
 * @param entity        Index of entity to convert to weapon spawn
 * @param wepid            WeaponId of the weapon to have the spawner hold
 * @param count            Weapon count for the spawner (default 5)
 * @param model            World model to use for the weapon spawn
 * @return entity of the new weapon spawn, or -1 on errors.
 */
static stock ConvertWeaponSpawn(entity, WeaponId:wepid, count=5, const String:model[] = "")
{
    if(!IsValidEntity(entity)) return -1;
    if(!IsValidWeaponId(wepid)) return -1;
    if(model[0] == '\0' && !HasValidWeaponModel(wepid)) return -1;
    
    
    new Float:origins[3], Float:angles[3];
    GetEntPropVector(entity, Prop_Send, "m_vecOrigin", origins);
    GetEntPropVector(entity, Prop_Send, "m_angRotation", angles);
    
    AcceptEntityInput(entity, "kill");
    
    entity = CreateEntityByName("weapon_spawn");
    if(!IsValidEntity(entity)) return -1;
    
    SetEntProp(entity, Prop_Send, "m_weaponID", wepid);

    decl String:buf[64];
    if(model[0] == '\0')
    {
        SetEntityModel(entity, model);
    }
    else
    {
        GetWeaponModel(wepid, buf, sizeof(buf));
        SetEntityModel(entity, buf);
    }
    IntToString(count, buf, sizeof(buf));
    DispatchKeyValue(entity, "count", buf);
    
    TeleportEntity(entity, origins, angles, NULL_VECTOR);
    DispatchSpawn(entity);
    SetEntityMoveType(entity,MOVETYPE_NONE);
    return entity;
}

// should not be called manually
stock L4D2Util_Weapons_SetNTVOptional()
{
    MarkNativeAsOptional("GetSlotFromWeaponId");
    MarkNativeAsOptional("HasValidWeaponModel");
    MarkNativeAsOptional("WeaponNameToId");
    MarkNativeAsOptional("GetWeaponName");
    MarkNativeAsOptional("GetWeaponModel");
}