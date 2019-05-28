#pragma once
#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_ANIMDUCKING			(1<<2)	// Player flag -- Player is in the process of crouching or uncrouching but could be in transition
// examples:                                   Fully ducked:  FL_DUCKING &  FL_ANIMDUCKING
//           Previously fully ducked, unducking in progress:  FL_DUCKING & !FL_ANIMDUCKING
//                                           Fully unducked: !FL_DUCKING & !FL_ANIMDUCKING
//           Previously fully unducked, ducking in progress: !FL_DUCKING &  FL_ANIMDUCKING
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER				(1<<10)	// In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		11

#define	FL_FLY					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<12)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<13)
#define	FL_NPC					(1<<14)
#define	FL_GODMODE				(1<<15)
#define	FL_NOTARGET				(1<<16)
#define	FL_AIMTARGET			(1<<17)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<18)	// not all corners are valid
#define FL_STATICPROP			(1<<19)	// Eetsa static prop!		
#define FL_GRAPHED				(1<<20) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<21)
#define FL_STEPMOVEMENT			(1<<22)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<23)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<24)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<25)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<26) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<27)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<28)	// You know...
#define FL_DISSOLVING			(1<<29) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<30) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<31) // pusher that can't be blocked by the player

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)

enum client_class_ids
{
	CAI_BaseNPC = 0,
	ID_CAK47,
	ID_CBaseAnimating,
	ID_CBaseAnimatingOverlay,
	ID_CBaseAttributableItem,
	ID_CBaseButton,
	ID_CBaseCombatCharacter,
	ID_CBaseCombatWeapon,
	ID_CBaseCSGrenade,
	ID_CBaseCSGrenadeProjectile,
	ID_CBaseDoor,
	ID_CBaseEntity,
	ID_CBaseFlex,
	ID_CBaseGrenade,
	ID_CBaseParticleEntity,
	ID_CBasePlayer,
	ID_CBasePropDoor,
	ID_CBaseTeamObjectiveResource,
	ID_CBaseTempEntity,
	ID_CBaseToggle,
	ID_CBaseTrigger,
	ID_CBaseViewModel,
	ID_CBaseVPhysicsTrigger,
	ID_CBaseWeaponWorldModel,
	ID_CBeam,
	ID_CBeamSpotlight,
	ID_CBoneFollower,
	ID_CBRC4Target,
	ID_CBreachCharge,
	ID_CBreachChargeProjectile,
	ID_CBreakableProp,
	ID_CBreakableSurface,
	ID_CC4,
	ID_CCascadeLight,
	ID_CChicken,
	ID_CColorCorrection,
	ID_CColorCorrectionVolume,
	ID_CCSGameRulesProxy,
	ID_CCSPlayer,
	ID_CCSPlayerResource,
	ID_CCSRagdoll,
	ID_CCSTeam,
	ID_CDangerZone,
	ID_CDangerZoneController,
	ID_CDEagle,
	ID_CDecoyGrenade,
	ID_CDecoyProjectile,
	ID_CDrone,
	ID_CDronegun,
	ID_CDynamicLight,
	ID_CDynamicProp,
	ID_CEconEntity,
	ID_CEconWearable,
	ID_CEmbers,
	ID_CEntityDissolve,
	ID_CEntityFlame,
	ID_CEntityFreezing,
	ID_CEntityParticleTrail,
	ID_CEnvAmbientLight,
	ID_CEnvDetailController,
	ID_CEnvDOFController,
	ID_CEnvGasCanister,
	ID_CEnvParticleScript,
	ID_CEnvProjectedTexture,
	ID_CEnvQuadraticBeam,
	ID_CEnvScreenEffect,
	ID_CEnvScreenOverlay,
	ID_CEnvTonemapController,
	ID_CEnvWind,
	ID_CFEPlayerDecal,
	ID_CFireCrackerBlast,
	ID_CFireSmoke,
	ID_CFireTrail,
	ID_CFish,
	ID_CFists,
	ID_CFlashbang,
	ID_CFogController,
	ID_CFootstepControl,
	ID_CFunc_Dust,
	ID_CFunc_LOD,
	ID_CFuncAreaPortalWindow,
	ID_CFuncBrush,
	ID_CFuncConveyor,
	ID_CFuncLadder,
	ID_CFuncMonitor,
	ID_CFuncMoveLinear,
	ID_CFuncOccluder,
	ID_CFuncReflectiveGlass,
	ID_CFuncRotating,
	ID_CFuncSmokeVolume,
	ID_CFuncTrackTrain,
	ID_CGameRulesProxy,
	ID_CGrassBurn,
	ID_CHandleTest,
	ID_CHEGrenade,
	ID_CHostage,
	ID_CHostageCarriableProp,
	ID_CIncendiaryGrenade,
	ID_CInferno,
	ID_CInfoLadderDismount,
	ID_CInfoMapRegion,
	ID_CInfoOverlayAccessor,
	ID_CItem_Healthshot,
	ID_CItemCash,
	ID_CItemDogtags,
	ID_CKnife,
	ID_CKnifeGG,
	ID_CLightGlow,
	ID_CMaterialModifyControl,
	ID_CMelee,
	ID_CMolotovGrenade,
	ID_CMolotovProjectile,
	ID_CMovieDisplay,
	ID_CParadropChopper,
	ID_CParticleFire,
	ID_CParticlePerformanceMonitor,
	ID_CParticleSystem,
	ID_CPhysBox,
	ID_CPhysBoxMultiplayer,
	ID_CPhysicsProp,
	ID_CPhysicsPropMultiplayer,
	ID_CPhysMagnet,
	ID_CPhysPropAmmoBox,
	ID_CPhysPropLootCrate,
	ID_CPhysPropRadarJammer,
	ID_CPhysPropWeaponUpgrade,
	ID_CPlantedC4,
	ID_CPlasma,
	ID_CPlayerResource,
	ID_CPointCamera,
	ID_CPointCommentaryNode,
	ID_CPointWorldText,
	ID_CPoseController,
	ID_CPostProcessController,
	ID_CPrecipitation,
	ID_CPrecipitationBlocker,
	ID_CPredictedViewModel,
	ID_CProp_Hallucination,
	ID_CPropCounter,
	ID_CPropDoorRotating,
	ID_CPropJeep,
	ID_CPropVehicleDriveable,
	ID_CRagdollManager,
	ID_CRagdollProp,
	ID_CRagdollPropAttached,
	ID_CRopeKeyframe,
	ID_CSCAR17,
	ID_CSceneEntity,
	ID_CSensorGrenade,
	ID_CSensorGrenadeProjectile,
	ID_CShadowControl,
	ID_CSlideshowDisplay,
	ID_CSmokeGrenade,
	ID_CSmokeGrenadeProjectile,
	ID_CSmokeStack,
	ID_CSpatialEntity,
	ID_CSpotlightEnd,
	ID_CSprite,
	ID_CSpriteOriented,
	ID_CSpriteTrail,
	ID_CStatueProp,
	ID_CSteamJet,
	ID_CSun,
	ID_CSunlightShadowControl,
	ID_CSurvivalSpawnChopper,
	ID_CTablet,
	ID_CTeam,
	ID_CTeamplayRoundBasedRulesProxy,
	ID_CTEArmorRicochet,
	ID_CTEBaseBeam,
	ID_CTEBeamEntPoint,
	ID_CTEBeamEnts,
	ID_CTEBeamFollow,
	ID_CTEBeamLaser,
	ID_CTEBeamPoints,
	ID_CTEBeamRing,
	ID_CTEBeamRingPoint,
	ID_CTEBeamSpline,
	ID_CTEBloodSprite,
	ID_CTEBloodStream,
	ID_CTEBreakModel,
	ID_CTEBSPDecal,
	ID_CTEBubbles,
	ID_CTEBubbleTrail,
	ID_CTEClientProjectile,
	ID_CTEDecal,
	ID_CTEDust,
	ID_CTEDynamicLight,
	ID_CTEEffectDispatch,
	ID_CTEEnergySplash,
	ID_CTEExplosion,
	ID_CTEFireBullets,
	ID_CTEFizz,
	ID_CTEFootprintDecal,
	ID_CTEFoundryHelpers,
	ID_CTEGaussExplosion,
	ID_CTEGlowSprite,
	ID_CTEImpact,
	ID_CTEKillPlayerAttachments,
	ID_CTELargeFunnel,
	ID_CTEMetalSparks,
	ID_CTEMuzzleFlash,
	ID_CTEParticleSystem,
	ID_CTEPhysicsProp,
	ID_CTEPlantBomb,
	ID_CTEPlayerAnimEvent,
	ID_CTEPlayerDecal,
	ID_CTEProjectedDecal,
	ID_CTERadioIcon,
	ID_CTEShatterSurface,
	ID_CTEShowLine,
	ID_CTesla,
	ID_CTESmoke,
	ID_CTESparks,
	ID_CTESprite,
	ID_CTESpriteSpray,
	ID_CTest_ProxyToggle_Networkable,
	ID_CTestTraceline,
	ID_CTEWorldDecal,
	ID_CTriggerPlayerMovement,
	ID_CTriggerSoundOperator,
	ID_CVGuiScreen,
	ID_CVoteController,
	ID_CWaterBullet,
	ID_CWaterLODControl,
	ID_CWeaponAug,
	ID_CWeaponAWP,
	ID_CWeaponBaseItem,
	ID_CWeaponBizon,
	ID_CWeaponCSBase,
	ID_CWeaponCSBaseGun,
	ID_CWeaponCycler,
	ID_CWeaponElite,
	ID_CWeaponFamas,
	ID_CWeaponFiveSeven,
	ID_CWeaponG3SG1,
	ID_CWeaponGalil,
	ID_CWeaponGalilAR,
	ID_CWeaponGlock,
	ID_CWeaponHKP2000,
	ID_CWeaponM249,
	ID_CWeaponM3,
	ID_CWeaponM4A1,
	ID_CWeaponMAC10,
	ID_CWeaponMag7,
	ID_CWeaponMP5Navy,
	ID_CWeaponMP7,
	ID_CWeaponMP9,
	ID_CWeaponNegev,
	ID_CWeaponNOVA,
	ID_CWeaponP228,
	ID_CWeaponP250,
	ID_CWeaponP90,
	ID_CWeaponSawedoff,
	ID_CWeaponSCAR20,
	ID_CWeaponScout,
	ID_CWeaponSG550,
	ID_CWeaponSG552,
	ID_CWeaponSG556,
	ID_CWeaponSSG08,
	ID_CWeaponTaser,
	ID_CWeaponTec9,
	ID_CWeaponTMP,
	ID_CWeaponUMP45,
	ID_CWeaponUSP,
	ID_CWeaponXM1014,
	ID_CWorld,
	ID_CWorldVguiText,
	ID_DustTrail,
	ID_MovieExplosion,
	ID_ParticleSmokeGrenade,
	ID_RocketTrail,
	ID_SmokeTrail,
	ID_SporeExplosion,
	ID_SporeTrail,
};
enum life_state {
	LIFE_ALIVE = 0,// alive
	LIFE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
	LIFE_DEAD = 2 // dead. lying still.
};

