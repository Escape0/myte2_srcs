#pragma once

#include "../gamelib/RaceData.h"
#include "../gamelib/ActorInstance.h"
#ifdef ENABLE_ACCE_SYSTEM
#include "../eterlib/GrpObjectInstance.h"
#endif

#include "AffectFlagContainer.h"

class CInstanceBase
{	
	public:
		struct SCreateData
		{
			BYTE	m_bType;
			DWORD	m_dwStateFlags;
			DWORD	m_dwEmpireID;
			DWORD	m_dwGuildID;
			DWORD	m_dwLevel;
			DWORD	m_dwVID;
			DWORD	m_dwRace;
			DWORD	m_dwMovSpd;
			DWORD	m_dwAtkSpd;
			LONG	m_lPosX;
			LONG	m_lPosY;
			FLOAT	m_fRot;
			DWORD	m_dwArmor;
			DWORD	m_dwWeapon;
			DWORD	m_dwHair;
#ifdef ENABLE_ACCE_SYSTEM
			DWORD	m_dwSash;
#endif
			DWORD	m_dwMountVnum;
			
#ifdef ENABLE_ALIGNMENT_SYSTEM
			long long m_sAlignment;
#else
			short	m_sAlignment;
#endif
			BYTE	m_byPKMode;
#if defined(ENABLE_BATTLE_ZONE_SYSTEM)
			BYTE	combat_zone_rank;
			DWORD	combat_zone_points;
#endif
#ifdef ENABLE_BUFFI_SYSTEM
			bool	is_support_shaman;
#endif
#ifdef ENABLE_GUILD_LEADER_SYSTEM
			BYTE	m_bMemberType;
#endif
#if defined(WJ_SHOW_MOB_INFO)
			DWORD	m_dwAIFlag;
#endif
#ifdef ENABLE_WEAPON_RARITY_SYSTEM
			DWORD	m_dwWeaponRareLv;
#endif
#ifdef ENABLE_EFFECT_STONE_SYSTEM
			DWORD	m_dwStoneEffect;
			DWORD	m_dwWeaponStoneEffect;
#endif
#ifdef ENABLE_AURA_SYSTEM
			DWORD	m_dwAura;
#endif
#ifdef ENABLE_QUIVER_SYSTEM
			DWORD	m_dwArrow;
#endif
			CAffectFlagContainer	m_kAffectFlags;

			std::string m_stName;

			bool	m_isMain;
		};

	public:
		typedef DWORD TType;

		enum EDirection
		{
			DIR_NORTH,
			DIR_NORTHEAST,
			DIR_EAST,
			DIR_SOUTHEAST,
			DIR_SOUTH,
			DIR_SOUTHWEST,
			DIR_WEST,
			DIR_NORTHWEST,
			DIR_MAX_NUM,
		};

		enum
		{
			FUNC_WAIT,
			FUNC_MOVE,
			FUNC_ATTACK,
			FUNC_COMBO,
			FUNC_MOB_SKILL,
			FUNC_EMOTION,
			FUNC_SKILL = 0x80,
		};

		enum
		{
			AFFECT_YMIR,
			AFFECT_INVISIBILITY,
			AFFECT_SPAWN,

			AFFECT_POISON,
			AFFECT_SLOW,
			AFFECT_STUN,

			AFFECT_DUNGEON_READY,			// �������� �غ� ����
			AFFECT_SHOW_ALWAYS,				// AFFECT_DUNGEON_UNIQUE ���� ����(Ŭ���̾�Ʈ���� �ø���������)

			AFFECT_BUILDING_CONSTRUCTION_SMALL,
			AFFECT_BUILDING_CONSTRUCTION_LARGE,
			AFFECT_BUILDING_UPGRADE,

			AFFECT_MOV_SPEED_POTION,		// 11
			AFFECT_ATT_SPEED_POTION,		// 12

			AFFECT_FISH_MIND,				// 13
			AFFECT_JEONGWI,					// 14 ����ȥ
			AFFECT_GEOMGYEONG,				// 15 �˰�
			AFFECT_CHEONGEUN,				// 16 õ����
			AFFECT_GYEONGGONG,				// 17 �����
			AFFECT_EUNHYEONG,				// 18 ������
			AFFECT_GWIGEOM,					// 19 �Ͱ�
			AFFECT_GONGPO,					// 20 ����
			AFFECT_JUMAGAP,					// 21 �ָ���
			AFFECT_HOSIN,					// 22 ȣ��
			AFFECT_BOHO,					// 23 ��ȣ
			AFFECT_KWAESOK,					// 24 ���
		    AFFECT_HEUKSIN,					// 25 ��ż�ȣ
			AFFECT_MUYEONG,					// 26 ������
			AFFECT_REVIVE_INVISIBILITY,		// 27 ��Ȱ ����
			AFFECT_FIRE,					// 28 ���� ��
			AFFECT_GICHEON,					// 29 ��õ ���
			AFFECT_JEUNGRYEOK,				// 30 ���¼� 
			AFFECT_DASH,					// 31 �뽬
			AFFECT_PABEOP,					// 32 �Ĺ���
			AFFECT_FALLEN_CHEONGEUN,		// 33 �ٿ� �׷��̵� õ����
			AFFECT_POLYMORPH,				// 34 ��������
			AFFECT_WAR_FLAG1,				// 35
			AFFECT_WAR_FLAG2,				// 36
			AFFECT_WAR_FLAG3,				// 37
			AFFECT_CHINA_FIREWORK,			// 38
			AFFECT_PREMIUM_SILVER,			// 39
			AFFECT_PREMIUM_GOLD,			// 40
			AFFECT_RAMADAN_RING,			// 41 �ʽ´� ���� ���� Affect
			AFFECT_BLEEDING,				// 42
			AFFECT_RED_POSSESION,			// 43
			AFFECT_BLUE_POSSESION,			// 44

#ifdef ENABLE_MELEY_LAIR_DUNGEON
			AFFECT_STATUE1,
			AFFECT_STATUE2,
			AFFECT_STATUE3,
			AFFECT_STATUE4,
#endif

#ifdef ENABLE_YOUTUBER_SYSTEM
			AFFECT_YOUTUBER,
			AFFECT_TWITCH,
#endif

#ifdef ENABLE_DRAGON_SOUL_ACTIVE_EFFECT
			AFFECT_DRAGON_SOUL,
#endif
			
#ifdef ENABLE_WIND_SHOES_RENEWAL
			AFFECT_WIND_SHOES,
#endif

#ifdef ENABLE_AFK_MODE_SYSTEM
			AFFECT_AFK,
#endif

#ifdef ENABLE_VALUE_PACK_SYSTEM
			AFFECT_PREMIUM,
#endif

#ifdef ENABLE_ITEM_SOUL_SYSTEM
			AFFECT_RED_SOUL,
			AFFECT_BLUE_SOUL,
			AFFECT_MIX_SOUL,
#endif

#ifdef ENABLE_KING_GUILD_SYSTEM
			AFFECT_KING_GUILD,
#endif

			AFFECT_NUM = 64,

			AFFECT_HWAYEOM = AFFECT_GEOMGYEONG,
		};

		enum
		{
			NEW_AFFECT_MOV_SPEED            = 200,
			NEW_AFFECT_ATT_SPEED,
			NEW_AFFECT_ATT_GRADE,
			NEW_AFFECT_INVISIBILITY,
			NEW_AFFECT_STR,
			NEW_AFFECT_DEX,                 // 205
			NEW_AFFECT_CON,
			NEW_AFFECT_INT,
			NEW_AFFECT_FISH_MIND_PILL,

			NEW_AFFECT_POISON,
			NEW_AFFECT_STUN,                // 210
			NEW_AFFECT_SLOW,
			NEW_AFFECT_DUNGEON_READY,
			NEW_AFFECT_DUNGEON_UNIQUE,

