#include <adt_trie>
#include <sourcemod>
#include <sdktools>

// Weapon names for each of the weapons, used in identification.
static const String:WeaponNames[WeaponId][] =
{
    "weapon_none", "weapon_pistol", "weapon_smg",                                            // 0
    "weapon_pumpshotgun", "weapon_autoshotgun", "weapon_rifle",                              // 3
    "weapon_hunting_rifle", "weapon_smg_silenced", "weapon_shotgun_chrome",                  // 6
    "weapon_rifle_desert", "weapon_sniper_military", "weapon_shotgun_spas",                  // 9
    "weapon_first_aid_kit", "weapon_molotov", "weapon_pipe_bomb",                            // 12
    "weapon_pain_pills", "weapon_gascan", "weapon_propanetank",                              // 15
    "weapon_oxygentank", "weapon_melee", "weapon_chainsaw",                                  // 18
    "weapon_grenade_launcher", "weapon_ammo_pack", "weapon_adrenaline",                      // 21
    "weapon_defibrillator", "weapon_vomitjar", "weapon_rifle_ak47",                          // 24
    "weapon_gnome", "weapon_cola_bottles", "weapon_fireworkcrate",                           // 27
    "weapon_upgradepack_incendiary", "weapon_upgradepack_explosive", "weapon_pistol_magnum", // 30
    "weapon_smg_mp5", "weapon_rifle_sg552", "weapon_sniper_awp",                             // 33
    "weapon_sniper_scout", "weapon_rifle_m60", "weapon_tank_claw",                           // 36
    "weapon_hunter_claw", "weapon_charger_claw", "weapon_boomer_claw",                       // 39
    "weapon_smoker_claw", "weapon_spitter_claw", "weapon_jockey_claw",                       // 42
    "weapon_machinegun", "vomit", "splat",                                                   // 45
    "pounce", "lounge", "pull",                                                              // 48
    "choke", "rock", "physics",                                                              // 51
    "ammo", "upgrade_item"                                                                   // 54
};

// World Weapon models for each of the weapons. Useful for making new weapon spawns
// Some models are left blank because no single model can be given, the model is known or none exist.
static const String:WeaponModels[WeaponId][] =
{
    "",
    "/w_models/weapons/w_pistol_B.mdl",
    "/w_models/weapons/w_smg_uzi.mdl",
    "/w_models/weapons/w_shotgun.mdl",
    "/w_models/weapons/w_autoshot_m4super.mdl",
    "/w_models/weapons/w_rifle_m16a2.mdl",
    "/w_models/weapons/w_sniper_mini14.mdl",
    "/w_models/weapons/w_smg_a.mdl",
    "/w_models/weapons/w_pumpshotgun_a.mdl",
    "/w_models/weapons/w_desert_rifle.mdl",           // "/w_models/weapons/w_rifle_b.mdl"
    "/w_models/weapons/w_sniper_military.mdl",
    "/w_models/weapons/w_shotgun_spas.mdl",
    "/w_models/weapons/w_eq_medkit.mdl",
    "/w_models/weapons/w_eq_molotov.mdl",
    "/w_models/weapons/w_eq_pipebomb.mdl",
    "/w_models/weapons/w_eq_painpills.mdl",
    "/props_junk/gascan001a.mdl",
    "/props_junk/propanecanister001.mdl",
    "/props_equipment/oxygentank01.mdl",
    "",                                               // "/weapons/w_knife_t.mdl",
                                                      // "/weapons/melee/w_bat.mdl",
                                                      // "/weapons/melee/w_chainsaw.mdl
                                                      // "/weapons/melee/w_cricket_bat.mdl",
                                                      // "/weapons/melee/w_crowbar.mdl",
                                                      // "/weapons/melee/w_didgeridoo.mdl",
                                                      // "/weapons/melee/w_electric_guitar.mdl",
                                                      // "/weapons/melee/w_fireaxe.mdl",
                                                      // "/weapons/melee/w_frying_pan.mdl",
                                                      // "/weapons/melee/w_golfclub.mdl",
                                                      // "/weapons/melee/w_katana.mdl",
                                                      // "/weapons/melee/w_machete.mdl",
                                                      // "/weapons/melee/w_riotshield.mdl",
                                                      // "/weapons/melee/w_tonfa.mdl"
    "/weapons/melee/w_chainsaw.mdl",
    "/w_models/weapons/w_grenade_launcher.mdl",
    "",
    "/w_models/weapons/w_eq_adrenaline.mdl",
    "/w_models/weapons/w_eq_defibrillator.mdl",
    "/w_models/weapons/w_eq_bile_flask.mdl",
    "/w_models/weapons/w_rifle_ak47.mdl",
    "/props_junk/gnome.mdl",
    "/w_models/weapons/w_cola.mdl",
    "/props_junk/explosive_box001.mdl",
    "/w_models/weapons/w_eq_incendiary_ammopack.mdl",
    "/w_models/weapons/w_eq_explosive_ammopack.mdl",
    "/w_models/weapons/w_desert_eagle.mdl",
    "/w_models/weapons/w_smg_mp5.mdl",
    "/w_models/weapons/w_rifle_sg552.mdl",
    "/w_models/weapons/w_sniper_awp.mdl",
    "/w_models/weapons/w_sniper_scout.mdl",
    "/w_models/weapons/w_m60.mdl",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    ""
};