enum button_code_t //https://www.unknowncheats.me/forum/counterstrike-global-offensive/273081-getkeystate-getasynckeystate.html
{

	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,				// A fake button which is 'pressed' and 'released' when the wheel is moved up
	MOUSE_WHEEL_DOWN,			// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

};

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

////////////////
//	PISTOLS	 //
//////////////
#define USP			((_stride == 32) && (_num_vertices == 2503) && (_prim_count == 2018))
#define USP_MAG		((_stride == 32) && (_num_vertices == 180) && (_prim_count == 190))
#define P2000		((_stride == 32) && (_num_vertices == 1310) && (_prim_count == 1010))
#define GLOCK		((_stride == 32) && (_num_vertices == 2369) && (_prim_count == 2463))
#define GLOCK_MAG	((_stride == 32) && (_num_vertices == 290) && (_prim_count == 320))
#define DUALIES		((_stride == 32) && (_num_vertices == 2354) && (_prim_count == 2037))
#define DUALIES_2	((_stride == 32) && (_num_vertices == 2332) && (_prim_count == 2037))
#define FIVESEVEN	((_stride == 32) && (_num_vertices == 1426) && (_prim_count == 1175))
#define P250		((_stride == 32) && (_num_vertices == 1766) && (_prim_count == 1389))
#define REVOLVER	((_stride == 32) && (_num_vertices == 3693) && (_prim_count == 3202))
#define CZ75		((_stride == 32) && (_num_vertices == 4634) && (_prim_count == 3979))
#define CZ75_MAG	((_stride == 32) && (_num_vertices == 1074) && (_prim_count == 1012))
#define CZ75_MAG2	((_stride == 32) && (_num_vertices == 1685) && (_prim_count == 2036))
#define DEAGLE		((_stride == 32) && (_num_vertices == 2140) && (_prim_count == 1519))
#define DEAGLE_MAG	((_stride == 32) && (_num_vertices == 112) && (_prim_count == 68))
#define TEC9		((_stride == 32) && (_num_vertices == 2847) && (_prim_count == 2871))
#define TEC9_MAG	((_stride == 32) && (_num_vertices == 170) && (_prim_count == 122))

