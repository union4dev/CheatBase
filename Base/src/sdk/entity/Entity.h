#pragma once
#include "ClientEntity.h"
#include "../../core/Netvar.h"
#include "../../utils/AddressUtils.h"

//LIFESTATE
#define LIFE_ALIVE	 0
#define LIFE_DYING 1
#define LIFE_DEAD	 2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

//Player flags
#define FL_ONGROUND			(1<<0)		// At rest / on the ground
#define FL_DUCKING					(1<<1)		// Player flag -- Player is fully crouched
#define FL_WATERJUMP			(1<<3)		// player jumping out of water
#define FL_ONTRAIN					(1<<4)		// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN						(1<<5)		// Indicates the entity is standing in rain
#define FL_FROZEN					(1<<6)		// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7)		// Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT						(1<<8)		// Is a player
#define FL_FAKECLIENT				(1<<9)		// Fake client, simulated server side; don't send network messages to them
#define FL_INWATER					(1<<10)	// In water

class BaseAttributableItem;
class CSPlayer;

enum MoveTypes
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

class BaseEntity : public ClientEntity
{
public:
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool)
	NETVAR(OwnerEntity, "CBaseEntity->m_hOwnerEntity", BaseHandle)
	NETVAR(ModelIndex, "CBaseEntity->m_nModelIndex", unsigned)
	NETVAR(SimulationTime, "CBaseEntity->m_flSimulationTime", float)

	const char* GetClassName()
	{
		return AddressUtils::Call<const char*>(this, 59);
	}

	void SetModelIndex(const int index)
	{
		AddressUtils::Call<void>(this, 75, index);
	}

	int GetTeam()
	{
		return AddressUtils::Call<int>(this, 88);
	}

	int GetHealth()
	{
		return AddressUtils::Call<int>(this, 122);
	}

	bool IsAlive()
	{
		return AddressUtils::Call<bool>(this, 156);
	}

	bool IsPlayer()
	{
		return AddressUtils::Call<bool>(this, 158);
	}

	bool IsWeapon()
	{
		return AddressUtils::Call<bool>(this, 166);
	}

	void SetSequence(int sequence)
	{
		AddressUtils::Call<void>(this, 218, sequence);
	}

	BaseAttributableItem* GetActiveWeapon()
	{
		return AddressUtils::Call<BaseAttributableItem*>(this, 268);
	}

	Vector GetEyePosition()
	{
		Vector v;
		AddressUtils::Call<void>(this, 285, std::cref(v));
		return v;
	}

	CSPlayer* GetObserverTarget()
	{
		return AddressUtils::Call<CSPlayer*>(this, 294);
	}

	Vector GetAimPunch()
	{
		Vector v;
		AddressUtils::Call<void>(this, 346, std::cref(v));
		return v;
	}

	Matrix3x4* GetBoneMatrix();
	Vector GetBonePosition(int bone);
};

class BaseAnimating : public BaseEntity
{
public:

};

class BaseAnimatingOverlay : public BaseAnimating
{
public:
	NETVAR(Sequence, "CBaseAnimating->m_nSequence", unsigned)
};

class BaseFlex : public BaseAnimatingOverlay
{
public:

};

class BaseCombatCharacter : public BaseFlex
{
public:
	NETVAR(Weapons, "CBaseCombatCharacter->m_hMyWeapons", std::array<unsigned long, 48>)
};

class BasePlayer : public BaseCombatCharacter
{
public:
	NETVAR(Flags, "CBasePlayer->m_fFlags", int)
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vector)
	NETVAR(ViewModel, "CBasePlayer->m_hViewModel[0]", BaseHandle)
	NETVAR(TickBase, "CBasePlayer->m_nTickBase", int)
	NETVAR(MoveType, "CBasePlayer->m_MoveType", int)
};

class CSPlayer : public BasePlayer
{
public:
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool)
	NETVAR(IsDefusing, "CCSPlayer->m_bIsDefusing", bool)
	NETVAR(HasGunGameImmunity, "CCSPlayer->m_bGunGameImmunity", bool)
	NETVAR(Account, "CCSPlayer->m_iAccount", int)
	NETVAR(InBombZone, "CCSPlayer->m_bInBombZone", bool)
	NETVAR(HasDefuser, "CCSPlayer->m_bHasDefuser", bool)
	NETVAR(HasHelmet, "CCSPlayer->m_bHasHelmet", bool)
};

class CSPlayerResource : public BaseEntity
{
public:
	NETVAR(PlayerC4, "CCSPlayerResource->m_iPlayerC4", int)
	NETVAR(PlayerVIP, "CCSPlayerResource->m_iPlayerVIP", int)
	NETVAR(BombsiteCenterA, "CCSPlayerResource->m_bombsiteCenterA", Vector)
	NETVAR(BombsiteCenterB, "CCSPlayerResource->m_bombsiteCenterB", Vector)
};

class BaseCombatWeapon : public BaseEntity
{
public:
	NETVAR(ViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex", int)
	NETVAR(WorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex", int)
	NETVAR(WorldDroppedModelIndex, "CBaseCombatWeapon->m_iWorldDroppedModelIndex", int)
	NETVAR(WeaponWorldModel, "CBaseCombatWeapon->m_hWeaponWorldModel", BaseHandle)
};

class BaseAttributableItem : public BaseCombatWeapon
{
public:
	NETVAR(AccountID, "CBaseAttributableItem->m_iAccountID", int)
	NETVAR(ItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short)
	NETVAR(ItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh", int)
	NETVAR(EntityQuality, "CBaseAttributableItem->m_iEntityQuality", int)
	NETVAR(CustomName, "CBaseAttributableItem->m_szCustomName", char[32])
	NETVAR(FallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit", unsigned)
	NETVAR(FallbackSeed, "CBaseAttributableItem->m_nFallbackSeed", unsigned)
	NETVAR(FallbackWear, "CBaseAttributableItem->m_flFallbackWear", float)
	NETVAR(FallbackStatTrak, "CBaseAttributableItem->m_nFallbackStatTrak", unsigned)
};

class BaseViewModel : public BaseEntity
{
public:
	NETVAR(Owner, "CBaseViewModel->m_hOwner", BaseHandle)
	NETVAR(Weapon, "CBaseViewModel->m_hWeapon", BaseHandle)
	NETPROP(SequenceProp, "CBaseViewModel->m_nSequence")
};