static const WeaponSlots[_:WeaponId] =
{
    -1, // WEPID_NONE
    1,  // WEPID_PISTOL
    0,  // WEPID_SMG
    0,  // WEPID_PUMPSHOTGUN
    0,  // WEPID_AUTOSHOTGUN
    0,  // WEPID_RIFLE
    0,  // WEPID_HUNTING_RIFLE
    0,  // WEPID_SMG_SILENCED
    0,  // WEPID_SHOTGUN_CHROME
    0,  // WEPID_RIFLE_DESERT
    0,  // WEPID_SNIPER_MILITARY
    0,  // WEPID_SHOTGUN_SPAS
    3,  // WEPID_FIRST_AID_KIT
    2,  // WEPID_MOLOTOV
    2,  // WEPID_PIPE_BOMB
    4,  // WEPID_PAIN_PILLS
    -1, // WEPID_GASCAN
    -1, // WEPID_PROPANE_TANK
    -1, // WEPID_OXYGEN_TANK
    1,  // WEPID_MELEE
    1,  // WEPID_CHAINSAW
    0,  // WEPID_GRENADE_LAUNCHER
    3,  // WEPID_AMMO_PACK
    4,  // WEPID_ADRENALINE
    3,  // WEPID_DEFIBRILLATOR
    2,  // WEPID_VOMITJAR
    0,  // WEPID_RIFLE_AK47
    -1, // WEPID_GNOME_CHOMPSKI
    -1, // WEPID_COLA_BOTTLES
    -1, // WEPID_FIREWORKS_BOX
    3,  // WEPID_INCENDIARY_AMMO
    3,  // WEPID_FRAG_AMMO
    1,  // WEPID_PISTOL_MAGNUM
    0,  // WEPID_SMG_MP5
    0,  // WEPID_RIFLE_SG552
    0,  // WEPID_SNIPER_AWP
    0,  // WEPID_SNIPER_SCOUT
    0,  // WEPID_RIFLE_M60
    -1, // WEPID_TANK_CLAW
    -1, // WEPID_HUNTER_CLAW
    -1, // WEPID_CHARGER_CLAW
    -1, // WEPID_BOOMER_CLAW
    -1, // WEPID_SMOKER_CLAW
    -1, // WEPID_SPITTER_CLAW
    -1, // WEPID_JOCKEY_CLAW
    -1, // WEPID_MACHINEGUN
    -1, // WEPID_FATAL_VOMIT
    -1, // WEPID_EXPLODING_SPLAT
    -1, // WEPID_LUNGE_POUNCE
    -1, // WEPID_LOUNGE
    -1, // WEPID_FULLPULL
    -1, // WEPID_CHOKE
    -1, // WEPID_THROWING_ROCK
    -1, // WEPID_TURBO_PHYSICS
    -1, // WEPID_AMMO
    -1  // WEPID_UPGRADE_ITEM
};

