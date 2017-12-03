#pragma once
#include "Obj.h"

class CMyButton : public CObj
{
private:
	int m_iImage;
	Rect m_ImageSize;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMyButton(void);
	CMyButton(string strName, float _fX, float _fY, float _fCX, float _fCY);
	~CMyButton(void);
};