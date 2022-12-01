//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Things thrown from the hand
//
// Modified: Lox
//=============================================================================//

#include "cbase.h"
#include "player.h"
#include "ammodef.h"
#include "gamerules.h"
#include "grenade_brickbat.h"
#include "weapon_brickbat.h"
#include "soundent.h"
#include "decals.h"
#include "IEffects.h"
#include "engine/IEngineSound.h"
#include "physics_saverestore.h"
#include "props.h"
#include "props_shared.h"
#include "npc_headcrab.h"


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern ConVar sk_plr_dmg_brickbat;

#define BOTTLE_MODEL_NAME "models/props_junk/garbage_glassbottle003a.mdl"


// Global Savedata for changelevel trigger
BEGIN_DATADESC(CGrenade_Brickbat)
DEFINE_FIELD(m_nType, FIELD_INTEGER),
DEFINE_FIELD(m_bExplodes, FIELD_BOOLEAN),
DEFINE_FIELD(m_bBounceToFlat, FIELD_BOOLEAN),

// Function Pointers
DEFINE_ENTITYFUNC(BrickbatTouch),
DEFINE_THINKFUNC(BrickbatThink),

END_DATADESC()

LINK_ENTITY_TO_CLASS(brickbat, CGrenade_Brickbat);

void CGrenade_Brickbat::Spawn(void)
{
	RemoveEffects(EF_NOINTERP);
	SetCollisionGroup(COLLISION_GROUP_PROJECTILE);
	SetTouch(&CGrenade_Brickbat::BrickbatTouch);
	SetThink(&CGrenade_Brickbat::BrickbatThink);
	SetNextThink(gpGlobals->curtime + 0.1f);

	m_takedamage = DAMAGE_YES;
	m_iHealth = 1;

	SetGravity(1.0);
	SetSequence(1);

	CreateVPhysics();
}