static Handle:hWeaponNamesTrie;


/**
 * Initializes internal structure necessary for weapons.inc functions
 * @remark It is recommended that you run this function on plugin start, but not necessary
 *
 * @noreturn
 */
L4D2Util_Weapons_Init()
{
    InitWeaponNamesTrie();
}

L4D2Util_Weapons_CreateNatives() {
    CreateNative("GetSlotFromWeaponId", _native_L4D2Util_GetSlotFromWeaponId);
    CreateNative("HasValidWeaponModel", _native_L4D2Util_HasValidWeaponModel);
    CreateNative("WeaponNameToId", _native_L4D2Util_WeaponNameToId);
    CreateNative("GetWeaponName", _native_L4D2Util_GetWeaponName);
    CreateNative("GetWeaponModel", _native_L4D2Util_GetWeaponModel);
}

stock GetSlotFromWeaponId(WeaponId:wepid)
{
    return IsValidWeaponId(wepid) ? WeaponSlots[wepid] : -1;
}

public _native_L4D2Util_GetSlotFromWeaponId(Handle:hPlugin, iNumParams) {
    return _:GetSlotFromWeaponId(WeaponId:GetNativeCell(1));
}

stock bool:HasValidWeaponModel(WeaponId:wepid)
{
    // return IsValidWeaponId(wepid) && WeaponModels[wepid][0] == '\0';
    return IsValidWeaponId(wepid) && WeaponModels[wepid][0] != '\0';
}

public _native_L4D2Util_HasValidWeaponModel(Handle:hPlugin, iNumParams) {
    return _:HasValidWeaponModel(WeaponId:GetNativeCell(1));
}

static stock WeaponId:WeaponNameToId(const String:weaponName[])
{
    new WeaponID:id;
    if(GetTrieValue(hWeaponNamesTrie, weaponName, id))
    {
        return WeaponId:id;
    }
    return WEPID_NONE;
}

public _native_L4D2Util_WeaponNameToId(Handle:hPlugin, iNumParams) {
    decl len;
    GetNativeStringLength(1, len);
    decl String:name[len+1];
    GetNativeString(1, name, len+1);
    return _:WeaponNameToId(name);
}

#define GETWEAPONNAME(%0) (IsValidWeaponId(WeaponId:(%0)) ? WeaponNames[WeaponId:(%0)] : "")

stock GetWeaponName(WeaponId:wepid, String:nameBuffer[], length)
{
    return strcopy(nameBuffer, length, GETWEAPONNAME(wepid));
}

public _native_L4D2Util_GetWeaponName(Handle:hPlugin, iNumParams) {
    new WeaponId:wepid = WeaponId:GetNativeCell(1);
    
    if(!IsValidWeaponId(wepid)) return 0;

    new len = GetNativeCell(3);
    decl bytes;
    SetNativeString(2, WeaponNames[wepid], len, _, bytes);
    return bytes;
}

#define GETWEAPONMODEL(%0) (HasValidWeaponModel(WeaponId:(%0)) ? WeaponModels[WeaponId:(%0)] : "")

stock GetWeaponModel(WeaponId:wepid, String:modelBuffer[], length)
{
    return strcopy(modelBuffer, length, GETWEAPONMODEL(wepid));
}

public _native_L4D2Util_GetWeaponModel(Handle:hPlugin, iNumParams) {
    new WeaponId:wepid = WeaponId:GetNativeCell(1);
    
    if(!HasValidWeaponModel(wepid)) return 0;

    new len = GetNativeCell(3);
    decl bytes;
    SetNativeString(2, WeaponModels[wepid], len, _, bytes);
    return bytes;
}

static InitWeaponNamesTrie()
{
    hWeaponNamesTrie = CreateTrie();
    for(new i = 0; i < _:WeaponId; i++)
    {
        SetTrieValue(hWeaponNamesTrie, WeaponNames[WeaponId:i], i);
    }
}