#define PISTOL		(USP || USP_MAG || P2000 || GLOCK || GLOCK_MAG || DUALIES \
					|| DUALIES_2 || FIVESEVEN || P250 || REVOLVER || CZ75 || CZ75_MAG || CZ75_MAG2 \
					|| DEAGLE || DEAGLE_MAG || TEC9 || TEC9_MAG)

	//////////////
	//	RIFLES	//
	//////////////

#define AK47		((_stride == 32) && (_num_vertices == 3661) && (_prim_count == 3137))
#define AK47_MAG	((_stride == 32) && (_num_vertices == 125) && (_prim_count == 113))
#define M4A4		((_stride == 32) && (_num_vertices == 2770) && (_prim_count == 1924))
#define M4A4_MAG	((_stride == 32) && (_num_vertices == 100) && (_prim_count == 68))
#define M4A1		((_stride == 32) && (_num_vertices == 8218) && (_prim_count == 6797))
#define M4A1_2		((_stride == 32) && (_num_vertices == 133) && (_prim_count == 116))
#define M4A1_MAG	((_stride == 32) && (_num_vertices == 821) && (_prim_count == 563))
#define FAMAS		((_stride == 32) && (_num_vertices == 3633) && (_prim_count == 3105))
#define FAMAS_MAG	((_stride == 32) && (_num_vertices == 150) && (_prim_count == 114))
#define GALIL		((_stride == 32) && (_num_vertices == 4131) && (_prim_count == 2929))
#define GALIL_MAG	((_stride == 32) && (_num_vertices == 166) && (_prim_count == 90))
#define AWP			((_stride == 32) && (_num_vertices == 3685) && (_prim_count == 3382))
#define AWP_MAG		((_stride == 32) && (_num_vertices == 32) && (_prim_count == 20))
#define SCOUT		((_stride == 32) && (_num_vertices == 2899) && (_prim_count == 2284))
#define SCOUT_SCOPE	((_stride == 32) && (_num_vertices == 1746) && (_prim_count == 1768))
#define AUG			((_stride == 32) && (_num_vertices == 1941) && (_prim_count == 1676))
#define AUG_SCOPE	((_stride == 32) && (_num_vertices == 3123) && (_prim_count == 3187))
#define AUG_MAG		((_stride == 32) && (_num_vertices == 92) && (_prim_count == 88))
#define SIG			((_stride == 32) && (_num_vertices == 4375) && (_prim_count == 3398))
#define SIG_MAG		((_stride == 32) && (_num_vertices == 104) && (_prim_count == 68))
#define SCAR20		((_stride == 32) && (_num_vertices == 4557) && (_prim_count == 3049))
#define SCAR20_MAG	((_stride == 32) && (_num_vertices == 48) && (_prim_count == 28))
#define G3SG1		((_stride == 32) && (_num_vertices == 3411) && (_prim_count == 2782))
#define G3SG1_MAG	((_stride == 32) && (_num_vertices == 82) && (_prim_count == 46))

