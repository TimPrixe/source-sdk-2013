//========= Copyright © 1996-2003, Valve LLC, All rights reserved. ============
//
// Purpose: This is the incendiary rifle.
//
//=============================================================================

#include "cbase.h"
#include "basecombatweapon.h"
#include "npcevent.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "grenade_ar2.h"
#include "gamerules.h"
#include "game.h"
#include "in_buttons.h"
#include "ai_memory.h"
#include "soundent.h"
#include "hl2_player.h"
#include "EntityFlame.h"
#include "weapon_flaregun.h"
#include "te_effect_dispatch.h"
#include "prop_combine_ball.h"
#include "beam_shared.h"
#include "npc_combine.h"
#include "rumble_shared.h"
#include "gamestats.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar sk_weapon_ar2_alt_fire_radius("sk_weapon_ar2_alt_fire_radius", "10");

//ConVar sk_weapon_ar2_alt_fire_duration("sk_weapon_ar2_alt_fire_duration", "2");

ConVar sk_weapon_ar2_alt_fire_mass("sk_weapon_ar2_alt_fire_mass", "150");

extern ConVar sk_weapon_ar2_alt_fire_duration;

//###########################################################################
//	>> CWeaponIRifle
//###########################################################################

class CWeaponIRifle : public CBaseHLCombatWeapon
{
public:

	CWeaponIRifle();

	DECLARE_SERVERCLASS();
	DECLARE_CLASS(CWeaponIRifle, CBaseHLCombatWeapon);

	void	Precache(void);
	void	ItemPostFrame(void);
	bool	Deploy(void);

	void	PrimaryAttack(void);
	void	DelayedAttack(void);
	virtual float GetFireRate(void) { return 1; };


	int CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone;

		cone = VECTOR_CONE_3DEGREES;

		return cone;
	}

protected:

	float					m_flDelayedFire;
	bool					m_bShotDelayed;
	int						m_nVentPose;

	DECLARE_ACTTABLE();
	DECLARE_DATADESC();
};

BEGIN_DATADESC(CWeaponIRifle)

DEFINE_FIELD(m_flDelayedFire, FIELD_TIME),
DEFINE_FIELD(m_bShotDelayed, FIELD_BOOLEAN),
//DEFINE_FIELD( m_nVentPose, FIELD_INTEGER ),

END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CWeaponIRifle, DT_WeaponIRifle)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_irifle, CWeaponIRifle);
PRECACHE_WEAPON_REGISTER(weapon_irifle);

//---------------------------------------------------------
// Activity table
//---------------------------------------------------------
acttable_t	CWeaponIRifle::m_acttable[] =
{
	{ ACT_RANGE_ATTACK1, ACT_RANGE_ATTACK_ML, true },
};
IMPLEMENT_ACTTABLE(CWeaponIRifle);

//---------------------------------------------------------
// Constructor
//---------------------------------------------------------
CWeaponIRifle::CWeaponIRifle()
{
	m_bReloadsSingly = false;

	m_fMinRange1 = 65;
	m_fMinRange2 = 0;
	m_fMaxRange1 = 2048;
	m_fMaxRange2 = 1024;

//  m_nShotsFired = 0;
	m_nVentPose = -1;
}

//---------------------------------------------------------
//---------------------------------------------------------
void CWeaponIRifle::Precache(void)
{
	BaseClass::Precache();

	UTIL_PrecacheOther("prop_combine_ball");
	UTIL_PrecacheOther("env_entity_dissolver");
}

/*
//---------------------------------------------------------
//---------------------------------------------------------
void CWeaponIRifle::PrimaryAttack( void )
{
CBasePlayer *pOwner = ToBasePlayer( GetOwner() );

if ( pOwner == NULL )
return;

m_iClip1 = m_iClip1 - 1;

SendWeaponAnim( ACT_VM_PRIMARYATTACK );
pOwner->m_flNextAttack = gpGlobals->curtime + 1;

CFlare *pFlare = CFlare::Create( pOwner->Weapon_ShootPosition(), pOwner->EyeAngles(), pOwner, FLARE_DURATION );

if ( pFlare == NULL )
return;

Vector forward;
pOwner->EyeVectors( &forward );

pFlare->SetAbsVelocity( forward * 1500 );

WeaponSound( SINGLE );
}
*/

