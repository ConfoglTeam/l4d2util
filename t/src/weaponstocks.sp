#pragma semicolon 1

#define L4D2UTIL_STOCKS_ONLY

#include <l4d2util>
#include <sourcemod>
#include <sdktools>
#include <smtest>

public OnStartTests() {
    SMOK(IsValidWeaponId(WEPID_RIFLE), "WEPID_RIFLE is valid");
    SMOK(!IsValidWeaponId(WeaponId:200), "WeaponId:200 is invalid");
    SMOK(IsValidWeaponId(WEPID_KATANA),"WEPID_KATANA is valid");
    SMOK(!IsValidWeaponId(MeleeWeaponId:200), "MeleeWeaponId:200 is invalid");

    // Show that overloaded function is working correctly
    SMOK(IsValidWeaponId(WeaponId:20), "WeaponId:20 is valid");
    SMOK(!IsValidWeaponId(MeleeWeaponId:20), "MeleeWeaponId:20 is invalid");

    SMIS(-1, GetSlotFromWeaponId(WEPID_NONE), "WEPID_NONE slot is -1");
    SMIS(0, GetSlotFromWeaponId(WEPID_RIFLE), "WEPID_RIFLE slot is 0");
    SMIS(1, GetSlotFromWeaponId(WEPID_MELEE), "WEPID_MELEE slot is 1");
    SMIS(2, GetSlotFromWeaponId(WEPID_MOLOTOV), "WEPID_MOLOTOV slot is 2");
    SMIS(3, GetSlotFromWeaponId(WEPID_FIRST_AID_KIT), "WEPID_FIRST_AID_KIT slot is 3");
    SMIS(4, GetSlotFromWeaponId(WEPID_PAIN_PILLS), "WEPID_PAIN_PILLS slot is 4");

    SMOK(!HasValidWeaponModel(WEPID_NONE), "WEPID_NONE has no weapon model");
    SMOK(!HasValidWeaponModel(WEPID_MELEE), "WEPID_MELEE has no weapon model");
    SMOK(!HasValidWeaponModel(WEPID_MELEE_NONE), "WEPID_MELEE_NONE has no weapon model");
    SMOK(HasValidWeaponModel(WEPID_RIFLE), "WEPID_RIFLE has a weapon model");
    SMOK(HasValidWeaponModel(WEPID_KATANA), "WEPID_KATANA has a weapon model");

    SMIS(WEPID_RIFLE, WeaponNameToId("weapon_rifle"), "\"weapon_rifle\" == WEPID_RIFLE");
    SMIS(WEPID_NONE, WeaponNameToId("nothing"), "\"nothing\" has no weapon id");

    decl String:name[128];
    decl String:model[PLATFORM_MAX_PATH];

    GetWeaponName(WEPID_RIFLE, name, sizeof(name));
    SMSTREQ("weapon_rifle", name, "name of WEPID_RIFLE");

    GetWeaponName(WeaponId:56, name, sizeof(name));
    SMSTREQ("", name, "name of WeaponId:56");

    GetWeaponModel(WEPID_RIFLE, model, sizeof(model));
    SMSTREQ("/w_models/weapons/w_rifle_m16a2.mdl", model, "model name of WEPID_RIFLE");

    GetWeaponModel(WEPID_NONE, model, sizeof(model));
    SMSTREQ("", model, "model name of WEPID_NONE");

    GetWeaponModel(WEPID_KATANA, model, sizeof(model));
    SMSTREQ("/weapons/melee/w_katana.mdl", model, "model name of WEPID_KATANA");

    GetWeaponModel(WEPID_MELEE_NONE, model, sizeof(model));
    SMSTREQ("", model, "model name of WEPID_MELEE_NONE");

    decl String:classname[128];
    new bool:bIdWep = false;
    new bool:bIdWepNone = false;
    new bool:bIdMeleeWepNone = false;

    for (new i = 1; i < GetEntityCount(); i++) {
        if (!IsValidEntity(i)) {
            continue;
        }

        GetEntityClassname(i, classname,  sizeof(classname));

        if (!StrEqual(classname, "weapon_spawn") && StrContains(classname, "weapon_") != -1) {
            if (!bIdWep) {
                SMOK(IdentifyWeapon(i) != WEPID_NONE, "IdentifyWeapon() works on weapon_spawn");
                bIdWep = true;
            }
            if (!bIdMeleeWepNone && !StrEqual(classname, "weapon_melee_spawn")) {
                SMOK(IdentifyMeleeWeapon(i) == WEPID_MELEE_NONE, "IdentifyMeleeWeapon() is WEPID_MELEE_NONE on a non-melee weapon spawn");
                bIdMeleeWepNone = true;
            }
        }
        else if (StrContains(classname, "weapon_") == -1) {
            if (!bIdWepNone) {
                SMOK(IdentifyWeapon(i) == WEPID_NONE, "IdentifyWeapon() is WEPID_NONE on a non-weapon entity");
                SMOK(IdentifyMeleeWeapon(i) == WEPID_MELEE_NONE, "IdentifyMeleeWeapon() is WEPID_MELEE_NONE on a non-weapon entity");
                bIdWepNone = true;
            }
        }

        if (bIdWep && bIdWepNone && bIdMeleeWepNone) {
            break;
        }
    }

    new iEntity = -1;
    while ((iEntity = FindEntityByClassname(iEntity, "weapon_melee_spawn")) != -1) {
        SMOK(IdentifyMeleeWeapon(iEntity) != WEPID_MELEE_NONE, "IdentifyMeleeWeapon() is not WEPID_MELEE_NONE for weapon_melee_spawn");
        break;
    }
    SMISNT(-1, iEntity, "Found a weapon_melee_spawn");
}