			NEW_AFFECT_BUILDING,
			NEW_AFFECT_REVIVE_INVISIBLE,    // 215
			NEW_AFFECT_FIRE,
			NEW_AFFECT_CAST_SPEED,
			NEW_AFFECT_HP_RECOVER_CONTINUE,
			NEW_AFFECT_SP_RECOVER_CONTINUE, 

			NEW_AFFECT_POLYMORPH,           // 220
			NEW_AFFECT_MOUNT,

			NEW_AFFECT_WAR_FLAG,            // 222

			NEW_AFFECT_BLOCK_CHAT,          // 223
			NEW_AFFECT_CHINA_FIREWORK,

			NEW_AFFECT_BOW_DISTANCE,        // 225

			NEW_AFFECT_EXP_BONUS         = 500, // ������ ����
			NEW_AFFECT_ITEM_BONUS        = 501, // ������ �尩
			NEW_AFFECT_SAFEBOX           = 502, // PREMIUM_SAFEBOX,
			NEW_AFFECT_AUTOLOOT          = 503, // PREMIUM_AUTOLOOT,
			NEW_AFFECT_FISH_MIND         = 504, // PREMIUM_FISH_MIND,
			NEW_AFFECT_MARRIAGE_FAST     = 505, // ������ ���� (�ݽ�),
			NEW_AFFECT_GOLD_BONUS        = 506,

		    NEW_AFFECT_MALL              = 510, // �� ������ ����Ʈ
			NEW_AFFECT_NO_DEATH_PENALTY  = 511, // ����� ��ȣ (����ġ �г�Ƽ�� �ѹ� �����ش�)
			NEW_AFFECT_SKILL_BOOK_BONUS  = 512, // ������ ���� (å ���� ���� Ȯ���� 50% ����)
			NEW_AFFECT_SKILL_BOOK_NO_DELAY  = 513, // �־� ���� (å ���� ������ ����)

			NEW_AFFECT_EXP_BONUS_EURO_FREE = 516, // ������ ���� (���� ���� 14 ���� ���� �⺻ ȿ��)
			NEW_AFFECT_EXP_BONUS_EURO_FREE_UNDER_15 = 517,

			NEW_AFFECT_AUTO_HP_RECOVERY		= 534,		// �ڵ����� HP
			NEW_AFFECT_AUTO_SP_RECOVERY		= 535,		// �ڵ����� SP

			NEW_AFFECT_DRAGON_SOUL_QUALIFIED = 540, 
			NEW_AFFECT_DRAGON_SOUL_DECK1 = 541,
			NEW_AFFECT_DRAGON_SOUL_DECK2 = 542,
			
#ifdef ENABLE_SHOP_DECORATION_SYSTEM
			NEW_AFFECT_SHOP_DECO = 559,
#endif

#ifdef ENABLE_AUTO_HUNTING_SYSTEM
			NEW_AFFECT_AUTO_HUNT = 560,
#endif

			NEW_AFFECT_RAMADAN_ABILITY = 300,
			NEW_AFFECT_RAMADAN_RING    = 301,			// �󸶴� �̺�Ʈ�� Ư�������� �ʽ´��� ���� ���� ����

			NEW_AFFECT_NOG_POCKET_ABILITY = 302,
			NEW_AFFECT_BLEEDING = 320,

			NEW_AFFECT_QUEST_START_IDX   = 1000,
		};

		enum
		{
			STONE_SMOKE1 = 0,	// 99%
			STONE_SMOKE2 = 1,	// 85%
			STONE_SMOKE3 = 2,	// 80%
			STONE_SMOKE4 = 3,	// 60%
			STONE_SMOKE5 = 4,	// 45%
			STONE_SMOKE6 = 5,	// 40%
			STONE_SMOKE7 = 6,	// 20%
			STONE_SMOKE8 = 7,	// 10%
			STONE_SMOKE_NUM = 4,
		};

		enum EBuildingAffect
		{
			BUILDING_CONSTRUCTION_SMALL = 0,
			BUILDING_CONSTRUCTION_LARGE = 1,
			BUILDING_UPGRADE = 2,
		};

		enum
		{
			WEAPON_DUALHAND,
			WEAPON_ONEHAND,
			WEAPON_TWOHAND,
			WEAPON_NUM,
		};

		enum
		{
			EMPIRE_NONE,
			EMPIRE_A,
			EMPIRE_B,
			EMPIRE_C,
			EMPIRE_NUM,
		};

		enum
		{	
			NAMECOLOR_MOB,
			NAMECOLOR_NPC,
			NAMECOLOR_PC,
			NAMECOLOR_PC_END = NAMECOLOR_PC + EMPIRE_NUM,							
			NAMECOLOR_NORMAL_MOB,
			NAMECOLOR_NORMAL_NPC,
			NAMECOLOR_NORMAL_PC,
			NAMECOLOR_NORMAL_PC_END = NAMECOLOR_NORMAL_PC + EMPIRE_NUM,
			NAMECOLOR_EMPIRE_MOB,
			NAMECOLOR_EMPIRE_NPC,
			NAMECOLOR_EMPIRE_PC,
			NAMECOLOR_EMPIRE_PC_END = NAMECOLOR_EMPIRE_PC + EMPIRE_NUM,
			NAMECOLOR_FUNC,
			NAMECOLOR_PK,
			NAMECOLOR_PVP,
			NAMECOLOR_PARTY,
			NAMECOLOR_WARP,
			NAMECOLOR_WAYPOINT,	
#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
			NAMECOLOR_SHOP,
#endif
			NAMECOLOR_SUPPORT,
			NAMECOLOR_STONE,
			NAMECOLOR_EXTRA = NAMECOLOR_FUNC + 10,
			NAMECOLOR_NUM = NAMECOLOR_EXTRA + 10,
		};
				
		enum
		{
			ALIGNMENT_TYPE_WHITE,
			ALIGNMENT_TYPE_NORMAL,
			ALIGNMENT_TYPE_DARK,
		};

		enum
		{
			EMOTICON_EXCLAMATION	= 1,
			EMOTICON_FISH			= 11,
			EMOTICON_NUM			= 128,
#ifdef ENABLE_ALIGNMENT_SYSTEM
			TITLE_NUM				= 12,
			TITLE_NONE				= 7,
#else
			TITLE_NUM 				= 9,
			TITLE_NONE 				= 4,
#endif
		};

		enum	//�Ʒ� ��ȣ�� �ٲ�� registerEffect �ʵ� �ٲپ� ��� �Ѵ�.
		{
			EFFECT_REFINED_NONE,
			
			EFFECT_SWORD_REFINED7,
			EFFECT_SWORD_REFINED8,
			EFFECT_SWORD_REFINED9,

			EFFECT_BOW_REFINED7,
			EFFECT_BOW_REFINED8,
			EFFECT_BOW_REFINED9,

			EFFECT_FANBELL_REFINED7,
			EFFECT_FANBELL_REFINED8,
			EFFECT_FANBELL_REFINED9,

			EFFECT_SMALLSWORD_REFINED7,
			EFFECT_SMALLSWORD_REFINED8,
			EFFECT_SMALLSWORD_REFINED9,

			EFFECT_SMALLSWORD_REFINED7_LEFT,
			EFFECT_SMALLSWORD_REFINED8_LEFT,
			EFFECT_SMALLSWORD_REFINED9_LEFT,

			EFFECT_BODYARMOR_REFINED7,
			EFFECT_BODYARMOR_REFINED8,
			EFFECT_BODYARMOR_REFINED9,

