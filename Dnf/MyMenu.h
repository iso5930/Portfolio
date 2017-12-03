#pragma once
#include "scene.h"
#include "BitBmp.h"
#include "MyButton.h"

class CMyMenu : public CScene
{
private:
	CBitBmp m_BackBuffer;
	Rect	m_ImageSize;
	list<CMyButton*> m_ButtonList;

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMyMenu(void);
	virtual ~CMyMenu(void);
};