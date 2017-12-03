#include "StdAfx.h"
#include "Store.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Factory.h"
#include "Inven.h"

CStore::CStore(void)
	:CObj("Store",300,200,368,464) //CObj("Store",200,200,368,464)
{

}

CStore::~CStore(void)
{
	Release();
}


void CStore::Init(void)
{
	m_bShowStore = false;
	CImageMgr::GetInstance()->LoadBmp("Store", L"../Image/UI/Store.bmp");
	CImageMgr::GetInstance()->LoadBmp("Item", L"../Image/Item/ItemTest.bmp");
	m_fDragX = 0;
	dwBuyTime = GetTickCount();
	
	CObj::Progress();

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			m_vecStore.push_back(new CItem("Item",float(j * 170) + m_ImageSize.X + 16, float(i * 59) + m_ImageSize.Y + 84, 170, 59, true));
		}
	}//아이템 생성.

	m_vecStore[0]->SetItemInfo(ItemInfo(L"이기의스태프",1000,200));
	m_vecStore[0]->SetItemType(ITEM_WEAPON);
	m_vecStore[0]->SetItemRare(ITEM_NORMAL);

	m_vecStore[1]->SetItemInfo(ItemInfo(L"다크고스 상의",0,100,1,500,300));
	m_vecStore[1]->SetItemType(ITEM_ARMOR);
	m_vecStore[1]->SetItemRare(ITEM_NORMAL);

	m_vecStore[2]->SetItemInfo(ItemInfo(L"다크고스 하의",0,120,1,600,400));
	m_vecStore[2]->SetItemType(ITEM_PANTS);
	m_vecStore[2]->SetItemRare(ITEM_NORMAL);

	m_vecStore[3]->SetItemInfo(ItemInfo(L"다크고스 샌들",0,150,1,500,300));
	m_vecStore[3]->SetItemType(ITEM_SHOES);
	m_vecStore[3]->SetItemRare(ITEM_NORMAL);

	m_vecStore[4]->SetItemInfo(ItemInfo(L"다크고스 숄더",0,100,1,500,300));
	m_vecStore[4]->SetItemType(ITEM_SHOULDER);
	m_vecStore[4]->SetItemRare(ITEM_NORMAL);

	m_vecStore[5]->SetItemInfo(ItemInfo(L"다크고스 벨트",0,100,1,500,300));
	m_vecStore[5]->SetItemType(ITEM_BELT);
	m_vecStore[5]->SetItemRare(ITEM_NORMAL);

	m_vecStore[6]->SetItemInfo(ItemInfo(L"스탭 오브 위저드",900,150));
	m_vecStore[6]->SetItemType(ITEM_WEAPON);
	m_vecStore[6]->SetItemRare(ITEM_RARE);

	m_vecStore[7]->SetItemInfo(ItemInfo(L"라이트니스 오토 상의",0,100,1,500,300));
	m_vecStore[7]->SetItemType(ITEM_ARMOR);
	m_vecStore[7]->SetItemRare(ITEM_RARE);

	m_vecStore[8]->SetItemInfo(ItemInfo(L"파이어니스 오토 하의",0,100,1,500,300));
	m_vecStore[8]->SetItemType(ITEM_PANTS);
	m_vecStore[8]->SetItemRare(ITEM_RARE);

	m_vecStore[9]->SetItemInfo(ItemInfo(L"윈드니스 오토 신발",0,100,1,500,300));
	m_vecStore[9]->SetItemType(ITEM_SHOES);
	m_vecStore[9]->SetItemRare(ITEM_RARE);

	m_vecStore[10]->SetItemInfo(ItemInfo(L"블랙니스 오토 어깨",0,100,1,500,300));
	m_vecStore[10]->SetItemType(ITEM_SHOULDER);
	m_vecStore[10]->SetItemRare(ITEM_RARE);

	m_vecStore[11]->SetItemInfo(ItemInfo(L"아이니스 오토 벨트",0,100,1,500,300));
	m_vecStore[11]->SetItemType(ITEM_BELT);
	m_vecStore[11]->SetItemRare(ITEM_RARE);

	m_bWindow = false;
	m_dwClickTime = GetTickCount();

	m_ItemBuyCollision.left = m_ImageSize.X;
	m_ItemBuyCollision.top = m_ImageSize.Y;
	m_ItemBuyCollision.right = m_ImageSize.X + m_ImageSize.Width;
	m_ItemBuyCollision.bottom = m_ImageSize.Y + m_ImageSize.Height;

	//아이템 셋팅
}