			EFFECT_BODYARMOR_SPECIAL,	// ���� 4-2-1
			EFFECT_BODYARMOR_SPECIAL2,	// ���� 4-2-2
#ifdef ENABLE_VERSION_162_ENABLED
			EFFECT_BODYARMOR_SPECIAL3,
#endif
			
#ifdef ENABLE_ACCE_SYSTEM
			EFFECT_SASH,
#endif

#ifdef ENABLE_WEAPON_RARITY_SYSTEM
			EFFECT_SPECIAL_REFINED_SWORD_SPECIAL1,
			EFFECT_SPECIAL_REFINED_SWORD_SPECIAL2,
			EFFECT_SPECIAL_REFINED_SWORD_SPECIAL3,
			EFFECT_SPECIAL_REFINED_SWORD_SPECIAL4,

			EFFECT_SPECIAL_REFINED_BOW_SPECIAL1,
			EFFECT_SPECIAL_REFINED_BOW_SPECIAL2,
			EFFECT_SPECIAL_REFINED_BOW_SPECIAL3,
			EFFECT_SPECIAL_REFINED_BOW_SPECIAL4,

			EFFECT_SPECIAL_REFINED_DAGGER_SPECIAL1,
			EFFECT_SPECIAL_REFINED_DAGGER_SPECIAL2,
			EFFECT_SPECIAL_REFINED_DAGGER_SPECIAL3,
			EFFECT_SPECIAL_REFINED_DAGGER_SPECIAL4,

			EFFECT_SPECIAL_REFINED_LDAGGER_SPECIAL1,
			EFFECT_SPECIAL_REFINED_LDAGGER_SPECIAL2,
			EFFECT_SPECIAL_REFINED_LDAGGER_SPECIAL3,
			EFFECT_SPECIAL_REFINED_LDAGGER_SPECIAL4,

			EFFECT_SPECIAL_REFINED_FAN_SPECIAL1,
			EFFECT_SPECIAL_REFINED_FAN_SPECIAL2,
			EFFECT_SPECIAL_REFINED_FAN_SPECIAL3,
			EFFECT_SPECIAL_REFINED_FAN_SPECIAL4,

			EFFECT_SPECIAL_REFINED_LCLAW_SPECIAL1,
			EFFECT_SPECIAL_REFINED_LCLAW_SPECIAL2,
			EFFECT_SPECIAL_REFINED_LCLAW_SPECIAL3,
			EFFECT_SPECIAL_REFINED_LCLAW_SPECIAL4,

			EFFECT_SPECIAL_REFINED_DCLAW_SPECIAL1,
			EFFECT_SPECIAL_REFINED_DCLAW_SPECIAL2,
			EFFECT_SPECIAL_REFINED_DCLAW_SPECIAL3,
			EFFECT_SPECIAL_REFINED_DCLAW_SPECIAL4,
#endif

			EFFECT_REFINED_7TH_SWORD,
			EFFECT_REFINED_7TH_BOW,
			EFFECT_REFINED_7TH_DAGGER,
			EFFECT_REFINED_7TH_DAGGER_LEFT,
			EFFECT_REFINED_7TH_FAN,
			EFFECT_REFINED_7TH_CLAW,
			EFFECT_REFINED_7TH_CLAW_LEFT,
			
			EFFECT_BODYARMOR_SPECIAL4,
			
#ifdef ENABLE_EFFECT_STONE_SYSTEM
			EFFECT_STONE_ARMOR_1,
			EFFECT_STONE_ARMOR_2,
			EFFECT_STONE_ARMOR_3,
			EFFECT_STONE_ARMOR_4,
			EFFECT_STONE_ARMOR_5,
			EFFECT_STONE_ARMOR_6,
#endif

			EFFECT_REFINED_NUM,
		};
		
		enum DamageFlag
		{
			DAMAGE_NORMAL	= (1<<0),
			DAMAGE_POISON	= (1<<1),
			DAMAGE_DODGE	= (1<<2),
			DAMAGE_BLOCK	= (1<<3),
			DAMAGE_PENETRATE= (1<<4),
			DAMAGE_CRITICAL = (1<<5),
#ifdef ENABLE_SHOW_DAMAGE_RENEWAL
			DAMAGE_BLEEDING = (1 << 6),
			DAMAGE_FIRE = (1 << 7),
#endif
			// ��-_-��
		};

		enum
		{
			EFFECT_DUST,
			EFFECT_STUN,
			EFFECT_HIT,
			EFFECT_FLAME_ATTACK,
			EFFECT_FLAME_HIT,
			EFFECT_FLAME_ATTACH,
			EFFECT_ELECTRIC_ATTACK,
			EFFECT_ELECTRIC_HIT,
			EFFECT_ELECTRIC_ATTACH,
			EFFECT_SPAWN_APPEAR,
			EFFECT_SPAWN_DISAPPEAR,
			EFFECT_LEVELUP,
			EFFECT_SKILLUP,
			EFFECT_HPUP_RED,
			EFFECT_SPUP_BLUE,
			EFFECT_SPEEDUP_GREEN,
			EFFECT_DXUP_PURPLE,
			EFFECT_CRITICAL,
			EFFECT_PENETRATE,
			EFFECT_BLOCK,
			EFFECT_DODGE,
			EFFECT_FIRECRACKER,
			EFFECT_SPIN_TOP,
			EFFECT_WEAPON,
			EFFECT_WEAPON_END = EFFECT_WEAPON + WEAPON_NUM,
			EFFECT_AFFECT,
			EFFECT_AFFECT_GYEONGGONG = EFFECT_AFFECT + AFFECT_GYEONGGONG,
			EFFECT_AFFECT_KWAESOK = EFFECT_AFFECT + AFFECT_KWAESOK,
			EFFECT_AFFECT_END = EFFECT_AFFECT + AFFECT_NUM,
			EFFECT_EMOTICON,
			EFFECT_EMOTICON_END = EFFECT_EMOTICON + EMOTICON_NUM,
			EFFECT_MONSTER,
			EFFECT_STONE,
			EFFECT_SHINSOO,
			EFFECT_CHUNJO,
			EFFECT_JINNOS,
			EFFECT_TARGET_SHINSOO,
			EFFECT_TARGET_JINNOS,
			EFFECT_TARGET_CHUNJO,
			EFFECT_TARGET_MONSTER,
			EFFECT_TARGET_STONE,			
			EFFECT_SELECT,
			EFFECT_TARGET,
			EFFECT_EMPIRE,
			EFFECT_EMPIRE_END = EFFECT_EMPIRE + EMPIRE_NUM,
			EFFECT_HORSE_DUST,
			EFFECT_REFINED,
			EFFECT_REFINED_END = EFFECT_REFINED + EFFECT_REFINED_NUM,
			EFFECT_DAMAGE_TARGET,
			EFFECT_DAMAGE_NOT_TARGET,
			EFFECT_DAMAGE_SELFDAMAGE,
			EFFECT_DAMAGE_SELFDAMAGE2,
			EFFECT_DAMAGE_POISON,
			EFFECT_DAMAGE_MISS,
			EFFECT_DAMAGE_TARGETMISS,
			EFFECT_DAMAGE_CRITICAL,
			EFFECT_SUCCESS,
			EFFECT_FAIL,	
			EFFECT_LEVELUP_ON_14_FOR_GERMANY,	//������ 14�϶� ( �������� )
			EFFECT_LEVELUP_UNDER_15_FOR_GERMANY,//������ 15�϶� ( �������� )
			EFFECT_PERCENT_DAMAGE1,
			EFFECT_PERCENT_DAMAGE2,
			EFFECT_PERCENT_DAMAGE3,
			EFFECT_AUTO_HPUP,
			EFFECT_AUTO_SPUP,
			EFFECT_RAMADAN_RING_EQUIP,			// �ʽ´� ���� ���� ������ �ߵ��ϴ� ����Ʈ
			EFFECT_HALLOWEEN_CANDY_EQUIP,		// �ҷ��� ���� ���� ������ �ߵ��ϴ� ����Ʈ
			EFFECT_HAPPINESS_RING_EQUIP,				// �ູ�� ���� ���� ������ �ߵ��ϴ� ����Ʈ
			EFFECT_LOVE_PENDANT_EQUIP,				// �ູ�� ���� ���� ������ �ߵ��ϴ� ����Ʈ
#ifdef ENABLE_VERSION_162_ENABLED
			EFFECT_HEALER,
#endif
#if defined(ENABLE_BATTLE_ZONE_SYSTEM)
			EFFECT_COMBAT_ZONE_POTION,
#endif
#ifdef ENABLE_ACCE_SYSTEM
			EFFECT_SASH_SUCCEDED,
			EFFECT_SASH_EQUIP,
#endif
			// NEW_EFFECTS
			EFFECT_PVP_WIN,
			EFFECT_PVP_OPEN1,
			EFFECT_PVP_OPEN2,

