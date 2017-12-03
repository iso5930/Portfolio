#include "StdAfx.h"
#include "Inven.h"
#include "ImageMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "Store.h"
#include "HUD.h"
#include "SoundMgr.h"


CInven::CInven(void)
	:CObj("Inven", 600, 290, 258, 521)
{

}

CInven::~CInven(void)
{
	Release();
}

void CInven::Init(void)
{
	m_bShowInven = false;
	m_fDistX = 0;

	CObj::Progress();
	for(int i = 0; i < 7; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			m_vecInven.push_back(new CItem("Item",float(j * 30) + m_ImageSize.X + 11, float(i * 30) + m_ImageSize.Y + 226, 30, 30));
			m_vecInven.back()->SetItemType(ITEM_NONE);
			m_vecInven.back()->SetItemRare(ITEM_NORMAL);
			m_iIndex = 0;
		}
	}
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 13), float(m_ImageSize.Y + 65), 30, 30)); //어깨
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 45), float(m_ImageSize.Y + 65), 30, 30)); //상의
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 13), float(m_ImageSize.Y + 97), 30, 30)); //하의
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 45), float(m_ImageSize.Y + 97), 30, 30)); //벨트
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 13), float(m_ImageSize.Y + 129), 30, 30)); //신발
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 187), float(m_ImageSize.Y + 65), 30, 30)); //무기
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 219), float(m_ImageSize.Y + 129), 30, 30)); //반지
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 219), float(m_ImageSize.Y + 97), 30, 30)); //목걸이
	m_vecEquip.push_back(new CItem("Item", float(m_ImageSize.X + 187), float(m_ImageSize.Y + 97), 30, 30)); //팔찌
	
	m_vecInven[0]->SetItemInfo(ItemInfo(L"이기의스태프",1000,200));
	m_vecInven[0]->SetItemType(ITEM_WEAPON);
	m_vecInven[0]->SetItemRare(ITEM_NORMAL);

	m_vecInven[1]->SetItemInfo(ItemInfo(L"다크고스 상의",0,100,1,500,300));
	m_vecInven[1]->SetItemType(ITEM_ARMOR);
	m_vecInven[1]->SetItemRare(ITEM_NORMAL);

	m_vecInven[2]->SetItemInfo(ItemInfo(L"다크고스 하의",0,120,1,600,400));
	m_vecInven[2]->SetItemType(ITEM_PANTS);
	m_vecInven[2]->SetItemRare(ITEM_NORMAL);

	m_vecInven[3]->SetItemInfo(ItemInfo(L"다크고스 샌들",0,150,1,500,300));
	m_vecInven[3]->SetItemType(ITEM_SHOES);
	m_vecInven[3]->SetItemRare(ITEM_NORMAL);

	m_vecInven[4]->SetItemInfo(ItemInfo(L"다크고스 숄더",0,100,1,500,300));
	m_vecInven[4]->SetItemType(ITEM_SHOULDER);
	m_vecInven[4]->SetItemRare(ITEM_NORMAL);

	m_vecInven[5]->SetItemInfo(ItemInfo(L"다크고스 벨트",0,100,1,500,300));
	m_vecInven[5]->SetItemType(ITEM_BELT);
	m_vecInven[5]->SetItemRare(ITEM_NORMAL);
	
	m_vecInven[6]->SetItemInfo(ItemInfo(L"무한한 탐식의 잔재",0,100,1,500,300));
	m_vecInven[6]->SetItemType(ITEM_RING);
	m_vecInven[6]->SetItemRare(ITEM_NORMAL);

	m_vecInven[7]->SetItemInfo(ItemInfo(L"무한한 탐식의 형상",0,100,1,500,300));
	m_vecInven[7]->SetItemType(ITEM_NECKLACE);
	m_vecInven[7]->SetItemRare(ITEM_NORMAL);

	m_vecInven[8]->SetItemInfo(ItemInfo(L"무한한 탐식의 얼개",0,100,1,500,300));
	m_vecInven[8]->SetItemType(ITEM_BRACELET);
	m_vecInven[8]->SetItemRare(ITEM_NORMAL);
	

	ITEM_ITER iter = m_vecEquip.begin();
	ITEM_ITER iter_end = m_vecEquip.end();

	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->SetItemType(ITEM_NONE);
		(*iter)->SetItemRare(ITEM_NORMAL);
	}
	m_dwEqipTime = GetTickCount();
	m_MouseClick = false;
	m_bItemSwap = false;
	m_bEquip = false;
	m_bWindow = false;

	m_EquipCollision.left = m_ImageSize.X + 10;
	m_EquipCollision.top = m_ImageSize.Y + 63;
	m_EquipCollision.right = m_ImageSize.X + 250;
	m_EquipCollision.bottom = m_ImageSize.Y + 180;
	m_dwClickTime = GetTickCount();
}