bool CGrenade_Brickbat::CreateVPhysics()
{
	VPhysicsInitNormal(SOLID_VPHYSICS, 0, false);
	IPhysicsObject *pPhysics = VPhysicsGetObject();
	if (pPhysics)
	{
		// we want world touches
		unsigned int flags = pPhysics->GetCallbackFlags();
		pPhysics->SetCallbackFlags(flags | CALLBACK_GLOBAL_TOUCH_STATIC);
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CGrenade_Brickbat::BrickbatTouch(CBaseEntity *pOther)
{
	// -----------------------------------------------------------
	// Might be physically simulated so get my velocity manually
	// -----------------------------------------------------------
	Vector vVelocity;
	GetVelocity(&vVelocity, NULL);

	// -----------------------------------
	// Do damage if we moving fairly fast
	// -----------------------------------
	if (vVelocity.Length() > 100)
	{
		if (GetThrower())
		{
			trace_t tr;
			tr = CBaseEntity::GetTouchTrace();
			ClearMultiDamage();
			Vector forward;
			AngleVectors(GetLocalAngles(), &forward);

			CTakeDamageInfo info(this, GetThrower(), m_flDamage, DMG_CRUSH);
			CalculateMeleeDamageForce(&info, forward, tr.endpos);
			pOther->DispatchTraceAttack(info, forward, &tr);
			ApplyMultiDamage();
		}
		// If this thrown item explodes, blow it up
		if (m_bExplodes)
		{
			Detonate();
			return;
		}
	}
	else if (pOther->GetFlags() & FL_CLIENT)
	{
		SpawnBrickbatWeapon();
		return;
	}
}

//------------------------------------------------------------------------------
// Purpose : Brickbat grenade turns back into a brickbat weapon
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CGrenade_Brickbat::SpawnBrickbatWeapon(void)
{
	CWeaponBrickbat *pBrickbat = (CWeaponBrickbat*)CBaseEntity::CreateNoSpawn(
		"weapon_brickbat", GetLocalOrigin(), GetLocalAngles(), NULL);
	// Spawn after we set the ammo type so the correct model is used
	if (pBrickbat)
	{
		pBrickbat->m_iCurrentAmmoType = m_nType;
		pBrickbat->Spawn();
		VPhysicsDestroyObject();
		SetThink(NULL);
		UTIL_Remove(this);

		if (m_bExplodes)
		{
			return;
		}

		if (!m_nType)
		{
			 m_nType = BRICKBAT_HEADCRAB;
		}
	}
}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CGrenade_Brickbat::BrickbatThink(void)
{
	// -----------------------------------------------------------
	// Might be physically simulated so get my velocity manually
	// -----------------------------------------------------------
	Vector vVelocity;
	AngularImpulse vAngVel;
	GetVelocity(&vVelocity, &vAngVel);

	// See if I can lose my owner (has dropper moved out of way?)
	// Want do this so owner can throw the brickbat
	if (GetOwnerEntity())
	{
		trace_t tr;
		Vector	vUpABit = GetAbsOrigin();
		vUpABit.z += 5.0;

		CBaseEntity* saveOwner = GetOwnerEntity();
		SetOwnerEntity(NULL);
		UTIL_TraceEntity(this, GetAbsOrigin(), vUpABit, MASK_SOLID, &tr);
		if (tr.startsolid || tr.fraction != 1.0)
		{
			SetOwnerEntity(saveOwner);
		}
	}

	// ---------------------------------------------------------------
	//	Make sure we're not resting on a living thing's bounding box
	// ---------------------------------------------------------------
	if (vVelocity.Length() < 0.01)
	{
		trace_t tr;
		UTIL_TraceLine(GetAbsOrigin(), GetAbsOrigin() - Vector(0, 0, 10), MASK_SOLID, this, COLLISION_GROUP_NONE, &tr);

		if (tr.fraction < 1.0 && tr.m_pEnt)
		{
			CBaseEntity *pEntity = tr.m_pEnt;
			if (pEntity->GetFlags() & (FL_CLIENT | FL_NPC))
			{
				// --------------------
				// Bounce me off 
				// --------------------
				Vector vNewVel;
				vNewVel.y = 100;
				vNewVel.x = random->RandomInt(-100, 100);
				vNewVel.z = random->RandomInt(-100, 100);

				// If physically simulated
				IPhysicsObject *pPhysicsObject = VPhysicsGetObject();
				if (pPhysicsObject)
				{
					pPhysicsObject->AddVelocity(&vNewVel, &vAngVel);
				}
				// Otherwise
				else
				{
					SetAbsVelocity(vNewVel);
				}
			}
		}
	}

	if (vVelocity.Length() < 0.01)
	{
	//	SpawnBrickbatWeapon(); // VXP: Commented - we don't need this to be here
	}
	SetNextThink(gpGlobals->curtime + 0.1f);
}

//=====================================================================
//	> Rock
//=====================================================================
class CGrenadeRockBB : public CGrenade_Brickbat
{
public:
	DECLARE_CLASS(CGrenadeRockBB, CGrenade_Brickbat);

	void Spawn(void)
	{
		m_nType = BRICKBAT_ROCK;
		SetModel("models/props_junk/Rock001a.mdl");
		BaseClass::Spawn();
	}
	void Precache(void)
	{
		PrecacheModel("models/props_junk/Rock001a.mdl");
		BaseClass::Precache();
	}
};
LINK_ENTITY_TO_CLASS(grenade_rockbb, CGrenadeRockBB);
PRECACHE_REGISTER(grenade_rockbb);


//=====================================================================
//	> BeerBottle
//=====================================================================
class CGrenadeBottle : public CGrenade_Brickbat
//class CGrenadeBottle : public CPhysicsProp
{
public:
	DECLARE_CLASS(CGrenadeBottle, CGrenade_Brickbat);

	void Spawn(void)
	{
		m_nType = BRICKBAT_BOTTLE;

		//Reptile: Create real bottles!
	//	SetMoveType(MOVETYPE_FLYGRAVITY, MOVECOLLIDE_FLY_BOUNCE);
	//	SetSolid(SOLID_VPHYSICS);
	//	SetCollisionGroup(COLLISION_GROUP_BREAKABLE_GLASS);

		m_bExplodes = true;
	//	SetModel("models/weapons/w_bb_bottle.mdl");
//		SetThink(&CGrenadeBottle::Detonate);
		//int damageType = DMG_SLASH;
	//	float damage = 50;
	//	int radius = 250;
	//	SetDamage(damage);
	//	SetExplosiveRadius(radius);
		//SetTouch(&CBreakableProp::BreakablePropTouch);

	//	PrecacheModel(szModel);
		char *szModel = (char *)STRING(GetModelName());
		if (!szModel || !*szModel)
		{
			szModel = BOTTLE_MODEL_NAME;
			SetModelName(AllocPooledString(szModel));
		}

		SetModel(szModel);
		Precache();
		
	//	RadiusDamage(CTakeDamageInfo(this, pOwner, sk_plr_dmg_brickbat.GetFloat(), DMG_SLASH), GetAbsOrigin(), 10, CLASS_NONE, NULL);
	//	SetDamage(sk_plr_dmg_brickbat.GetFloat());
	//	Spawn();

	//	SetCollisionGroup(collisionGroup);
	//	cFlag = BREAK_GLASS;

	//	CPhysicsProp *pBottle = (CPhysicsProp*)CBaseEntity::Create("prop_physics", vecSrc, pPlayer->EyeAngles(), pOwner);

	//	pBottle->SetDamage(sk_plr_dmg_brickbat.GetFloat());
	//	pBottle->SetOwnerEntity(pOwner);

	//	SetTouch(&CGrenade_Brickbat::BrickbatTouch);

		BaseClass::Spawn();

	//	BaseClass::Activate();
	}

	void Precache(void);
	void Detonate(void);
//	void SpawnBrickbatWeapon(void);

};

void CGrenadeBottle::Precache(void)
{
	//PrecacheModel("models/weapons/w_bb_bottle.mdl");

//	PrecacheModel(STRING(GetModelName()));
	PrecacheModel("models/props_junk/garbage_glassbottle003a.mdl");
	PrecacheModel("models/props_junk/garbage_glassbottle003a_chunk01.mdl");
	PrecacheModel("models/props_junk/garbage_glassbottle003a_chunk02.mdl");
	PrecacheModel("models/props_junk/garbage_glassbottle003a_chunk03.mdl");

	UTIL_PrecacheOther("prop_physics");

//	m_iNumBreakableChunks = PropBreakablePrecacheAll(GetModelName());

	PrecacheScriptSound("GrenadeBottle.Detonate");

	BaseClass::Precache();
}


void CGrenadeBottle::Detonate(void)
{
	trace_t trace;

	UTIL_TraceLine(GetAbsOrigin(), GetAbsOrigin() + GetAbsVelocity(), MASK_SOLID, this, COLLISION_GROUP_NONE, &trace);
	UTIL_DecalTrace(&trace, "BeerSplash");

	//SetThink(&CBreakableProp::BreakThink);
	//SetTouch(&CBreakableProp::BreakablePropTouch);

	//AddSolidFlags(FSOLID_NOT_SOLID);


//	SetThink(&CGrenadeBottle::Detonate);

//	SetTouch(&CBreakableProp::BreakablePropTouch);

//	EmitSound("GrenadeBottle.Detonate");

//	CSoundEnt::InsertSound(SOUND_COMBAT, GetAbsOrigin(), 400, 0.5);

//	UTIL_Remove(this);

//	SetModel("models/props_junk/glassbottle01a_chunk01a.mdl");
//	SetModel("models/props_junk/glassbottle01a_chunk01a.mdl");

//	SetLocalOrigin( GetLocalOrigin() );
//	SetLocalAngles( GetLocalAngles() );
}



LINK_ENTITY_TO_CLASS(grenade_beerbottle, CGrenadeBottle);
PRECACHE_REGISTER(grenade_beerbottle);


//=====================================================================
//	> HeadCrab
//=====================================================================
//class CGrenadeHeadCrab : public CGrenade_Brickbat
class CGrenadeHeadCrab : public CFastHeadcrab
{
public:
	DECLARE_CLASS(CGrenadeHeadCrab, CFastHeadcrab);

	void Spawn(void);
	void Precache(void);
//	int m_nHeadcrabType;
};

/*
static const char *s_pHeadcrabClass[] =
{
	"npc_headcrab_fast",
};
*/

void CGrenadeHeadCrab::Spawn(void)
{	
	//	m_bExplodes	= false;
	//	SetModel( "models/hc_squashed01.mdl" );
//	CBaseEntity *pEnt = CreateEntityByName(s_pHeadcrabClass[m_nHeadcrabType]);
//	CFastHeadcrab *pHeadCrab = assert_cast<CFastHeadcrab*>(pEnt);
//	SetOwnerEntity(((CFastHeadcrab*)pOwner));
	Precache();
	SetModel("models/headcrab.mdl");
//	SetOwnerEntity(pOwner);
//	m_pOwner = pOwner;
//	Precache();
	BaseClass::Spawn();
	//	SetMoveType( MOVETYPE_STEP );
}

void CGrenadeHeadCrab::Precache(void)
{
	//	engine->PrecacheModel("models/hc_squashed01.mdl");
	engine->PrecacheModel("models/headcrab.mdl");
	UTIL_PrecacheOther("npc_headcrab_fast");
	// UTIL_PrecacheOther(s_pHeadcrabClass[m_nHeadcrabType]);
	BaseClass::Precache();
}

LINK_ENTITY_TO_CLASS(grenade_headcrab, CGrenadeHeadCrab);
PRECACHE_REGISTER(grenade_headcrab);


//=====================================================================
//	> CrematorHead
//=====================================================================
class CGrenadeCrematorHead : public CGrenade_Brickbat
{
public:
	DECLARE_CLASS(CGrenadeCrematorHead, CGrenade_Brickbat);

	void Spawn(void);
	void Precache(void);
	void TraceAttack(const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr);
};

//-----------------------------------------------------------------------------
// Purpose:
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CGrenadeCrematorHead::TraceAttack(const CTakeDamageInfo &info, const Vector &vecDir, trace_t *ptr)
{
	if (info.GetDamageType() & DMG_BULLET)
	{
		g_pEffects->Ricochet(ptr->endpos, ptr->plane.normal);
	}
	BaseClass::TraceAttack(info, vecDir, ptr);
}

void CGrenadeCrematorHead::Spawn(void)
{
	m_nType = BRICKBAT_CREMATORHEAD;
	m_bExplodes = false;
	SetModel("models/cremator_head.mdl");
	BaseClass::Spawn();
	SetMoveType(MOVETYPE_VPHYSICS);		// uses physics
}

void CGrenadeCrematorHead::Precache(void)
{
	engine->PrecacheModel("models/cremator_head.mdl");
	BaseClass::Precache();
}

LINK_ENTITY_TO_CLASS(grenade_crematorhead, CGrenadeCrematorHead);
PRECACHE_REGISTER(grenade_crematorhead);


/*
//=====================================================================
//	> CrematorHead
//=====================================================================
class CCrematorHeadBB : public CGrenade_Brickbat
{
public:
	DECLARE_CLASS(CCrematorHeadBB, CGrenade_Brickbat);

	void Spawn(void)
	{
		m_nType = BRICKBAT_CREMATORHEAD;
		SetModel("models/cremator_head.mdl");
		BaseClass::Spawn();
	}
	void Precache(void)
	{
		PrecacheModel("models/cremator_head.mdl");
		BaseClass::Precache();
	}
};
LINK_ENTITY_TO_CLASS(grenade_crematorhead, CCrematorHeadBB);
PRECACHE_REGISTER(grenade_crematorhead);
*/