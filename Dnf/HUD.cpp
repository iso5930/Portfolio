#include "StdAfx.h"
#include "HUD.h"
#include "ImageMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "Inven.h"
#include "Store.h"

CHUD::CHUD(void)
	:CObj("HUD", 400, 555, 800, 91)
{

}

CHUD::~CHUD(void)
{
	Release();
}

void CHUD::Init(void)
{
	CObj::Progress();
	CImageMgr::GetInstance()->LoadBmp("HP",L"../Image/UI/HP.bmp");
	CImageMgr::GetInstance()->LoadBmp("MP",L"../Image/UI/MP.bmp");
	CImageMgr::GetInstance()->LoadBmp("QuickSlot", L"../Image/UI/QuickSlot.bmp");
	CImageMgr::GetInstance()->LoadBmp("SkillQuickSlot", L"../Image/UI/SkillQuickSlot.bmp");
	CImageMgr::GetInstance()->LoadBmp("SkillQuick", L"../Image/Icon/IconSkill.bmp");
	
	m_HpSize.X = m_ImageSize.X + 13;
	m_HpSize.Y = m_ImageSize.Y + 15;
	m_HpSize.Height = 56;
	m_HpSize.Width = 56;

	//hp
	m_MpSize.X = m_ImageSize.X + 732;
	m_MpSize.Y = m_ImageSize.Y + 15;
	m_MpSize.Height = 56;
	m_MpSize.Width = 56;

	//mp
	m_fHpCurrY = 0;
	m_fHpCurrHeight = 0;
	m_fMpCurrY = 0;
	m_fMpCurrHeight = 0;

	m_QuickSlot.X = m_ImageSize.X + 105;
	m_QuickSlot.Y = m_ImageSize.Y + 68;
	m_QuickSlot.Width = 156;
	m_QuickSlot.Height = 7;

	m_SkillQuickSlot.X = m_ImageSize.X + 558;
	m_SkillQuickSlot.Y = m_ImageSize.Y + 68;
	m_SkillQuickSlot.Width = 156;
	m_SkillQuickSlot.Height = 7;

	m_QuickSlotCollision.left = m_ImageSize.X + 85;
	m_QuickSlotCollision.top = m_ImageSize.Y + 48;
	m_QuickSlotCollision.right = m_ImageSize.X + 265;
	m_QuickSlotCollision.bottom = m_ImageSize.Y + 78;

	m_iQuickSlotIndex = 0;
	
	for(int i = 0; i < 6; ++i)
	{
		m_vecQuickSlot.push_back(new CItem("Item", (i * 30) + float(m_ImageSize.X + 85), float(m_ImageSize.Y + 49), 28, 28));
		m_vecQuickSlot.back()->SetItemType(ITEM_NONE);
		m_vecQuickSlot.back()->SetItemRare(ITEM_NORMAL);
	}
	
	m_dwClickTime = GetTickCount();
	m_dwChangeTime = GetTickCount();
	m_bWindow = false;
	m_bMouseClick = false;
}