			EFFECT_PVP_BEGIN1,
			EFFECT_PVP_BEGIN2,

			EFFECT_FR_SUCCESS,
			EFFECT_FR_FAIL,	
			// NEW_EFFECTS
			
#ifdef ENABLE_SHOW_DAMAGE_RENEWAL
			EFFECT_DAMAGE_BLEEDING,
			EFFECT_DAMAGE_FIRE,
#endif

#ifdef ENABLE_ZODIAC_TEMPLE_SYSTEM
			EFFECT_SKILL_DAMAGE_ZONE,
			EFFECT_SKILL_DAMAGE_ZONE_BUYUK,
			EFFECT_SKILL_DAMAGE_ZONE_ORTA,
			EFFECT_SKILL_DAMAGE_ZONE_KUCUK,
			EFFECT_SKILL_SAFE_ZONE,
			EFFECT_SKILL_SAFE_ZONE_BUYUK,
			EFFECT_SKILL_SAFE_ZONE_ORTA,
			EFFECT_SKILL_SAFE_ZONE_KUCUK,
			EFFECT_METEOR,
			EFFECT_BEAD_RAIN,
			EFFECT_FALL_ROCK,
			EFFECT_ARROW_RAIN,
			EFFECT_HORSE_DROP,
			EFFECT_EGG_DROP,
			EFFECT_DEAPO_BOOM,
#endif
			EFFECT_TEMP,
			EFFECT_BOSS,
			EFFECT_NUM,
		};

		enum
		{
			DUEL_NONE,
			DUEL_CANNOTATTACK,
			DUEL_START,
		};

		enum EMobAIFlags
		{
			AIFLAG_AGGRESSIVE		= (1 <<  0),
			AIFLAG_NOMOVE			= (1 <<  1),
			AIFLAG_COWARD			= (1 <<  2),
			AIFLAG_NOATTACKSHINSU	= (1 <<  3),
			AIFLAG_NOATTACKJINNO	= (1 <<  4),
			AIFLAG_NOATTACKCHUNJO	= (1 <<  5),
			AIFLAG_ATTACKMOB		= (1 <<  6),
			AIFLAG_BERSERK			= (1 <<  7),
			AIFLAG_STONESKIN		= (1 <<  8),
			AIFLAG_GODSPEED			= (1 <<  9),
			AIFLAG_DEATHBLOW		= (1 << 10),
			AIFLAG_REVIVE			= (1 << 11),
		};
		
	public:
		static void DestroySystem();
		static void CreateSystem(UINT uCapacity);
		static bool RegisterEffect(UINT eEftType, const char* c_szEftAttachBone, const char* c_szEftName, bool isCache);
		static void RegisterTitleName(int iIndex, const char * c_szTitleName);
		static bool RegisterNameColor(UINT uIndex, UINT r, UINT g, UINT b);
		static bool RegisterTitleColor(UINT uIndex, UINT r, UINT g, UINT b);
		static bool ChangeEffectTexture(UINT eEftType, const char* c_szSrcFileName, const char* c_szDstFileName);

		static void SetDustGap(float fDustGap);
		static void SetHorseDustGap(float fDustGap);

		static void SetEmpireNameMode(bool isEnable);
		static const D3DXCOLOR& GetIndexedNameColor(UINT eNameColor);

	public:
		void SetMainInstance();

		void OnSelected();
		void OnUnselected();
		void OnTargeted();
		void OnUntargeted();

	protected:
		bool __IsExistMainInstance();
		bool __IsMainInstance();
		bool __MainCanSeeHiddenThing();
		float __GetBowRange();

	protected:
		DWORD	__AttachEffect(UINT eEftType);
		DWORD	__AttachEffect(char filename[128]);
		void	__DetachEffect(DWORD dwEID);

	public:		
		void CreateSpecialEffect(DWORD iEffectIndex);
		void AttachSpecialEffect(DWORD effect);
#ifdef ENABLE_ZODIAC_TEMPLE_SYSTEM
		void AttachSpecialZodiacEffect(UINT eEftType, long GetX, long GetY);
#endif

	protected:
		static std::string ms_astAffectEffectAttachBone[EFFECT_NUM];
		static DWORD ms_adwCRCAffectEffect[EFFECT_NUM];
		static float ms_fDustGap;
		static float ms_fHorseDustGap;

	public:
		CInstanceBase();
		virtual ~CInstanceBase();

		bool LessRenderOrder(CInstanceBase* pkInst);

		void MountHorse(UINT eRace);
		void DismountHorse();		

		// ��ũ��Ʈ�� �׽�Ʈ �Լ�. ���߿� ������
		void SCRIPT_SetAffect(UINT eAffect, bool isVisible); 

		float CalculateDistanceSq3d(const TPixelPosition& c_rkPPosDst);

		// Instance Data
		bool IsFlyTargetObject();
		void ClearFlyTargetInstance();
		void SetFlyTargetInstance(CInstanceBase& rkInstDst);
		void AddFlyTargetInstance(CInstanceBase& rkInstDst);
		void AddFlyTargetPosition(const TPixelPosition& c_rkPPosDst);

		float GetFlyTargetDistance();

		void SetAlpha(float fAlpha);

		void DeleteBlendOut();

		void					AttachTextTail();
		void					DetachTextTail();
		void					UpdateTextTailLevel(DWORD level);
		
		void					RefreshTextTail();
		void					RefreshTextTailTitle();

		bool					Create(const SCreateData& c_rkCreateData);

		bool					CreateDeviceObjects();
		void					DestroyDeviceObjects();

		void					Destroy();

		void					Update();
		bool					UpdateDeleting();

		void					Transform();
		void					Deform();
		void					Render();
		void					RenderTrace();
		void					RenderToShadowMap();
		void					RenderCollision();
		void					RegisterBoundingSphere();

		// Temporary
		void					GetBoundBox(D3DXVECTOR3 * vtMin, D3DXVECTOR3 * vtMax);