#define RIFLE		AK47 || AK47_MAG || M4A4 || M4A4_MAG || M4A1 || M4A1_2 || M4A1_MAG || FAMAS \
					|| FAMAS_MAG || GALIL || GALIL_MAG || AWP || AWP_MAG || SCOUT || SCOUT_SCOPE \
					|| AUG || AUG_SCOPE || AUG_MAG || SIG || SIG_MAG || SCAR20 || SCAR20_MAG || G3SG1 \
					|| G3SG1_MAG

//////////////
//	HEAVY	//
//////////////

#define MAG7		((_stride == 32) && (_num_vertices == 2128) && (_prim_count == 1769))
#define MAG7_MAG	((_stride == 32) && (_num_vertices == 152) && (_prim_count == 70))
#define NOVA		((_stride == 32) && (_num_vertices == 2258) && (_prim_count == 2033))
#define SHELLS		((_stride == 32) && (_num_vertices == 31) && (_prim_count == 26))
#define SAWEDOFF	((_stride == 32) && (_num_vertices == 2217) && (_prim_count == 2520))
#define XM1014		((_stride == 32) && (_num_vertices == 3796) && (_prim_count == 3149))
#define M249		((_stride == 32) && (_num_vertices == 4280) && (_prim_count == 3152))
#define M249_MAG	((_stride == 32) && (_num_vertices == 388) && (_prim_count == 260))	
#define NEGEV		((_stride == 32) && (_num_vertices == 4122) && (_prim_count == 2946))
#define NEGEV_MAG	((_stride == 32) && (_num_vertices == 430) && (_prim_count == 378))