int CHUD::Progress(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();
	HpAndMpSync();
	QuickSlotSync();
	POINT ptMouse = CMouse::GetMousePos();

	if(!dwKey)
	{
		if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
		{
			CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
			((CStore*)pTemp)->SetWindow(false);
			
		}
		CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
		((CInven*)pTemp)->SetWindow(false);
		
		if(m_bMouseClick)
		{
			CObj* pInven = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();

			vector<CItem*>::iterator iter = ((CInven*)pInven)->GetInven()->begin();
			vector<CItem*>::iterator iter_end = ((CInven*)pInven)->GetInven()->end();

			for(iter; iter != iter_end; ++iter)
			{
				RECT rcInven = { (long)(*iter)->GetInfo()->fX, (long)(*iter)->GetInfo()->fY, (long)(*iter)->GetInfo()->fX + 28, (long)(*iter)->GetInfo()->fY + 28 };
				if(PtInRect(&rcInven, ptMouse))
				{	
					CItem* pTemp = (*iter);
					(*iter) = m_vecQuickSlot[m_iQuickSlotIndex];
					m_vecQuickSlot[m_iQuickSlotIndex] = pTemp;
					break;
				}
			}
		}
		m_bMouseClick = false;	
		//여기서 만약 인벤토리와 닿았다면
	}

	if(m_bWindow == false)
	{
		if(m_bMouseClick == false)
		{
			for(int i = 0; i < 6; ++i)
			{
				if(m_vecQuickSlot[i]->GetItemType() == ITEM_NONE)
					continue;

				RECT rcQuick = { long(m_vecQuickSlot[i]->GetInfo()->fX), long(m_vecQuickSlot[i]->GetInfo()->fY),
					long(m_vecQuickSlot[i]->GetInfo()->fX + ITEMCX), long(m_vecQuickSlot[i]->GetInfo()->fY + ITEMCY) };

				if(PtInRect(&rcQuick, ptMouse))
				{
					m_iQuickSlotIndex = i;
					if(dwKey & KEY_LBUTTON)
					{
						m_dwClickTime = GetTickCount();
						m_bMouseClick = true;
						if(!CObjMgr::GetInstance()->GetList()[OBJ_STORE].empty())
						{
							CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_STORE].front();
							((CStore*)pTemp)->SetWindow(true);
						}
						CObj* pTemp = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
						((CInven*)pTemp)->SetWindow(true);
						((CInven*)pTemp)->SetMouseClick(true);
					}
					if(dwKey & KEY_RBUTTON)
					{
						m_dwClickTime = GetTickCount();
						if(m_dwChangeTime + 300 < GetTickCount())
						{
							m_dwChangeTime = GetTickCount();
							CObj* pInven = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
							vector<CItem*>* vecpInven = ((CInven*)pInven)->GetEqip();
							CItem* pTemp = m_vecQuickSlot[m_iQuickSlotIndex];
							switch(m_vecQuickSlot[m_iQuickSlotIndex]->GetItemType())
							{
							case ITEM_SHOULDER:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[0];				
								vecpInven->begin()[0] = pTemp;
								break;
							case ITEM_ARMOR:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[1];				
								vecpInven->begin()[1] = pTemp;
								break;

							case ITEM_PANTS:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[2];				
								vecpInven->begin()[2] = pTemp;
								break;

							case ITEM_BELT:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[3];				
								vecpInven->begin()[3] = pTemp;
								break;

							case ITEM_SHOES:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[4];				
								vecpInven->begin()[4] = pTemp;
								break;

							case ITEM_WEAPON:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[5];				
								vecpInven->begin()[5] = pTemp;
								break;

							case ITEM_RING:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[6];
								vecpInven->begin()[6] = pTemp;
								break;

							case ITEM_NECKLACE:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[7];
								vecpInven->begin()[7] = pTemp;
								break;

							case ITEM_BRACELET:
								m_vecQuickSlot[m_iQuickSlotIndex] = vecpInven->begin()[8];
								vecpInven->begin()[8] = pTemp;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			m_vecQuickSlot[m_iQuickSlotIndex]->GetInfo()->fX = float(ptMouse.x - (ITEMCX / 2));
			m_vecQuickSlot[m_iQuickSlotIndex]->GetInfo()->fY = float(ptMouse.y - (ITEMCY / 2));
		}
	}

	if(dwKey & KEY_1)
	{
		QuickItemUse(0);
	}

	if(dwKey & KEY_2)
	{
		QuickItemUse(1);
	}

	if(dwKey & KEY_3)
	{
		QuickItemUse(2);
	}

	if(dwKey & KEY_4)
	{
		QuickItemUse(3);
	}

	if(dwKey & KEY_5)
	{
		QuickItemUse(4);
	}

	if(dwKey & KEY_6)
	{
		QuickItemUse(5);
	}
	
	return 0;
}

void CHUD::Render(HDC _hdc)
{
	CImageMgr::GetInstance()->ImageRender(_hdc, m_strName, m_ImageSize, 0, 0, 255, 0, 255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "HP", m_HpSize, 0, (int)m_fHpCurrY, 56, (int)m_fHpCurrHeight, 255, 0, 255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "MP", m_MpSize, 0, (int)m_fMpCurrY, 56,  (int)m_fMpCurrHeight, 255, 0, 255);

	ITEM_ITER iter = m_vecQuickSlot.begin();
	ITEM_ITER iter_end = m_vecQuickSlot.end();
	
	for(iter; iter != iter_end; ++iter)
	{
		(*iter)->Render(_hdc);
	}

	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(538, 558, 28, 28),5,0,255,255,255); //1번

	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(538, 523, 28, 28),7,0,255,255,255); //1번
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(568, 523, 28, 28),6,0,255,255,255); //1번
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(568, 558, 28, 28),0,0,255,255,255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(598, 558, 28, 28),4,0,255,255,255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(628, 558, 28, 28),1,0,255,255,255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(658, 558, 28, 28),2,0,255,255,255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuick", Rect(688, 558, 28, 28),3,0,255,255,255);


	

	//vector<CSkill*>::iterator iter2 = m_vecSkillSlot.begin();
	//vector<CSkill*>::iterator iter_end2 = m_vecSkillSlot.end();

	//for(iter2; iter2 != iter_end2; ++iter2)
	//{
	//	(*iter2)->Render(_hdc);
	//}
	
	CImageMgr::GetInstance()->ImageRender(_hdc, "QuickSlot", m_QuickSlot, 0, 0, 255, 0 ,255);
	CImageMgr::GetInstance()->ImageRender(_hdc, "SkillQuickSlot", m_SkillQuickSlot, 0, 0, 255, 0 ,255);

	//Rectangle(_hdc,m_ImageSize.X + 536, m_ImageSize.Y + 48, m_ImageSize.X + 716, m_ImageSize.Y + 78 ); //스킬창 퀵슬롯.
	
}

void CHUD::Release(void)
{
	ITEM_ITER iter = m_vecQuickSlot.begin();
	ITEM_ITER iter_end = m_vecQuickSlot.end();
	
	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_vecQuickSlot.clear();

	vector<CSkill*>::iterator iter2 = m_vecSkillSlot.begin();
	vector<CSkill*>::iterator iter_end2 = m_vecSkillSlot.end();

	for(iter2; iter2 != iter_end2; ++iter2)
	{
		SAFE_DELETE(*iter);
	}
	m_vecSkillSlot.clear();	
}

void CHUD::QuickSlotSync(void)
{
	for(int i = 0; i < 6; ++i)
	{
		m_vecQuickSlot[i]->GetInfo()->fX = (i * 30) + float(m_ImageSize.X + 85);
		m_vecQuickSlot[i]->GetInfo()->fY = float(m_ImageSize.Y + 49);
	}
}

void CHUD::HpAndMpSync(void)
{
	CObj* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();

	PlayerInfo* tPlayerInfo = ((CPlayer*)pPlayer)->GetPlayerInfo();

	float fHPPersent =	(float)100 - (((float)tPlayerInfo->iHp / (float)tPlayerInfo->iMaxHp) * 100); //전체 체력에 대한 비율 
	float fMPPersent = (float)100 - (((float)tPlayerInfo->iMp / (float)tPlayerInfo->iMaxMp) * 100);

	float fHPPersent2 = (56 * fHPPersent / 100);
	float fMPPersent2 = (56 * fMPPersent / 100);

	m_HpSize.Y = int((m_ImageSize.Y + 15) + fHPPersent2);
	m_MpSize.Y = int((m_ImageSize.Y + 15) + fMPPersent2);

	m_HpSize.Height = int(56 - fHPPersent2);
	m_MpSize.Height = int(56 - fMPPersent2);

	m_fHpCurrHeight = 56 - fHPPersent2;
	m_fMpCurrHeight = 56 - fMPPersent2;

	m_fHpCurrY = fHPPersent2;
	m_fMpCurrY = fMPPersent2;
}

void CHUD::QuickItemUse(int _iIndex)
{
	CObj* pInven = CObjMgr::GetInstance()->GetList()[OBJ_INVEN].front();
	vector<CItem*>* vecpInven = ((CInven*)pInven)->GetEqip();
	CItem* pTemp = m_vecQuickSlot[_iIndex];
	switch(m_vecQuickSlot[_iIndex]->GetItemType())
	{
	case ITEM_SHOULDER:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[0];				
		vecpInven->begin()[0] = pTemp;
		break;
	case ITEM_ARMOR:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[1];				
		vecpInven->begin()[1] = pTemp;
		break;

	case ITEM_PANTS:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[2];				
		vecpInven->begin()[2] = pTemp;
		break;

	case ITEM_BELT:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[3];				
		vecpInven->begin()[3] = pTemp;
		break;

	case ITEM_SHOES:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[4];				
		vecpInven->begin()[4] = pTemp;
		break;

	case ITEM_WEAPON:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[5];				
		vecpInven->begin()[5] = pTemp;
		break;

	case ITEM_RING:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[6];
		vecpInven->begin()[6] = pTemp;
		break;

	case ITEM_NECKLACE:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[7];
		vecpInven->begin()[7] = pTemp;
		break;

	case ITEM_BRACELET:
		m_vecQuickSlot[_iIndex] = vecpInven->begin()[8];
		vecpInven->begin()[8] = pTemp;
		break;
	}
}	