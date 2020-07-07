#ifndef __INC_METIN_II_GAME_SHOP_H__
#define __INC_METIN_II_GAME_SHOP_H__
#include "../../common/service.h"

enum
{
	SHOP_MAX_DISTANCE = 1000
};

class CGrid;

/* ---------------------------------------------------------------------------------- */
class CShop
{
public:
	typedef struct shop_item
	{
		BYTE	pos;
		DWORD	vnum;		// ������ ��ȣ
		long	price;		// ����
#ifdef ENABLE_CHEQUE_SYSTEM
		long	price_cheque;
#endif

		BYTE	count;		// ������ ����

		LPITEM	pkItem;
		int		itemid;		// ������ �������̵�
		
#ifdef ENABLE_SOLD_ITEM_SYSTEM
		int		isSold;
#endif
#ifdef ENABLE_BUY_WITH_ITEM
		DWORD witemVnum;
#endif

		shop_item()
		{
			vnum = 0;
			price = 0;
#ifdef ENABLE_CHEQUE_SYSTEM
			price_cheque = 0;
#endif

			count = 0;
			itemid = 0;
			pkItem = nullptr;
			
#ifdef ENABLE_SOLD_ITEM_SYSTEM
			isSold = 0;
#endif
#ifdef ENABLE_BUY_WITH_ITEM
			witemVnum = 0;
#endif
		}
	} SHOP_ITEM;

	CShop();
	~CShop();

	bool	Create(DWORD dwVnum, DWORD dwNPCVnum, TShopItemTable* pItemTable);
	void	SetShopItems(TShopItemTable* pItemTable, BYTE bItemCount);
	void	SetShopItemsPrivateShop(TShopItemTable* pItemTable, BYTE bItemCount);

	virtual void		SetPCShop(LPCHARACTER ch) { m_pkPC = ch; };
	virtual LPCHARACTER GetPCShop() { return m_pkPC; }
	virtual bool		IsPCShop() { return m_pkPC ? true : false; };

	// �Խ�Ʈ �߰�/����
	virtual bool	AddGuest(LPCHARACTER ch, DWORD owner_vid, bool bOtherEmpire);
	void	RemoveGuest(LPCHARACTER ch);
#ifdef ENABLE_ADVANCED_RELOAD_SYSTEM
	void	RemoveAllGuests();
#endif

	// ���� ����
	virtual int	Buy(LPCHARACTER ch, BYTE pos, bool isSearchBuy = false);

	// �Խ�Ʈ���� ��Ŷ�� ����
	void	BroadcastUpdateItem(BYTE pos);

	// �Ǹ����� �������� ������ �˷��ش�.
	int		GetNumberByVnum(DWORD dwVnum);

	// �������� ������ ��ϵǾ� �ִ��� �˷��ش�.
	virtual bool	IsSellingItem(DWORD itemID);

	DWORD	GetVnum() { return m_dwVnum; }
	DWORD	GetNPCVnum() { return m_dwNPCVnum; }

	std::vector<SHOP_ITEM>	GetItemVector() { return m_itemVector; }
	
#ifdef ENABLE_SOLD_ITEM_SYSTEM
	DWORD GetSoldItemVnum(BYTE pos);
	BYTE GetSoldCount(BYTE pos);
#ifdef ENABLE_CHANGELOOK_SYSTEM
	BYTE GetSoldTransmutation(BYTE pos);
#endif
	long GetSoldPrice(BYTE pos, BYTE type);
	const long* GetSoldSockets(BYTE pos);
	const TPlayerItemAttribute* GetSoldAttributes(BYTE pos);
	const char* GetSoldNewOwner(BYTE pos);
#endif

#ifdef ENABLE_ZODIAC_TEMPLE_SYSTEM
	void	BroadcastUpdateItemCh(BYTE pos, LPCHARACTER ch);
#endif

protected:
	void	Broadcast(const void* data, int bytes);

#ifdef ENABLE_OFFLINE_SHOP_SYSTEM
public:
	int		GetItemCount();
	bool	GetItems();
	void	SetLocked(bool val) { m_bLocked = val; }
	bool	IsLocked() { return m_bLocked; }
	void	RemoveGuests(LPCHARACTER except = nullptr);
	void	ClearItems();
	void	SetPrivShopItems(std::vector<TShopItemTable*> map_shop);
	void	Refresh();
	LPCHARACTER GetPC() { return m_pkPC; }
protected:
	bool					m_bLocked;
#endif

protected:
	DWORD				m_dwVnum;
	DWORD				m_dwNPCVnum;
	CGrid* m_pGrid;

	typedef TR1_NS::unordered_map<LPCHARACTER, bool> GuestMapType;
	GuestMapType m_map_guest;
	std::vector<SHOP_ITEM>		m_itemVector;	// �� �������� ����ϴ� ���ǵ�

	LPCHARACTER m_pkPC;
	#ifdef ENABLE_ZODIAC_TEMPLE_SYSTEM
	bool m_IsLimitedItemShop;
	#endif
	
#ifdef ENABLE_SHOP_SEEN
	std::vector<DWORD> bakanlar;
#endif
	
#ifdef ENABLE_SOLD_ITEM_SYSTEM
	typedef struct shop_sold_info
	{
		CShop*	lpShop;
		DWORD	vnum;
		long	Price;
		long	price_cheque;
		BYTE	Count;
#ifdef ENABLE_CHANGELOOK_SYSTEM
		int		Transmutation;
#endif
		long	alSockets[ITEM_SOCKET_MAX_NUM];
		TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
		std::string	newOwner;
	} SShopSoldData;
	std::map<BYTE, SShopSoldData> m_SoldItems;
#endif
};

#endif
