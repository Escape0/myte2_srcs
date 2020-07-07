#include "stdafx.h"
#include "../../libgame/libgame/grid.h"
#include "constants.h"
#include "safebox.h"
#include "packet.h"
#include "char.h"
#include "desc_client.h"
#include "item.h"
#include "item_manager.h"
#include "config.h"

CSafebox::CSafebox(LPCHARACTER pkChrOwner, int iSize, long long dwGold, WORD cheque) : m_pkChrOwner(pkChrOwner), m_iSize(iSize), m_lGold(dwGold), m_wCheque(cheque)
{
	assert(m_pkChrOwner != nullptr);
	memset(m_pkItems, 0, sizeof(m_pkItems));

	if (m_iSize)
		m_pkGrid = M2_NEW CGrid(5, m_iSize);
	else
		m_pkGrid = nullptr;

	m_bWindowMode = SAFEBOX;
}

CSafebox::~CSafebox()
{
	__Destroy();
}

void CSafebox::SetWindowMode(BYTE bMode)
{
	m_bWindowMode = bMode;
}

void CSafebox::__Destroy()
{
	for (int i = 0; i < SAFEBOX_MAX_NUM; ++i)
	{
		if (m_pkItems[i])
		{
			m_pkItems[i]->SetSkipSave(true);
			ITEM_MANAGER::instance().FlushDelayedSave(m_pkItems[i]);

			M2_DESTROY_ITEM(m_pkItems[i]->RemoveFromCharacter());
			m_pkItems[i] = nullptr;
		}
	}

	if (m_pkGrid)
	{
		M2_DELETE(m_pkGrid);
		m_pkGrid = nullptr;
	}
}

bool CSafebox::Add(DWORD dwPos, LPITEM pkItem)
{
	if (!IsValidPosition(dwPos))
	{
		sys_err("SAFEBOX: item on wrong position at %d (size of grid = %d)", dwPos, m_pkGrid->GetSize());
		return false;
	}

	pkItem->SetWindow(m_bWindowMode);
	pkItem->SetCell(m_pkChrOwner, dwPos);
	pkItem->Save(); // ������ Save�� �ҷ���� �Ѵ�.
	ITEM_MANAGER::instance().FlushDelayedSave(pkItem);

	m_pkGrid->Put(dwPos, 1, pkItem->GetSize());
	m_pkItems[dwPos] = pkItem;

	TPacketGCItemSet pack;

	pack.header = m_bWindowMode == SAFEBOX ? HEADER_GC_SAFEBOX_SET : HEADER_GC_MALL_SET;
	pack.Cell = TItemPos(m_bWindowMode, dwPos);
	pack.vnum = pkItem->GetVnum();
	pack.count = pkItem->GetCount();
#ifdef ENABLE_CHANGELOOK_SYSTEM
	pack.transmutation = pkItem->GetTransmutation();
#endif
	pack.flags = pkItem->GetFlag();
	pack.anti_flags = pkItem->GetAntiFlag();
	pack.sealbind = pkItem->GetSealBindTime();
	thecore_memcpy(pack.alSockets, pkItem->GetSockets(), sizeof(pack.alSockets));
	thecore_memcpy(pack.aAttr, pkItem->GetAttributes(), sizeof(pack.aAttr));

	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));
	sys_log(1, "SAFEBOX: ADD %s %s count %d", m_pkChrOwner->GetName(), pkItem->GetName(), pkItem->GetCount());
	return true;
}

LPITEM CSafebox::Get(DWORD dwPos)
{
	if (dwPos >= m_pkGrid->GetSize())
		return nullptr;

	return m_pkItems[dwPos];
}

LPITEM CSafebox::Remove(DWORD dwPos)
{
	LPITEM pkItem = Get(dwPos);

	if (!pkItem)
		return nullptr;

	if (!m_pkGrid)
		sys_err("Safebox::Remove : nil grid");
	else
		m_pkGrid->Get(dwPos, 1, pkItem->GetSize());

	pkItem->RemoveFromCharacter();

	m_pkItems[dwPos] = nullptr;

	TPacketGCItemDel pack;

	pack.header = m_bWindowMode == SAFEBOX ? HEADER_GC_SAFEBOX_DEL : HEADER_GC_MALL_DEL;
	pack.pos = dwPos;

	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));
	sys_log(1, "SAFEBOX: REMOVE %s %s count %d", m_pkChrOwner->GetName(), pkItem->GetName(), pkItem->GetCount());
	return pkItem;
}