#define HEAVY		MAG7 || MAG7_MAG || NOVA || SHELLS || SAWEDOFF || XM1014 || M249 || M249_MAG \
					|| NEGEV || NEGEV_MAG

//////////////
//	HEAVY	//
//////////////

#define MAC10		((_stride == 32) && (_num_vertices == 2729) && (_prim_count == 2870))	
#define MAC10_MAG	((_stride == 32) && (_num_vertices == 244) && (_prim_count == 186))	
#define MP7			((_stride == 32) && (_num_vertices == 4485) && (_prim_count == 3155))
#define MP7_MAG		((_stride == 32) && (_num_vertices == 202) && (_prim_count == 147))	
#define MP9			((_stride == 32) && (_num_vertices == 3851) && (_prim_count == 3143))	
#define MP9_MAG		((_stride == 32) && (_num_vertices == 212) && (_prim_count == 164))	
#define MP5			((_stride == 32) && (_num_vertices == 4230) && (_prim_count == 4674))	
#define MP5_MAG		((_stride == 32) && (_num_vertices == 231) && (_prim_count == 212))	
#define BIZON		((_stride == 32) && (_num_vertices == 3398) && (_prim_count == 2921))	
#define BIZON_MAG	((_stride == 32) && (_num_vertices == 602) && (_prim_count == 460))	
#define P90			((_stride == 32) && (_num_vertices == 4480) && (_prim_count == 3888))	
#define P90_MAG		((_stride == 32) && (_num_vertices == 225) && (_prim_count == 179))	
#define UMP			((_stride == 32) && (_num_vertices == 3152) && (_prim_count == 2306))	
#define UMP_MAG		((_stride == 32) && (_num_vertices == 128) && (_prim_count == 66))	

#define SMG			MAC10 || MAC10_MAG || MP7 || MP7_MAG || MP9 || MP9_MAG || MP5 \
					|| MP5_MAG || BIZON || BIZON_MAG || P90 || P90_MAG || UMP || UMP_MAG


#define WEAPON		PISTOL || RIFLE || HEAVY || SMG

//////////////////
//	GRENADES	//
//////////////////

#define SMOKE_1 ((_stride == 144) && (_num_vertices == 280) && (_prim_count == 140))
#define SMOKE_2 ((_stride == 144) && (_num_vertices == 416) && (_prim_count == 208))

#define SMOKE	SMOKE_1 || SMOKE_2


#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100


enum move_type_t
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


enum class cs_weapon_type_t : int
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,	
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

#define MAX_SHOOT_SOUNDS 16
#define MAX_WEAPON_STRING 80
#define MAX_WEAPON_PREFIX 16
#define MAX_WEAPON_AMMO_NAME 32

enum weapon_sound_t
{
	EMPTY,
	SINGLE,
	SINGLE_NPC,
	WPN_DOUBLE,
	DOUBLE_NPC,
	BURST,
	RELOAD,
	RELOAD_NPC,
	MELEE_MISS,
	MELEE_HIT,
	MELEE_HIT_WORLD,
	SPECIAL1,
	SPECIAL2,
	SPECIAL3,
	TAUNT,
	FAST_RELOAD,
	REVERSE_THE_NEW_SOUND,
	NUM_SHOOT_SOUND_TYPES,
};