		void					SetNameString(const char* c_szName, int len);
		bool					SetRace(DWORD dwRaceIndex);
		void					SetVirtualID(DWORD wVirtualNumber);
		void					SetVirtualNumber(DWORD dwVirtualNumber);
		void					SetInstanceType(int iInstanceType);
#ifdef ENABLE_ALIGNMENT_SYSTEM
		void					SetAlignment(long long sAlignment);
#else
		void					SetAlignment(short sAlignment);	
#endif
#ifdef ENABLE_GROWTH_PET_SYSTEM
		void					SetLevelText(int mLevel);
#endif
		void					SetLevel(DWORD level);
		void					SetPKMode(BYTE byPKMode);
		void					SetKiller(bool bFlag);
		void					SetPartyMemberFlag(bool bFlag);
		void					SetStateFlags(DWORD dwStateFlags);

#ifdef ENABLE_EFFECT_STONE_SYSTEM
		void					SetArmor(DWORD dwArmor, DWORD dwStoneEffect = 0);
#else
		void					SetArmor(DWORD dwArmor);
#endif
		void					SetShape(DWORD eShape, float fSpecular=0.0f);
		void					SetHair(DWORD eHair);	
#ifdef ENABLE_ACCE_SYSTEM
		void					SetSash(DWORD dwSash);
		void					ChangeSash(DWORD dwSash);
#endif
#ifdef ENABLE_AURA_SYSTEM
		bool					SetAura(DWORD eAura);
		void					ChangeAura(DWORD eAura);
#endif
#ifdef ENABLE_EFFECT_STONE_SYSTEM
		bool					SetWeapon(DWORD eWeapon, DWORD dwWeaponRareLv = 0, DWORD dwWeaponStoneEffect = 0);
#else
		bool					SetWeapon(DWORD eWeapon, DWORD dwWeaponRareLv = 0);
#endif
#ifdef ENABLE_QUIVER_SYSTEM
		bool					SetArrow(DWORD eArrow);
#endif
#ifdef ENABLE_EFFECT_STONE_SYSTEM
		bool					ChangeArmor(DWORD dwArmor, DWORD dwStoneEffect = 0);
#else
		bool					ChangeArmor(DWORD dwArmor);
#endif
#ifdef ENABLE_EFFECT_STONE_SYSTEM
		void					ChangeWeapon(DWORD eWeapon, DWORD dwWeaponRareLv = 0, DWORD dwWeaponStoneEffect = 0);
#else
		void					ChangeWeapon(DWORD eWeapon, DWORD dwWeaponRareLv = 0);
#endif
		void					ChangeHair(DWORD eHair);
		void					ChangeGuild(DWORD dwGuildID);
		DWORD					GetWeaponType();

		void					SetComboType(UINT uComboType);
		void					SetAttackSpeed(UINT uAtkSpd);
		void					SetMoveSpeed(UINT uMovSpd);
		void					SetRotationSpeed(float fRotSpd);

		const char *			GetNameString();
		int						GetInstanceType();
		DWORD					GetLevel();
#if defined(ENABLE_BATTLE_ZONE_SYSTEM)
		bool					IsCombatZoneMap();
		void					SetCombatZonePoints(DWORD dwValue);
		DWORD					GetCombatZonePoints();
		void					SetCombatZoneRank(BYTE bValue);
		BYTE					GetCombatZoneRank();
#endif
#ifdef ENABLE_BUFFI_SYSTEM
		void					SetSupportShaman(bool bTrue);
		bool					IsSupportShaman();
#endif
#ifdef ENABLE_GUILD_LEADER_SYSTEM
		BYTE					GetGuildMemberType();
#endif
		DWORD					GetPart(CRaceData::EParts part);
		DWORD					GetShape();
		DWORD					GetRace();
		DWORD					GetOriginalRace();
		DWORD					GetVirtualID();
		DWORD					GetVirtualNumber();
		DWORD					GetEmpireID();
		DWORD					GetGuildID();
#if defined(WJ_SHOW_MOB_INFO)
		DWORD					GetAIFlag();
#endif
#ifdef ENABLE_ALIGNMENT_SYSTEM
		long long				GetAlignment();
#else
		int						GetAlignment();
#endif
		UINT					GetAlignmentGrade();
		int						GetAlignmentType();
		BYTE					GetPKMode();
		float					GetBaseHeight();
		bool					IsKiller();
		bool					IsPartyMember();

		void					ActDualEmotion(CInstanceBase & rkDstInst, WORD dwMotionNumber1, WORD dwMotionNumber2);
		void					ActEmotion(DWORD dwMotionNumber);
		void					LevelUp();
		void					SkillUp();
		void					UseSpinTop();
		void					Revive();
		void					Stun();
		void					Die();
		void					Hide();
		void					Show();

		bool					CanAct();
		bool					CanMove();
		bool					CanAttack();
		bool					CanUseSkill();
		bool					CanFishing();
		bool					IsConflictAlignmentInstance(CInstanceBase& rkInstVictim);
		bool					IsAttackableInstance(CInstanceBase& rkInstVictim);
		bool					IsTargetableInstance(CInstanceBase& rkInstVictim);
		bool					IsPVPInstance(CInstanceBase& rkInstVictim);
		bool					CanChangeTarget();
		bool					CanPickInstance();
		bool					CanViewTargetHP(CInstanceBase& rkInstVictim);


		// Movement
		BOOL					IsGoing();
		bool					NEW_Goto(const TPixelPosition& c_rkPPosDst, float fDstRot);
		void					EndGoing();

		void					SetRunMode();
		void					SetWalkMode();

		bool					IsAffect(UINT uAffect);
		BOOL					IsInvisibility();
		BOOL					IsParalysis();
		BOOL					IsGameMaster();
#ifdef ENABLE_YOUTUBER_SYSTEM
		BOOL					IsYoutuber();
		BOOL					IsTwitcher();
#endif
		BOOL					IsSameEmpire(CInstanceBase& rkInstDst);
		BOOL					IsBowMode();
		BOOL					IsHandMode();
		BOOL					IsFishingMode();
		BOOL					IsFishing();

		BOOL					IsWearingDress();
		BOOL					IsHoldingPickAxe();
		BOOL					IsMountingHorse();
		BOOL					IsNewMount();
		BOOL					IsForceVisible();
		BOOL					IsInSafe();
#ifdef ENABLE_GROWTH_PET_SYSTEM
		BOOL					IsNewPet();
#endif
		BOOL					IsEnemy();
		BOOL					IsStone();
		BOOL					IsResource();
		BOOL					IsNPC();
		BOOL					IsPC();
		BOOL					IsPoly();
		BOOL					IsWarp();
		BOOL					IsGoto();
		BOOL					IsObject();
		BOOL					IsDoor();
		BOOL					IsBuilding();
		BOOL					IsWoodenDoor();
		BOOL					IsStoneDoor();
		BOOL					IsFlag();
		BOOL					IsGuildWall();
		BOOL					IsPet();
		BOOL					IsMount();
		BOOL					IsOfflineShop();

		BOOL					IsDead();
		BOOL					IsStun();
		BOOL					IsSleep();
		BOOL					__IsSyncing();
		BOOL					IsWaiting();
		BOOL					IsWalking();
		BOOL					IsPushing();
		BOOL					IsAttacking();
		BOOL					IsActingEmotion();
		BOOL					IsAttacked();
		BOOL					IsKnockDown();
		BOOL					IsUsingSkill();
		BOOL					IsUsingMovingSkill();
		BOOL					CanCancelSkill();
		BOOL					CanAttackHorseLevel();
		
#ifdef ENABLE_EFFECT_STONE_SYSTEM
		DWORD					GetAddedEffectStone(DWORD dwStoneEffect);
		DWORD					GetAddedEffectStoneWeapon(DWORD dwType, DWORD dwEffectStone, bool dagger = false);
#endif

#ifdef __MOVIE_MODE__
		BOOL					IsMovieMode(); // ��ڿ� ������ �Ⱥ��̴°�
#endif
		bool					NEW_CanMoveToDestPixelPosition(const TPixelPosition& c_rkPPosDst);

		void					NEW_SetAdvancingRotationFromPixelPosition(const TPixelPosition& c_rkPPosSrc, const TPixelPosition& c_rkPPosDst);
		void					NEW_SetAdvancingRotationFromDirPixelPosition(const TPixelPosition& c_rkPPosDir);
		bool					NEW_SetAdvancingRotationFromDestPixelPosition(const TPixelPosition& c_rkPPosDst);
		void					SetAdvancingRotation(float fRotation);

