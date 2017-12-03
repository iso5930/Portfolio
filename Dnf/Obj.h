#pragma once

#include "Define.h"

class CObj
{
protected:
	tagInfo m_tInfo;
	string	m_strName;
	Rect	m_ImageSize;
	RECT	m_Collision;
	RECT	m_AttCollision;
	RECT	m_ShadowCollision;
	Rect	m_ShadowSize;

public:
	virtual void Init(void)		PURE;
	virtual int Progress(void)	PURE;
	virtual void Render(HDC _hdc)	PURE;
	virtual void Release(void)	PURE;

public:
	RECT GetRect(void);
	void SetPos(float _fX, float _fY);
	tagInfo* GetInfo(void) { return &m_tInfo; }
	RECT GetAttCollision(void) { return m_AttCollision; };
	RECT GetCollision(void) { return m_Collision; };
	RECT GetShadowCollision(void) { return m_ShadowCollision; };
	string GetName(void) { return m_strName; };

public:
	CObj(void);
	CObj(string strName, float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CObj(void);
};