int CInven::Progress(void)
{
	if(m_bShowInven == false)
	{
		m_tInfo.fX = 600;
		m_tInfo.fY = 290;
		if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
		{
			CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
			((CStore*)pTemp)->SetWindow(false);
		}
		return 0;
	}

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	POINT ptMouse = CMouse::GetMousePos();
	
	if(!dwKey)
	{	
		m_fDistX = abs(ptMouse.x - m_tInfo.fX);
		m_MouseClick = false;
		if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
		{
			CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
			((CStore*)pTemp)->SetWindow(false);
		}
		CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_HUD].front();
		((CHUD*)pTemp)->SetWindow(false);

		if(m_bItemSwap)
		{
			for(int i = 0; i < 7; ++i)
			{
				for(int j = 0; j < 8; ++j)
				{
					int iIndex = j + i * 8;
					RECT ItemCollision = { long(m_vecInven[iIndex]->GetInfo()->fX), long(m_vecInven[iIndex]->GetInfo()->fY), 
								long(m_vecInven[iIndex]->GetInfo()->fX + ITEMCX), long(m_vecInven[iIndex]->GetInfo()->fY + ITEMCY) };
							
					if(PtInRect(&ItemCollision, ptMouse))
					{
						CItem* pTemp = m_vecInven[m_iIndex];
						m_vecInven[m_iIndex] = m_vecInven[iIndex];
						m_vecInven[iIndex] = pTemp;
						m_bItemSwap = false;
					}
				}
			}
						
			if(PtInRect(&m_EquipCollision, ptMouse))
			{
				CSoundMgr::GetInstance()->PlayEffect(L"scrap_touch.ogg");
				CItem* pTemp = m_vecInven[m_iIndex];
				switch(m_vecInven[m_iIndex]->GetItemType())
				{
				case ITEM_SHOULDER:
					m_vecInven[m_iIndex] = m_vecEquip[0];				
					m_vecEquip[0] = pTemp;
					break;
				case ITEM_ARMOR:
					m_vecInven[m_iIndex] = m_vecEquip[1];				
					m_vecEquip[1] = pTemp;
					break;

				case ITEM_PANTS:
					m_vecInven[m_iIndex] = m_vecEquip[2];				
					m_vecEquip[2] = pTemp;
					break;

				case ITEM_BELT:
					m_vecInven[m_iIndex] = m_vecEquip[3];				
					m_vecEquip[3] = pTemp;
					break;

				case ITEM_SHOES:
					m_vecInven[m_iIndex] = m_vecEquip[4];				
					m_vecEquip[4] = pTemp;
					break;

				case ITEM_WEAPON:
					m_vecInven[m_iIndex] = m_vecEquip[5];				
					m_vecEquip[5] = pTemp;
					break;

				case ITEM_RING:
					m_vecInven[m_iIndex] = m_vecEquip[6];
					m_vecEquip[6] = pTemp;
					break;

				case ITEM_NECKLACE:
					m_vecInven[m_iIndex] = m_vecEquip[7];
					m_vecEquip[7] = pTemp;
					break;

				case ITEM_BRACELET:
					m_vecInven[m_iIndex] = m_vecEquip[8];
					m_vecEquip[8] = pTemp;
					break;
				}
			}
			if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
			{
				CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
				if(PtInRect(&((CStore*)pTemp)->GetBuyCollision(),ptMouse))
				{
					TCHAR TempName[100] = L"";
					lstrcat(TempName,m_vecInven[m_iIndex]->GetItemInfo()->szName);
					lstrcat(TempName,L" 1개 판매 \n\n정말 판매하시겠습니까?");
					if(MessageBox(g_hwnd,TempName,L"알림",MB_YESNO) == IDYES)
					{
						m_vecInven[m_iIndex]->SetItemType(ITEM_NONE);
						m_vecInven[m_iIndex]->SetItemRare(ITEM_NORMAL);
					}
				}//아이템 판매
			}

			//퀵슬롯으로 가는거
			pTemp = CObjMgr::GetInstance()->GetList()[OBJ_HUD].front();
			vector<CItem*>::iterator iter = ((CHUD*)pTemp)->GetQuickSlot()->begin();
			vector<CItem*>::iterator iter_end = ((CHUD*)pTemp)->GetQuickSlot()->end();

			for(iter; iter != iter_end; ++iter)
			{
				RECT rcQuickSlot = { (long)(*iter)->GetInfo()->fX, (long)(*iter)->GetInfo()->fY, (long)(*iter)->GetInfo()->fX + 28, (long)(*iter)->GetInfo()->fY + 28 };
				if(PtInRect(&rcQuickSlot, ptMouse))
				{	
					CItem* pTemp = (*iter);
					(*iter) = m_vecInven[m_iIndex];
					m_vecInven[m_iIndex] = pTemp;
				}
			}
		}
		if(m_bEquip)
		{
			for(int i = 0; i < 7; ++i)
			{
				for(int j = 0; j < 8; ++j)
				{
					int iIndex = j + i * 8;
					RECT ItemCollision = { long(m_vecInven[iIndex]->GetInfo()->fX), long(m_vecInven[iIndex]->GetInfo()->fY), 
								long(m_vecInven[iIndex]->GetInfo()->fX + ITEMCX), long(m_vecInven[iIndex]->GetInfo()->fY + ITEMCY) };

					if(PtInRect(&ItemCollision, ptMouse))
					{
						CSoundMgr::GetInstance()->PlayEffect(L"icondrop.ogg");
						CItem* pTemp = m_vecInven[iIndex];
						m_vecInven[iIndex] = m_vecEquip[m_iEquitIndex];
						m_vecEquip[m_iEquitIndex] = pTemp;
						m_bEquip = false;
					}
				}
			}
		}
	}
	CObj::Progress();
	
	m_MoveCollision.left = m_ImageSize.X;
	m_MoveCollision.right = m_ImageSize.X + m_ImageSize.Height / 2;
	m_MoveCollision.top = m_ImageSize.Y;
	m_MoveCollision.bottom = m_ImageSize.Y + 32;

	if(m_bWindow == false)
	{
		if(m_MouseClick == false)
		{
			if(PtInRect(&m_ExitCollision,ptMouse))
			{
				if(dwKey & KEY_LBUTTON)
				{
					m_dwClickTime = GetTickCount();
					m_bShowInven = false;
				}
			}
			if(PtInRect(&m_MoveCollision, ptMouse))
			{
				if(dwKey & KEY_LBUTTON)
				{
					if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
					{	
						CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
						((CStore*)pTemp)->SetWindow(true);
					}
					m_dwClickTime = GetTickCount();
					if(m_tInfo.fX > ptMouse.x)
					{
						m_tInfo.fX = ptMouse.x + m_fDistX;
					}
					else
					{
						m_tInfo.fX = ptMouse.x - m_fDistX;
					}
					m_tInfo.fY = float(ptMouse.y + 245);
				}
			}//아이템 창 드래그.
		}

		ItemInfoSync();

		if(m_MouseClick == false)
		{
			for(int i = 0; i < 7; ++i)
			{
				for(int j = 0; j < 8; ++j)
				{
					m_iIndex = j + i * 8;

					if(m_vecInven[m_iIndex]->GetItemType() == ITEM_NONE)
						continue;

					RECT ItemCollision = { long(m_vecInven[m_iIndex]->GetInfo()->fX), long(m_vecInven[m_iIndex]->GetInfo()->fY), 
						long(m_vecInven[m_iIndex]->GetInfo()->fX + ITEMCX), long(m_vecInven[m_iIndex]->GetInfo()->fY + ITEMCY) };
					
					if(PtInRect(&ItemCollision, ptMouse))
					{
						m_vecInven[m_iIndex]->SetShowInfo(true);
						
						if(dwKey & KEY_LBUTTON)
						{
							CSoundMgr::GetInstance()->PlayEffect(L"mouseover.ogg");
							if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
							{	
								CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
								((CStore*)pTemp)->SetWindow(true);
							}
							CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_HUD].front();
							((CHUD*)pTemp)->SetWindow(true);
							m_dwClickTime = GetTickCount();
							m_MouseClick = true;
							m_bItemSwap = true;
							
							return 0;
						}
						if(dwKey & KEY_RBUTTON)
						{
							m_dwClickTime = GetTickCount();
							if(m_dwEqipTime + 300 < GetTickCount())
							{
								m_dwEqipTime = GetTickCount();
								CItem* pTemp = m_vecInven[m_iIndex];
								switch(m_vecInven[m_iIndex]->GetItemType())
								{
								case ITEM_SHOULDER:
									m_vecInven[m_iIndex] = m_vecEquip[0];				
									m_vecEquip[0] = pTemp;
									break;
								case ITEM_ARMOR:
									m_vecInven[m_iIndex] = m_vecEquip[1];				
									m_vecEquip[1] = pTemp;
									break;

								case ITEM_PANTS:
									m_vecInven[m_iIndex] = m_vecEquip[2];				
									m_vecEquip[2] = pTemp;
									break;

								case ITEM_BELT:
									m_vecInven[m_iIndex] = m_vecEquip[3];				
									m_vecEquip[3] = pTemp;
									break;

								case ITEM_SHOES:
									m_vecInven[m_iIndex] = m_vecEquip[4];				
									m_vecEquip[4] = pTemp;
									break;

								case ITEM_WEAPON:
									m_vecInven[m_iIndex] = m_vecEquip[5];				
									m_vecEquip[5] = pTemp;
									break;
									
								case ITEM_RING:
									m_vecInven[m_iIndex] = m_vecEquip[6];
									m_vecEquip[6] = pTemp;
									break;

								case ITEM_NECKLACE:
									m_vecInven[m_iIndex] = m_vecEquip[7];
									m_vecEquip[7] = pTemp;
									break;

								case ITEM_BRACELET:
									m_vecInven[m_iIndex] = m_vecEquip[8];
									m_vecEquip[8] = pTemp;
									break;
								}
							}
						}
					}
				}
			}
			for(int i = 0; i < 9; ++i)
			{
				m_iEquitIndex = i;

				if(m_vecEquip[m_iEquitIndex]->GetItemType() == ITEM_NONE)
					continue;

				RECT ItemCollision = { long(m_vecEquip[m_iEquitIndex]->GetInfo()->fX), long(m_vecEquip[m_iEquitIndex]->GetInfo()->fY), 
					long(m_vecEquip[m_iEquitIndex]->GetInfo()->fX + ITEMCX), long(m_vecEquip[m_iEquitIndex]->GetInfo()->fY + ITEMCY) };
				
				if(PtInRect(&ItemCollision, ptMouse))
				{
					if(dwKey & KEY_LBUTTON)
					{
						if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
						{
							CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
							((CStore*)pTemp)->SetWindow(true);
						}
						m_dwClickTime = GetTickCount();
						m_MouseClick = true;
						m_bEquip = true;
						return 0;
					}
					if(dwKey & KEY_RBUTTON)
					{	
						CSoundMgr::GetInstance()->PlayEffect(L"icondrop.ogg");
						m_dwClickTime = GetTickCount();
						
						if(m_dwEqipTime + 300 < GetTickCount())
						{
							m_dwEqipTime = GetTickCount();
							ITEM_ITER iter = m_vecInven.begin();
							ITEM_ITER iter_end = m_vecInven.end();

							for(iter; iter != iter_end; ++iter)
							{
								if((*iter)->GetItemType() == ITEM_NONE)
								{
									CItem* pTemp = m_vecEquip[m_iEquitIndex];
									m_vecEquip[m_iEquitIndex] = (*iter);
									(*iter) = pTemp;
									return 0;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if(m_bEquip)
			{
				m_vecEquip[m_iEquitIndex]->GetInfo()->fX = float(ptMouse.x - (ITEMCX / 2));
				m_vecEquip[m_iEquitIndex]->GetInfo()->fY = float(ptMouse.y - (ITEMCY / 2));				
			}
			else
			{
				m_vecInven[m_iIndex]->GetInfo()->fX = float(ptMouse.x - (ITEMCX / 2));
				m_vecInven[m_iIndex]->GetInfo()->fY = float(ptMouse.y - (ITEMCY / 2));
			}
		}
	}
	
	//아이템 드래그

	return 0;
}

void CInven::Render(HDC _hdc)
{
	if(m_bShowInven == false)
		return;

	if(m_bShowInven)
	{	
		
		CImageMgr::GetInstance()->ImageRender(_hdc, "Inven", m_ImageSize,0,0,255,0,255);

		ITEM_ITER iter = m_vecInven.begin();
		ITEM_ITER iter_end = m_vecInven.end();
		
		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
			//아이템렌더
		}

		iter = m_vecEquip.begin();
		iter_end = m_vecEquip.end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
			//장비창렌더
		}

		if(m_bItemSwap)
		{
			Rect m_ItemSize;
			m_ItemSize.X = long(m_vecInven[m_iIndex]->GetInfo()->fX);
			m_ItemSize.Y = long(m_vecInven[m_iIndex]->GetInfo()->fY);
			m_ItemSize.Width = ITEMCX;
			m_ItemSize.Height = ITEMCY;
			CImageMgr::GetInstance()->ImageRender(_hdc,"Item", m_ItemSize, m_vecInven[m_iIndex]->GetItemType(), m_vecInven[m_iIndex]->GetItemRare(), 255, 0, 255);
		}
		//Rectangle(_hdc, m_ExitCollision.left, m_ExitCollision.top, m_ExitCollision.right, m_ExitCollision.bottom);
	}
}

void CInven::Release(void)
{
	ITEM_ITER iter = m_vecInven.begin();
	ITEM_ITER iter_end = m_vecInven.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecInven.clear();

	iter = m_vecEquip.begin();
	iter_end = m_vecEquip.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecEquip.clear();
}

void CInven::ItemInfoSync(void)
{
	for(int i = 0; i < 7; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			int iIndex = j + i * 8;
			m_vecInven[iIndex]->GetInfo()->fX = float(j * 30) + m_ImageSize.X + 11;
			m_vecInven[iIndex]->GetInfo()->fY = float(i * 30) + m_ImageSize.Y + 226;
		}
	}
	//아이템 위치 보정

	m_vecEquip[0]->GetInfo()->fX = float(m_ImageSize.X + 13);
	m_vecEquip[0]->GetInfo()->fY = float(m_ImageSize.Y + 65);

	m_vecEquip[1]->GetInfo()->fX = float(m_ImageSize.X + 45);
	m_vecEquip[1]->GetInfo()->fY = float(m_ImageSize.Y + 65);

	m_vecEquip[2]->GetInfo()->fX = float(m_ImageSize.X + 13);
	m_vecEquip[2]->GetInfo()->fY = float(m_ImageSize.Y + 97);

	m_vecEquip[3]->GetInfo()->fX = float(m_ImageSize.X + 45);
	m_vecEquip[3]->GetInfo()->fY = float(m_ImageSize.Y + 97);

	m_vecEquip[4]->GetInfo()->fX = float(m_ImageSize.X + 13);
	m_vecEquip[4]->GetInfo()->fY = float(m_ImageSize.Y + 129);

	m_vecEquip[5]->GetInfo()->fX = float(m_ImageSize.X + 187);
	m_vecEquip[5]->GetInfo()->fY = float(m_ImageSize.Y + 65);

	m_vecEquip[6]->GetInfo()->fX = float(m_ImageSize.X + 219);
	m_vecEquip[6]->GetInfo()->fY = float(m_ImageSize.Y + 129);

	m_vecEquip[7]->GetInfo()->fX = float(m_ImageSize.X + 219);
	m_vecEquip[7]->GetInfo()->fY = float(m_ImageSize.Y + 97);

	m_vecEquip[8]->GetInfo()->fX = float(m_ImageSize.X + 187);
	m_vecEquip[8]->GetInfo()->fY = float(m_ImageSize.Y + 97);
	//장비템 위치 보정

	m_EquipCollision.left = m_ImageSize.X + 10;
	m_EquipCollision.top = m_ImageSize.Y + 63;
	m_EquipCollision.right = m_ImageSize.X + 250;
	m_EquipCollision.bottom = m_ImageSize.Y + 180;

	m_ExitCollision.left = (m_ImageSize.X + m_ImageSize.Width) - 30;
	m_ExitCollision.right = m_ImageSize.X + m_ImageSize.Width;
	m_ExitCollision.top = m_ImageSize.Y + 5;
	m_ExitCollision.bottom = m_ImageSize.Y + 32;
	//종료키 보정
}
void CInven::AddItem(CItem* _Item)
{
	ITEM_ITER iter = m_vecInven.begin();
	ITEM_ITER iter_end = m_vecInven.end();

	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->GetItemType() == ITEM_NONE)
		{
			SAFE_DELETE(*iter);
			iter = m_vecInven.erase(iter);
			m_vecInven.insert(iter,_Item);
			break;
		}
	}
}