		void					EndWalking(float fBlendingTime=0.15f);
		void					EndWalkingWithoutBlending();

		// Battle
		void					SetEventHandler(CActorInstance::IEventHandler* pkEventHandler);

		void					PushUDPState(DWORD dwCmdTime, const TPixelPosition& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg);
		void					PushTCPState(DWORD dwCmdTime, const TPixelPosition& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg);
		void					PushTCPStateExpanded(DWORD dwCmdTime, const TPixelPosition& c_rkPPosDst, float fDstRot, UINT eFunc, UINT uArg, UINT uTargetVID);

		void					NEW_Stop();

		bool					NEW_UseSkill(UINT uSkill, UINT uMot, UINT uMotLoopCount, bool isMovingSkill);
		void					NEW_Attack();
		void					NEW_Attack(float fDirRot);
		void					NEW_AttackToDestPixelPositionDirection(const TPixelPosition& c_rkPPosDst);
		bool					NEW_AttackToDestInstanceDirection(CInstanceBase& rkInstDst, IFlyEventHandler* pkFlyHandler);
		bool					NEW_AttackToDestInstanceDirection(CInstanceBase& rkInstDst);

		bool					NEW_MoveToDestPixelPositionDirection(const TPixelPosition& c_rkPPosDst);
		void					NEW_MoveToDestInstanceDirection(CInstanceBase& rkInstDst);
		void					NEW_MoveToDirection(float fDirRot);

		float					NEW_GetDistanceFromDirPixelPosition(const TPixelPosition& c_rkPPosDir);
		float					NEW_GetDistanceFromDestPixelPosition(const TPixelPosition& c_rkPPosDst);
		float					NEW_GetDistanceFromDestInstance(CInstanceBase& rkInstDst);

		float					NEW_GetRotation();
		float					NEW_GetRotationFromDestPixelPosition(const TPixelPosition& c_rkPPosDst);
		float					NEW_GetRotationFromDirPixelPosition(const TPixelPosition& c_rkPPosDir);
		float					NEW_GetRotationFromDestInstance(CInstanceBase& rkInstDst);

		float					NEW_GetAdvancingRotationFromDirPixelPosition(const TPixelPosition& c_rkPPosDir);
		float					NEW_GetAdvancingRotationFromDestPixelPosition(const TPixelPosition& c_rkPPosDst);
		float					NEW_GetAdvancingRotationFromPixelPosition(const TPixelPosition& c_rkPPosSrc, const TPixelPosition& c_rkPPosDst);

		BOOL					NEW_IsClickableDistanceDestPixelPosition(const TPixelPosition& c_rkPPosDst);
		BOOL					NEW_IsClickableDistanceDestInstance(CInstanceBase& rkInstDst);

		bool					NEW_GetFrontInstance(CInstanceBase ** ppoutTargetInstance, float fDistance);
		void					NEW_GetRandomPositionInFanRange(CInstanceBase& rkInstTarget, TPixelPosition* pkPPosDst);
		bool					NEW_GetInstanceVectorInFanRange(float fSkillDistance, CInstanceBase& rkInstTarget, std::vector<CInstanceBase*>* pkVct_pkInst);
		bool					NEW_GetInstanceVectorInCircleRange(float fSkillDistance, std::vector<CInstanceBase*>* pkVct_pkInst);

		void					NEW_SetOwner(DWORD dwOwnerVID);
		void					NEW_SyncPixelPosition(long & nPPosX, long & nPPosY);
		void					NEW_SyncCurrentPixelPosition();

		void					NEW_SetPixelPosition(const TPixelPosition& c_rkPPosDst);

		bool					NEW_IsLastPixelPosition();
		const TPixelPosition&	NEW_GetLastPixelPositionRef();


		// Battle
		BOOL					isNormalAttacking();
		BOOL					isComboAttacking();
		MOTION_KEY				GetNormalAttackIndex();
		DWORD					GetComboIndex();
		float					GetAttackingElapsedTime();
		void					InputNormalAttack(float fAtkDirRot);
		void					InputComboAttack(float fAtkDirRot);

		void					RunNormalAttack(float fAtkDirRot);
		void					RunComboAttack(float fAtkDirRot, DWORD wMotionIndex);

		CInstanceBase*			FindNearestVictim();
		BOOL					CheckAdvancing();


		bool					AvoidObject(const CGraphicObjectInstance& c_rkBGObj);		
		bool					IsBlockObject(const CGraphicObjectInstance& c_rkBGObj);
		void					BlockMovement();

	public:
		BOOL					CheckAttacking(CInstanceBase& rkInstVictim);
		void					ProcessHitting(DWORD dwMotionKey, CInstanceBase * pVictimInstance);
		void					ProcessHitting(DWORD dwMotionKey, BYTE byEventIndex, CInstanceBase * pVictimInstance);
		void					GetBlendingPosition(TPixelPosition * pPixelPosition);
		void					SetBlendingPosition(const TPixelPosition & c_rPixelPosition);

		// Fishing
		void					StartFishing(float frot);
		void					StopFishing();
		void					ReactFishing();
		void					CatchSuccess();
		void					CatchFail();
		BOOL					GetFishingRot(int * pirot);

		// Render Mode
		void					RestoreRenderMode();
		void					SetAddRenderMode();
		void					SetModulateRenderMode();
		void					SetRenderMode(int iRenderMode);
		void					SetAddColor(const D3DXCOLOR & c_rColor);

		// Position
		void					SCRIPT_SetPixelPosition(float fx, float fy);
		void					NEW_GetPixelPosition(TPixelPosition * pPixelPosition);

		// Rotation
		void					NEW_LookAtFlyTarget();
		void					NEW_LookAtDestInstance(CInstanceBase& rkInstDst);
		void					NEW_LookAtDestPixelPosition(const TPixelPosition& c_rkPPosDst);

		float					GetRotation();
		float					GetAdvancingRotation();
		void					SetRotation(float fRotation);
		void					BlendRotation(float fRotation, float fBlendTime = 0.1f);

		void					SetDirection(int dir);
		void					BlendDirection(int dir, float blendTime);
		float					GetDegreeFromDirection(int dir);

		// Motion
		//	Motion Deque
		BOOL					isLock();

		void					SetMotionMode(int iMotionMode);
		int						GetMotionMode(DWORD dwMotionIndex);

		// Motion
		//	Pushing Motion
		void					ResetLocalTime();
		void					SetLoopMotion(WORD wMotion, float fBlendTime=0.1f, float fSpeedRatio=1.0f);
		void					PushOnceMotion(WORD wMotion, float fBlendTime=0.1f, float fSpeedRatio=1.0f);
		void					PushLoopMotion(WORD wMotion, float fBlendTime=0.1f, float fSpeedRatio=1.0f);
		void					SetEndStopMotion();

		// Intersect
		bool					IntersectDefendingSphere();
		bool					IntersectBoundingBox();

		// Part
		//void					SetParts(const WORD * c_pParts);
		void					Refresh(DWORD dwMotIndex, bool isLoop);

		//void					AttachEffectByID(DWORD dwParentPartIndex, const char * c_pszBoneName, DWORD dwEffectID, int dwLife = CActorInstance::EFFECT_LIFE_INFINITE ); // ������ ms�����Դϴ�.
		//void					AttachEffectByName(DWORD dwParentPartIndex, const char * c_pszBoneName, const char * c_pszEffectName, int dwLife = CActorInstance::EFFECT_LIFE_INFINITE ); // ������ ms�����Դϴ�.

		float					GetDistance(CInstanceBase * pkTargetInst);
		float					GetDistance(const TPixelPosition & c_rPixelPosition);

