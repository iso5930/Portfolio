#include "StdAfx.h"
#include "Obj.h"

CObj::CObj(void)
{

}
CObj::CObj(string strName, float _fX, float _fY, float _fCX, float _fCY)
	:m_tInfo(_fX, _fY, _fCX, _fCY), m_strName(strName)
{
	m_tInfo.fJumpY = 0;
}

CObj::~CObj(void)
{

}
int CObj::Progress(void)
{
	if(m_strName == "PlayerLeft" || m_strName == "PlayerRight" || m_strName == "Matacow_LEFT" || 
		m_strName == "Matacow_RIGHT" || m_strName == "Void" || m_strName == "BlackHole" 
		|| m_strName == "Thunder" || m_strName == "IceField" || m_strName == "Halloween" 
		|| m_strName == "Blood_Left" || m_strName == "Blood_Right"
		|| m_strName == "Cow_Left" || m_strName == "Cow_Right" || m_strName == "Boom"
		|| m_strName == "MonsterSkil")
	{
		m_ImageSize.X = int(m_tInfo.fX - m_tInfo.fCX / 2) - g_Scroll.x;
		m_ImageSize.Y = int(m_tInfo.fY - m_tInfo.fCY / 2) + (int)m_tInfo.fJumpY;
		m_ImageSize.Width = int(m_tInfo.fCX);
		m_ImageSize.Height = int(m_tInfo.fCY);
	}
	else
	{
		m_ImageSize.X = int(m_tInfo.fX - m_tInfo.fCX / 2);
		m_ImageSize.Y = int(m_tInfo.fY - m_tInfo.fCY / 2) + (int)m_tInfo.fJumpY;
		m_ImageSize.Width = int(m_tInfo.fCX);
		m_ImageSize.Height = int(m_tInfo.fCY);
	}

	if(m_strName == "Seria")
	{
		m_Collision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 55);
		m_Collision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 55);
		m_Collision.top = long((m_tInfo.fY - m_tInfo.fCY / 2) + 20);
		m_Collision.bottom = long((m_tInfo.fY + m_tInfo.fCY / 2) - 20);
	}

	else if(m_strName == "PlayerLeft" || m_strName == "PlayerRight") 
	{
		m_Collision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 70);
		m_Collision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 70);
		m_Collision.top = long((m_tInfo.fY - m_tInfo.fCY / 2) + 80);
		m_Collision.bottom = long((m_tInfo.fY + m_tInfo.fCY / 2) - 26);
		
		m_ShadowCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 95);
		m_ShadowCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 95);
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 164;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 26;

		m_ShadowSize.X = long((m_tInfo.fX - m_tInfo.fCX / 2) + 60) - g_Scroll.x;
		m_ShadowSize.Y = long(m_tInfo.fY - m_tInfo.fCY / 2) + 160;
		m_ShadowSize.Width = 82;
		m_ShadowSize.Height = 25;

		//플레이어 충돌 박스.		
	}
	else if(m_strName == "Matacow_LEFT" || m_strName == "Matacow_RIGHT")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 183;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 174;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 94;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 90;
		
		m_ShadowCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 288);
		m_ShadowCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 240);
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 329;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 90;

		if(m_strName == "Matacow_RIGHT")
		{
			m_ShadowSize.X = (m_ShadowCollision.left - g_Scroll.x);
			m_ShadowSize.Y = m_ShadowCollision.top;
			m_ShadowSize.Width = 195;
			m_ShadowSize.Height = 75;
		}
		else
		{
			m_ShadowSize.X = (m_ShadowCollision.left - g_Scroll.x) + 20;
			m_ShadowSize.Y = m_ShadowCollision.top - 30;
			m_ShadowSize.Width = 195;
			m_ShadowSize.Height = 75;
		}
	}
	else if(m_strName == "Blood_Left" || m_strName == "Blood_Right")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 50;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 56;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 33;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 20;
		
		m_ShadowCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 71);
		m_ShadowCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 71);
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 99;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2)- 20;
	}
	else if(m_strName == "Cow_Left" || m_strName == "Cow_Right")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 160;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 132;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 110;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 150;
		
		m_ShadowCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 186);
		m_ShadowCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 164);
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 240;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 152;
	}
	else if(m_strName == "Void")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 20;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 20;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 20;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 20;
		
		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 20;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 20;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 90;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 20;
	}
	else if(m_strName == "BlackHole")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 72;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 72;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 72;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 72;
		
		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 157;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 157;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 247;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 72;
	}
	else if(m_strName == "Thunder")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 180;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 180;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2);
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 20;

		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 290;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 552;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 290;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 36;
	}
	else if(m_strName == "IcePallat")
	{
		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 287;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 395;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) + 7;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) + 122;
	}
	else if(m_strName == "Elemental")
	{
		m_Collision.left = long(m_tInfo.fX + m_tInfo.fCX / 2) - 15;
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) + 38;
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 130;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) + 130;

		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 229;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 352;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) + 10;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) + 123;
	}
	else if(m_strName == "Halloween")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + (long)m_tInfo.fJumpY;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) + (long)m_tInfo.fJumpY;
		
		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 55;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 55;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 92;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 23;
	}
	else if(m_strName == "Boom")
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + (long)m_tInfo.fJumpY;
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) + (long)m_tInfo.fJumpY;
		
		m_ShadowCollision.left = long(m_tInfo.fX - m_tInfo.fCX / 2) + 148;
		m_ShadowCollision.right = long(m_tInfo.fX + m_tInfo.fCX / 2) - 148;
		m_ShadowCollision.top = long(m_tInfo.fY - m_tInfo.fCY / 2) + 148;
		m_ShadowCollision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2) - 148;
	}
	else
	{
		m_Collision.left = long(m_tInfo.fX - m_tInfo.fCX / 2);
		m_Collision.right = long(m_tInfo.fX + m_tInfo.fCX / 2);
		m_Collision.top = long(m_tInfo.fY - m_tInfo.fCY / 2);
		m_Collision.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2);
	}

	if(m_strName == "PlayerLeft")
	{
		m_AttCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2));
		m_AttCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2) - 90);
		m_AttCollision.top = long((m_tInfo.fY - m_tInfo.fCY / 2) + 80);
		m_AttCollision.bottom = long((m_tInfo.fY + m_tInfo.fCY / 2) - 26);
	}
	else if(m_strName == "PlayerRight")
	{
		m_AttCollision.left = long((m_tInfo.fX - m_tInfo.fCX / 2) + 90);
		m_AttCollision.right = long((m_tInfo.fX + m_tInfo.fCX / 2));
		m_AttCollision.top = long((m_tInfo.fY - m_tInfo.fCY / 2) + 80);
		m_AttCollision.bottom = long((m_tInfo.fY + m_tInfo.fCY / 2) - 26);
	}
	return 0;
}

RECT CObj::GetRect(void)
{
	RECT	rcObj =
	{
		long(m_tInfo.fX - m_tInfo.fCX / 2),
		long(m_tInfo.fY - m_tInfo.fCY / 2),
		long(m_tInfo.fX + m_tInfo.fCX / 2),
		long(m_tInfo.fY + m_tInfo.fCY / 2),
	};

	return rcObj;
}

void CObj::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}