#ifdef ENABLE_SAFEBOX_MONEY_SYSTEM
void CSafebox::SetGold(long long llGold, BYTE type)
{
	if (type)
		m_lGold += llGold;
	else
		m_lGold -= llGold;

	TPacketGCSafeboxMoneyChange pack;
	pack.bHeader = HEADER_GC_SAFEBOX_MONEY_CHANGE;
	pack.llMoney = m_lGold;
	pack.wCheque = m_wCheque;
	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));
}

void CSafebox::SetCheque(WORD wCheque, BYTE type)
{
	if (type)
		m_wCheque += wCheque;
	else
		m_wCheque -= wCheque;
	
	TPacketGCSafeboxMoneyChange pack;
	pack.bHeader = HEADER_GC_SAFEBOX_MONEY_CHANGE;
	pack.llMoney = m_lGold;
	pack.wCheque = m_wCheque;
	m_pkChrOwner->GetDesc()->Packet(&pack, sizeof(pack));
}
#else
void CSafebox::Save()
{
	TSafeboxTable t;

	memset(&t, 0, sizeof(TSafeboxTable));

	t.dwID = m_pkChrOwner->GetDesc()->GetAccountTable().id;
	t.dwGold = m_lGold;

	db_clientdesc->DBPacket(HEADER_GD_SAFEBOX_SAVE, 0, &t, sizeof(TSafeboxTable));
	sys_log(1, "SAFEBOX: SAVE %s", m_pkChrOwner->GetName());
}
#endif

bool CSafebox::IsEmpty(DWORD dwPos, BYTE bSize)
{
	if (!m_pkGrid)
		return false;

	return m_pkGrid->IsEmpty(dwPos, 1, bSize);
}

void CSafebox::ChangeSize(int iSize)
{
	// ���� ����� ���ں��� ũ�� ����� ���� �д�.
	if (m_iSize >= iSize)
		return;

	m_iSize = iSize;

	CGrid * pkOldGrid = m_pkGrid;

	if (pkOldGrid)
		m_pkGrid = M2_NEW CGrid(pkOldGrid, 5, m_iSize);
	else
		m_pkGrid = M2_NEW CGrid(5, m_iSize);
}

LPITEM CSafebox::GetItem(INT bCell)
{
	if (bCell >= 5 * m_iSize)
	{
		sys_err("CHARACTER::GetItem: invalid item cell %d", bCell);
		return nullptr;
	}

	return m_pkItems[bCell];
}

bool CSafebox::MoveItem(INT bCell, INT bDestCell, BYTE count)
{
	LPITEM item;

	int max_position = 5 * m_iSize;

	if (bCell >= max_position || bDestCell >= max_position)
		return false;

	if (!(item = GetItem(bCell)))
		return false;

	if (item->IsExchanging())
		return false;

	if (item->GetCount() < count)
		return false;

	{
		LPITEM item2;

		if ((item2 = GetItem(bDestCell)) && item != item2 && item2->IsStackable() &&
			!IS_SET(item2->GetAntiFlag(), ITEM_ANTIFLAG_STACK) &&
			item2->GetVnum() == item->GetVnum()) // ��ĥ �� �ִ� �������� ���
		{
			for (int i = 0; i < ITEM_SOCKET_MAX_NUM; ++i)
				if (item2->GetSocket(i) != item->GetSocket(i))
					return false;

			if (count == 0)
				count = item->GetCount();

			count = MIN(g_bItemCountLimit - item2->GetCount(), count);

			if (item->GetCount() >= count)
				Remove(bCell);

			item->SetCount(item->GetCount() - count);
			item2->SetCount(item2->GetCount() + count);

			sys_log(1, "SAFEBOX: STACK %s %d -> %d %s count %d", m_pkChrOwner->GetName(), bCell, bDestCell, item2->GetName(), item2->GetCount());
			return true;
		}

		if (!IsEmpty(bDestCell, item->GetSize()))
			return false;

		m_pkGrid->Get(bCell, 1, item->GetSize());

		if (!m_pkGrid->Put(bDestCell, 1, item->GetSize()))
		{
			m_pkGrid->Put(bCell, 1, item->GetSize());
			return false;
		}
		else
		{
			m_pkGrid->Get(bDestCell, 1, item->GetSize());
			m_pkGrid->Put(bCell, 1, item->GetSize());
		}

		sys_log(1, "SAFEBOX: MOVE %s %d -> %d %s count %d", m_pkChrOwner->GetName(), bCell, bDestCell, item->GetName(), item->GetCount());

		Remove(bCell);
		Add(bDestCell, item);
	}

	return true;
}

bool CSafebox::IsValidPosition(DWORD dwPos)
{
	if (!m_pkGrid)
		return false;

	if (dwPos >= m_pkGrid->GetSize())
		return false;

	return true;
}