//-----------------------------------------------------------------------------
// Purpose: Handle grenade detonate in-air (even when no ammo is left)
//-----------------------------------------------------------------------------
void CWeaponIRifle::ItemPostFrame(void)
{
	// See if we need to fire off our secondary round
	if (m_bShotDelayed && gpGlobals->curtime > m_flDelayedFire)
	{
		DelayedAttack();
	}

	BaseClass::ItemPostFrame();
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponIRifle::DelayedAttack(void)
{
	m_bShotDelayed = false;

	CBasePlayer *pOwner = ToBasePlayer(GetOwner());

	if ( pOwner == NULL )
		return;

	m_iClip1 = m_iClip1 - 10;   //1
//	m_iClip1 -= 0;

	// Deplete the clip completely
	SendWeaponAnim( ACT_VM_PRIMARYATTACK );
	m_flNextPrimaryAttack = pOwner->m_flNextAttack = gpGlobals->curtime + SequenceDuration();

	// Register a muzzleflash for the AI
	pOwner->DoMuzzleFlash();
	pOwner->SetMuzzleFlashTime(gpGlobals->curtime + 0.5);

	WeaponSound(WPN_DOUBLE);

	pOwner->RumbleEffect(RUMBLE_SHOTGUN_DOUBLE, 0, RUMBLE_FLAG_RESTART);

	// Fire the bullets
	Vector vecSrc = pOwner->Weapon_ShootPosition();
	Vector vecAiming = pOwner->GetAutoaimVector(AUTOAIM_SCALE_DEFAULT);
	Vector impactPoint = vecSrc + (vecAiming * MAX_TRACE_LENGTH);

	// Fire the bullets
	Vector vecVelocity = vecAiming * 1000.0f;

	// Fire the combine ball
	CreateCombineBall(vecSrc,
		vecVelocity,
		sk_weapon_ar2_alt_fire_radius.GetFloat(),
		sk_weapon_ar2_alt_fire_mass.GetFloat(),
		sk_weapon_ar2_alt_fire_duration.GetFloat(),
		pOwner);

	// View effects
	color32 white = { 255, 255, 255, 64 };
	UTIL_ScreenFade(pOwner, white, 0.1, 0, FFADE_IN);

	//Disorient the player
	QAngle angles = pOwner->GetLocalAngles();

	angles.x += random->RandomInt(-4, 4);
	angles.y += random->RandomInt(-4, 4);
	angles.z = 0;

	pOwner->SnapEyeAngles(angles);

	pOwner->ViewPunch(QAngle(random->RandomInt(-8, -12), random->RandomInt(1, 2), 0));

	//Decrease ammo
	//pOwner->RemoveAmmo(10, m_iPrimaryAmmoType);

	if ( !m_iClip1 && pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 0)
	{
		// HEV suit - indicate out of ammo condition
		pOwner->SetSuitUpdate("!HEV_AMO0", FALSE, 0);

	// Can blow up after a short delay (so have time to release mouse button)
	m_flNextPrimaryAttack = gpGlobals->curtime + 0.5f;     //0.5f

	// Can blow up after a short delay (so have time to release mouse button)
//    m_flNextSecondaryAttack = gpGlobals->curtime + 1.0f;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponIRifle::PrimaryAttack( void )
{
	if (m_bShotDelayed)
		return;

	// Cannot fire underwater
	if (GetOwner() && GetOwner()->GetWaterLevel() == 3)
	{
		SendWeaponAnim(ACT_VM_DRYFIRE);
		BaseClass::WeaponSound(EMPTY);
		m_flNextSecondaryAttack = gpGlobals->curtime + 0.5f;
		return;
	}

	m_bShotDelayed = true;
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = m_flDelayedFire = gpGlobals->curtime + 0.5f;

	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (pPlayer)
	{
		pPlayer->RumbleEffect(RUMBLE_AR2_ALT_FIRE, 0, RUMBLE_FLAG_RESTART);
	}

	SendWeaponAnim(ACT_VM_FIDGET);
	WeaponSound(SINGLE);
//	SendWeaponAnim(ACT_VM_RELOAD);
//	WeaponSound(RELOAD);
}


	/*
//-----------------------------------------------------------------------------
// Purpose: Override if we're waiting to release a shot
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CWeaponIRifle::CanHolster(void)
{
	if (m_bShotDelayed)
		return false;

	return BaseClass::CanHolster();
}
*/

/*
//-----------------------------------------------------------------------------
// Purpose: Override if we're waiting to release a shot
//-----------------------------------------------------------------------------
bool CWeaponIRifle::Reload(void)
{
	if (m_bShotDelayed)
		return false;

	return BaseClass::Reload();
}

*/

//---------------------------------------------------------
// BUGBUG - don't give ammo here.
//---------------------------------------------------------
bool CWeaponIRifle::Deploy(void)
{
	/*
	CBaseCombatCharacter *pOwner  = GetOwner();
	if (pOwner)
	{
	pOwner->GiveAmmo( 90, m_iPrimaryAmmoType);
	}
	*/
	//CBaseCombatCharacter *pOwner = GetOwner();
	//if (!m_iClip1 && pOwner->GetAmmoCount(m_iPrimaryAmmoType) <= 9)
	if (m_iPrimaryAmmoType <= 9)
	{
		return false;
	}

	return BaseClass::Deploy();
}