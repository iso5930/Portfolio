#include "StdAfx.h"
#include "CollisionMgr.h"
#include "Player.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "Monster.h"
#include "Factory.h"
#include "InterFace.h"
#include "MonsterHp.h"
#include "Combo.h"

CCollisionMgr* CCollisionMgr::m_pInstance = NULL;

CCollisionMgr::CCollisionMgr(void)
{

}

CCollisionMgr::~CCollisionMgr(void)
{

}

void CCollisionMgr::Init(void)
{
	m_dwHitTime = GetTickCount();
}

bool CCollisionMgr::RectToRect(RECT _Rect1, RECT _Rect2)
{
	if(_Rect1.left <= _Rect2.right && _Rect1.right >= _Rect2.left && _Rect1.top <= _Rect2.bottom && _Rect1.bottom >= _Rect2.top)
		return true;
	else
		return false;	

	return false;
}

int CCollisionMgr::Progress(void)
{
	RECT rcPlayer = ((CPlayer*)m_pPlayer)->GetShadowCollision();
	INFO* m_pInfo = m_pPlayer->GetInfo();
	
	vector<TILE*>::iterator iter = m_vecTile->begin();
	vector<TILE*>::iterator iter_end = m_vecTile->end();

	//플레이어 vs 타일.
	for(iter; iter != iter_end; ++iter)
	{
		if((*iter)->m_eOption == TILE_BLOCK)
		{
			RECT rcSource = { long((*iter)->m_fX), long((*iter)->m_fY), long((*iter)->m_fX + (*iter)->m_fCX), long((*iter)->m_fY + (*iter)->m_fCY) };

			RECT rcDist;

			if(IntersectRect(&rcDist, &rcPlayer, &rcSource))
			{
				float fPlayerX = float(rcPlayer.left + ((rcPlayer.right - rcPlayer.left) / 2));
				float fPlayerY = float(rcPlayer.bottom - ((rcPlayer.bottom - rcPlayer.top) / 2));
				float fSourceX = (*iter)->m_fX + ((*iter)->m_fCX / 2);
				float fSourceY = (*iter)->m_fY + ((*iter)->m_fCY / 2);

				float fDistX = abs(fPlayerX - fSourceX);
				float fDistY = abs(fPlayerY - fSourceY);

				float fOverlabX = ((rcPlayer.right - rcPlayer.left) / 2) + ((*iter)->m_fCX / 2) - fDistX;
				float fOverlabY = ((rcPlayer.bottom - rcPlayer.top) / 2) + ((*iter)->m_fCY / 2) - fDistY;

				if(fPlayerY < fSourceY)// 내가 위쪽
				{
					if(fOverlabX > fOverlabY)	//위쪽에서 부딪혔다.
					{
						m_pPlayer->SetPos(m_pInfo->fX, m_pInfo->fY - fOverlabY);
						continue;
					}
				}
				else
				{
					if(fOverlabX > fOverlabY) //밑에서
					{
						m_pPlayer->SetPos(m_pInfo->fX, m_pInfo->fY + fOverlabY);
						continue;
					}
				}
				if(fPlayerX > fSourceX) //오른쪽
				{
					m_pPlayer->SetPos(m_pInfo->fX + fOverlabX, m_pInfo->fY);
				}
				else
				{
					m_pPlayer->SetPos(m_pInfo->fX - fOverlabX, m_pInfo->fY);
				}
			}
		}			
	}
	((CPlayer*)m_pPlayer)->CObjProgress();

	ePLAYER_STATE ePlayerState = ((CPlayer*)m_pPlayer)->GetPlayerState();	

	if(ePlayerState == PLAYER_ATTACK1 || ePlayerState == PLAYER_ATTACK2 || ePlayerState == PLAYER_ATTACK3)
	{
		list<CObj*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
		list<CObj*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
		rcPlayer = ((CPlayer*)m_pPlayer)->GetAttCollision();


		if(m_dwHitTime + 500 < GetTickCount())
		{
			m_dwHitTime = GetTickCount();

			for(iter; iter != iter_end; ++iter)
			{
				float fDistY = abs((*iter)->GetInfo()->fY - m_pPlayer->GetInfo()->fY);

				if(fDistY >= 30)
				{
					RECT rcSource = (*iter)->GetCollision();

					RECT rcDist;

					if(IntersectRect(&rcDist, &rcPlayer, &rcSource))
					{
						int iAtt = rand() % 999999;
						((CMonster*)(*iter))->GetMonInfo()->iHp -= iAtt;
						CObjMgr::GetInstance()->GetList()[OBJ_INTERFACE].push_back(CFactory<CInterFace>::CreateObj((*iter)->GetInfo()->fX, (*iter)->GetInfo()->fY, iAtt, false));
						CObj* pObj = CObjMgr::GetInstance()->GetList()[OBJ_MONSTERHP].front();
						((CMonsterHp*)pObj)->SetMonsterHp((*iter));
						pObj = CObjMgr::GetInstance()->GetList()[OBJ_COMBO].front();
						((CCombo*)pObj)->SetComboTime(GetTickCount());
						((CCombo*)pObj)->AddCombo();
						((CBoss*)(*iter))->SetMonState(MONSTER_HIT);
					}
				}
			}
		}
	}
	return 0;
}