		// ETC
		CActorInstance&			GetGraphicThingInstanceRef();
		CActorInstance*			GetGraphicThingInstancePtr();		
		
		bool __Background_IsWaterPixelPosition(const TPixelPosition& c_rkPPos);
		bool __Background_GetWaterHeight(const TPixelPosition& c_rkPPos, float* pfHeight);

		// 2004.07.25.myevan.����Ʈ �ȳ����� ����
		/////////////////////////////////////////////////////////////
		void __ClearAffectFlagContainer();
		void __ClearAffects();
		/////////////////////////////////////////////////////////////

		void __SetAffect(UINT eAffect, bool isVisible);
		
		void SetAffectFlagContainer(const CAffectFlagContainer& c_rkAffectFlagContainer);

		void __SetNormalAffectFlagContainer(const CAffectFlagContainer& c_rkAffectFlagContainer);		
		void __SetStoneSmokeFlagContainer(const CAffectFlagContainer& c_rkAffectFlagContainer);

		void SetEmoticon(UINT eEmoticon);		
		void SetFishEmoticon();
		bool IsPossibleEmoticon();

	protected:
		UINT					__LessRenderOrder_GetLODLevel();
		void					__Initialize();
		void					__InitializeRotationSpeed();

		void					__Create_SetName(const SCreateData& c_rkCreateData);
		void					__Create_SetWarpName(const SCreateData& c_rkCreateData);

		CInstanceBase*			__GetMainInstancePtr();
		CInstanceBase*			__FindInstancePtr(DWORD dwVID);

		bool  __FindRaceType(DWORD dwRace, BYTE* pbType);
		DWORD __GetRaceType();

		bool __IsShapeAnimalWear();
		BOOL __IsChangableWeapon(int iWeaponID);

		void __EnableSkipCollision();
		void __DisableSkipCollision();

		void __ClearMainInstance();

		void __Shaman_SetParalysis(bool isParalysis);
		void __Warrior_SetGeomgyeongAffect(bool isVisible);
		void __Assassin_SetEunhyeongAffect(bool isVisible);
		void __SetReviveInvisibilityAffect(bool isVisible);

		BOOL __CanProcessNetworkStatePacket();
		
		bool __IsInDustRange();

		// Emotion
		void __ProcessFunctionEmotion(DWORD dwMotionNumber, DWORD dwTargetVID, const TPixelPosition & c_rkPosDst);
		void __EnableChangingTCPState();
		void __DisableChangingTCPState();
		BOOL __IsEnableTCPProcess(UINT eCurFunc);

		// 2004.07.17.levites.isShow�� ViewFrustumCheck�� ����
		bool __CanRender();
		bool __IsInViewFrustum();

		// HORSE
		void __AttachHorseSaddle();
		void __DetachHorseSaddle();
		
		struct SHORSE
		{
			bool m_isMounting;
			CActorInstance* m_pkActor;
			
			SHORSE();			
			~SHORSE();
			
			void Destroy();
			void Create(const TPixelPosition& c_rkPPos, UINT eRace, UINT eHitEffect);
			
			void SetAttackSpeed(UINT uAtkSpd);
			void SetMoveSpeed(UINT uMovSpd);
			void Deform();
			void Render();
			CActorInstance& GetActorRef();
			CActorInstance* GetActorPtr();

			bool IsMounting();
			bool CanAttack();
			bool CanUseSkill();

			UINT GetLevel();
			bool IsNewMount();
			bool IsManuManni();

			void __Initialize();
		} m_kHorse;


	protected:
		// Blend Mode
		void					__SetBlendRenderingMode();
		void					__SetAlphaValue(float fAlpha);
		float					__GetAlphaValue();

		void					__ComboProcess();
		void					MovementProcess();
		void					TodoProcess();
		void					StateProcess();
		void					AttackProcess();

		void					StartWalking();
		float					GetLocalTime();

		void					RefreshState(DWORD dwMotIndex, bool isLoop);
		void					RefreshActorInstance();

	protected:
		void					OnSyncing();
		void					OnWaiting();
		void					OnMoving();

		void					NEW_SetCurPixelPosition(const TPixelPosition& c_rkPPosDst);
		void					NEW_SetSrcPixelPosition(const TPixelPosition& c_rkPPosDst);
		void					NEW_SetDstPixelPosition(const TPixelPosition& c_rkPPosDst);
		void					NEW_SetDstPixelPositionZ(FLOAT z);

		const TPixelPosition&	NEW_GetCurPixelPositionRef();
		const TPixelPosition&	NEW_GetSrcPixelPositionRef();

	public:
		const TPixelPosition&	NEW_GetDstPixelPositionRef();
		
	protected:
		BOOL m_isTextTail;		

		// Instance Data
		std::string				m_stName;

		DWORD					m_awPart[CRaceData::PART_MAX_NUM];

		DWORD					m_dwLevel;
		DWORD					m_dwEmpireID;
		DWORD					m_dwGuildID;
#ifdef WJ_SHOW_MOB_INFO
		DWORD					m_dwAIFlag;
#endif
		bool					m_bIsHidden;
	public:
		bool					IsHidden();
		CAffectFlagContainer	GetAffectFlags() { return m_kAffectFlagContainer; }
	protected:		
		CAffectFlagContainer	m_kAffectFlagContainer;
		DWORD					m_adwCRCAffectEffect[AFFECT_NUM];
		
		UINT	__GetRefinedEffect(CItemData* pItem, DWORD dwWeaponRarePts = 0, DWORD dwEffectStone = 0);		
		void	__ClearWeaponRefineEffect();
		void	__ClearArmorRefineEffect();
#ifdef ENABLE_SHINING_SYSTEM
		void	__GetShiningEffect(CItemData* pItem);
		void	__ClearWeaponShiningEffect(bool detaching = true);
		void	__ClearArmorShiningEffect(bool detaching = true);
		void	__AttachWeaponShiningEffect(int effectIndex, const char* effectFileName, const char* boneName = "Bip01");
		void	__AttachArmorShiningEffect(int effectIndex, const char* effectFileName, const char* boneName = "Bip01");
#endif

#ifdef ENABLE_ACCE_SYSTEM
		void	ClearSashEffect();
#endif

#ifdef ENABLE_AURA_SYSTEM
		void	ClearAuraEffect();
#endif

#ifdef ENABLE_WEAPON_RARITY_SYSTEM
		DWORD	__DetermineRarityLevel(DWORD dwType, DWORD dwLv, bool isDagger = false);
		DWORD	GetRareLevel(DWORD iPoints);
#endif

	protected:
		void __AttachSelectEffect();
		void __DetachSelectEffect();

		void __AttachTargetEffect();
		void __DetachTargetEffect();

		void __AttachTargetEffectMonster();
		void __DetachTargetEffectMonster();
		void __AttachSelectEffectMonster();
		void __DetachSelectEffectMonster();

		void __AttachTargetEffectStone();
		void __DetachTargetEffectStone();
		void __AttachSelectEffectStone();
		void __DetachSelectEffectStone();		

		void __AttachTargetEffectShinsoo();
		void __DetachTargetEffectShinsoo();
		void __AttachSelectEffectShinsoo();
		void __DetachSelectEffectShinsoo();

		void __AttachTargetEffectJinnos();
		void __DetachTargetEffectJinnos();
		void __AttachSelectEffectJinnos();
		void __DetachSelectEffectJinnos();

		void __AttachTargetEffectChunjo();
		void __DetachTargetEffectChunjo();
		void __AttachSelectEffectChunjo();
		void __DetachSelectEffectChunjo();		

		void __AttachEmpireEffect(DWORD eEmpire);