int CStore::Progress(void)
{
	if(m_bShowStore == false)
	{
		m_tInfo.fX = 220;
		m_tInfo.fY = 280;
		CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
		((CInven*)pTemp)->SetWindow(false);
		return 0;
	}
	
	CObj::Progress();

	SetCollision();
	
	POINT ptMouse = CMouse::GetMousePos();

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!dwKey)
	{
		CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
		m_fDragX = abs(ptMouse.x - m_tInfo.fX);
		((CInven*)pTemp)->SetWindow(false);
	}

	if(m_bWindow == false)
	{
		if(PtInRect(&m_ExitCollision,ptMouse))
		{
			if(dwKey & KEY_LBUTTON)
			{
				m_dwClickTime = GetTickCount();
				m_bShowStore = false;
			}
		}//종료
	}

	if(m_bWindow == false)
	{
		if(PtInRect(&m_MoveCollision,ptMouse))
		{
			CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
			((CInven*)pTemp)->SetWindow(true);
			if(dwKey & KEY_LBUTTON)
			{
				m_dwClickTime = GetTickCount();
				if(m_tInfo.fX > ptMouse.x)
				{
					m_tInfo.fX = ptMouse.x + m_fDragX;
				}
				else
				{
					m_tInfo.fX = ptMouse.x - m_fDragX;
				}
				m_tInfo.fY = float(ptMouse.y) + 225;
			}
		}
	}

	//창 이동
	if(m_bWindow == false)
	{
		for(int i = 0; i < 6; ++i)
		{
			for(int j = 0; j < 2; ++j)
			{
				int iIndex = j + i * 2;

				RECT rc = { long(m_vecStore[iIndex]->GetInfo()->fX), long(m_vecStore[iIndex]->GetInfo()->fY),
					long(m_vecStore[iIndex]->GetInfo()->fX + ITEMCX), long(m_vecStore[iIndex]->GetInfo()->fY + ITEMCY) };

				if(PtInRect(&rc,ptMouse))
				{
					m_vecStore[iIndex]->SetShowInfo(true);
					//여기서는 팝업창!!
					//여긴 아이템 구매
					if(dwKey & KEY_LBUTTON && dwBuyTime + 300 < GetTickCount())
					{
						m_dwClickTime = GetTickCount();
						TCHAR TempName[100] = L"";
						lstrcat(TempName,m_vecStore[iIndex]->GetItemInfo()->szName);
						lstrcat(TempName,L" 1개 구입 \n\n정말 구매하시겠습니까?");
						if(MessageBox(g_hwnd,TempName,L"알림",MB_YESNO) == IDYES)
						{
							dwBuyTime = GetTickCount();
							CItem* pItem = new CItem;
							pItem->Init();
							pItem->SetItemInfo((*m_vecStore[iIndex]->GetItemInfo()));
							pItem->SetStoreItem(false);
							pItem->SetItemType(m_vecStore[iIndex]->GetItemType());
							pItem->SetItemRare(m_vecStore[iIndex]->GetItemRare());
							CObj* pInven = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
							((CInven*)pInven)->AddItem(pItem);
						}
					}
				}
			}
		}
	}
	//아이템 구매

	return 0;
}

void CStore::Render(HDC _hdc)
{
	if(m_bShowStore == false)
		return;

	CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize,0,0,255,0,255);

	ITEM_ITER iter = m_vecStore.begin();
	ITEM_ITER iter_end = m_vecStore.end();

	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->Render(_hdc);
	}
}

void CStore::Release(void)
{
	ITEM_ITER iter = m_vecStore.begin();
	ITEM_ITER iter_end = m_vecStore.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecStore.clear();
}

void CStore::SetCollision(void)
{
	m_ExitCollision.left = (m_ImageSize.X + m_ImageSize.Width) - 30;
	m_ExitCollision.right = m_ImageSize.X + m_ImageSize.Width;
	m_ExitCollision.top = m_ImageSize.Y;
	m_ExitCollision.bottom = m_ImageSize.Y + 32;
	//종료키 보정

	m_MoveCollision.left = m_ImageSize.X;
	m_MoveCollision.right = m_ImageSize.X + m_ImageSize.Width;
	m_MoveCollision.top = m_ImageSize.Y;
	m_MoveCollision.bottom = m_ImageSize.Y + 32;
	//드래그 콜리전 보정

	m_ItemBuyCollision.left = m_ImageSize.X;
	m_ItemBuyCollision.top = m_ImageSize.Y;
	m_ItemBuyCollision.right = m_ImageSize.X + m_ImageSize.Width;
	m_ItemBuyCollision.bottom = m_ImageSize.Y + m_ImageSize.Height;

	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			int iIndex = j + i * 2;
			m_vecStore[iIndex]->GetInfo()->fX = float(j * 170) + m_ImageSize.X + 16;
			m_vecStore[iIndex]->GetInfo()->fY = float(i * 59) + m_ImageSize.Y + 84;
		}
	}//아이템 위치 보정
	

	/*m_ItemBuyCollision.left = (m_ImageSize.X);
	m_ItemBuyCollision.right = m_ImageSize.X + 353;
	m_ItemBuyCollision.top = m_ImageSize.Y + 80;
	m_ItemBuyCollision.bottom = m_ImageSize.Y + 430;*/
}