	protected:
		struct SEffectContainer
		{
			typedef std::map<DWORD, DWORD> Dict;
			Dict m_kDct_dwEftID;
		} m_kEffectContainer;

		void __EffectContainer_Initialize();
		void __EffectContainer_Destroy();
		void __EffectContainer_Suspend();
		void __EffectContainer_Continue();
		
#ifdef ENABLE_BOSS_EFFECT_SYSTEM
		void __AttachEffectBoss();
#endif

		DWORD __EffectContainer_AttachEffect(DWORD eEffect);
		void __EffectContainer_DetachEffect(DWORD eEffect);

		SEffectContainer::Dict& __EffectContainer_GetDict();

	protected:
		struct SStoneSmoke 
		{
			DWORD m_dwEftID;
		} m_kStoneSmoke;

		void __StoneSmoke_Inialize();
		void __StoneSmoke_Destroy();
		void __StoneSmoke_Create(DWORD eSmoke);


	protected:
		// Emoticon
		//DWORD					m_adwCRCEmoticonEffect[EMOTICON_NUM];

		BYTE					m_eType;
		BYTE					m_eRaceType;
		DWORD					m_eShape;
		DWORD					m_dwRace;
		DWORD					m_dwOriginalRace;
		DWORD					m_dwVirtualNumber;
#ifdef ENABLE_ALIGNMENT_SYSTEM
		long long				m_sAlignment;
#else
		short					m_sAlignment;
#endif
		BYTE					m_byPKMode;
#if defined(ENABLE_BATTLE_ZONE_SYSTEM)
		BYTE					combat_zone_rank;
		DWORD					combat_zone_points;
#endif
#ifdef ENABLE_BUFFI_SYSTEM
		bool					is_support_shaman;
#endif
		bool					m_isKiller;
		bool					m_isPartyMember;

		// Movement
		int						m_iRotatingDirection;

		DWORD					m_dwAdvActorVID;
		DWORD					m_dwLastDmgActorVID;

		LONG					m_nAverageNetworkGap;
		DWORD					m_dwNextUpdateHeightTime;

		bool					m_isGoing;

		TPixelPosition			m_kPPosDust;

		DWORD					m_dwLastComboIndex;

		DWORD					m_swordRefineEffectRight;
		DWORD					m_swordRefineEffectLeft;
		DWORD					m_armorRefineEffect;
#ifdef ENABLE_GUILD_LEADER_SYSTEM
		BYTE					m_bMemberType;
#endif
#ifdef ENABLE_ACCE_SYSTEM
		DWORD					m_dwSashEffect;
#endif
#ifdef ENABLE_WEAPON_RARITY_SYSTEM
		DWORD					m_dwWeaponRareLv;
#endif
#ifdef ENABLE_SHINING_SYSTEM
		//2-Dimensions for Left & Right sided effects
		DWORD					m_weaponShiningEffects[2][CItemData::ITEM_SHINING_MAX_COUNT];
		DWORD					m_armorShiningEffects[CItemData::ITEM_SHINING_MAX_COUNT];
#endif
#ifdef ENABLE_AURA_SYSTEM
		DWORD					m_auraRefineEffect;
#endif

		struct SMoveAfterFunc
		{
			UINT eFunc;
			UINT uArg;

			// For Emotion Function
			UINT uArgExpanded;
			TPixelPosition kPosDst;
		};

		SMoveAfterFunc m_kMovAfterFunc;

		float m_fDstRot;
		float m_fAtkPosTime;
		float m_fRotSpd;
		float m_fMaxRotSpd;

		BOOL m_bEnableTCPState;

		// Graphic Instance
		CActorInstance m_GraphicThingInstance;


	protected:
		struct SCommand
		{
			DWORD	m_dwChkTime;
			DWORD	m_dwCmdTime;
			float	m_fDstRot;
			UINT 	m_eFunc;
			UINT 	m_uArg;
			UINT	m_uTargetVID;
			TPixelPosition m_kPPosDst;
		};

		typedef std::list<SCommand> CommandQueue;

		DWORD		m_dwBaseChkTime;
		DWORD		m_dwBaseCmdTime;

		DWORD		m_dwSkipTime;

		CommandQueue m_kQue_kCmdNew;

		BOOL		m_bDamageEffectType;

		struct SEffectDamage
		{
			DWORD damage;
			BYTE flag;
			BOOL bSelf;
			BOOL bTarget;
		};

		typedef std::list<SEffectDamage> CommandDamageQueue;
		CommandDamageQueue m_DamageQueue;

		void ProcessDamage();

	public:
		void AddDamageEffect(DWORD damage,BYTE flag,BOOL bSelf,BOOL bTarget);

	protected:
		struct SWarrior
		{
			DWORD m_dwGeomgyeongEffect;
		};

		SWarrior m_kWarrior;

		void __Warrior_Initialize();

	public:
		static void ClearPVPKeySystem();

		static void InsertPVPKey(DWORD dwSrcVID, DWORD dwDstVID);
		static void InsertPVPReadyKey(DWORD dwSrcVID, DWORD dwDstVID);
		static void RemovePVPKey(DWORD dwSrcVID, DWORD dwDstVID);

		static void InsertGVGKey(DWORD dwSrcGuildVID, DWORD dwDstGuildVID);
		static void RemoveGVGKey(DWORD dwSrcGuildVID, DWORD dwDstGuildVID);

		static void InsertDUELKey(DWORD dwSrcVID, DWORD dwDstVID);

		UINT GetNameColorIndex();

		const D3DXCOLOR& GetNameColor();
		const D3DXCOLOR& GetTitleColor();

	protected:
		static DWORD __GetPVPKey(DWORD dwSrcVID, DWORD dwDstVID);
		static bool __FindPVPKey(DWORD dwSrcVID, DWORD dwDstVID);
		static bool __FindPVPReadyKey(DWORD dwSrcVID, DWORD dwDstVID);
		static bool __FindGVGKey(DWORD dwSrcGuildID, DWORD dwDstGuildID);
		static bool __FindDUELKey(DWORD dwSrcGuildID, DWORD dwDstGuildID);

	protected:
		CActorInstance::IEventHandler* GetEventHandlerPtr();
		CActorInstance::IEventHandler& GetEventHandlerRef();

	protected:
		static float __GetBackgroundHeight(float x, float y);
		static DWORD __GetShadowMapColor(float x, float y);

	public:
		static void ResetPerformanceCounter();
		static void GetInfo(std::string* pstInfo);

	public:
		static CInstanceBase* New();
		static void Delete(CInstanceBase* pkInst);

		static CDynamicPool<CInstanceBase>	ms_kPool;

	protected:
		static DWORD ms_dwUpdateCounter;
		static DWORD ms_dwRenderCounter;
		static DWORD ms_dwDeformCounter;

	public:		
		DWORD					GetDuelMode();
		void					SetDuelMode(DWORD type);
	protected:
		DWORD					m_dwDuelMode;
		DWORD					m_dwEmoticonTime;
	public:
		void SetBodyColor (DWORD dwRace, DWORD dwBodyColor);
	protected:
		bool m_IsAlwaysRender;
	public:
		bool IsAlwaysRender();
		void SetAlwaysRender(bool val);
};

inline int RaceToJob(int race)
{
	switch (race)
	{
		case 0:
		case 4:
			return 0;
		case 1:
		case 5:
			return 1;
		case 2:
		case 6:
			return 2;
		case 3:
		case 7:
			return 3;
		case 8:
			return 4;
		default:
			return 0;
	}
	return 0;
}

inline int RaceToSex(int race)
{
	switch (race)
	{
		case 0:
		case 2:
		case 5:
		case 7:
		case 8:
			return 1;
		case 1:
		case 3:
		case 4:
		case 6:
			return 0;

	}
	return 0;
}
