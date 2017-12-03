#pragma once
#include "obj.h"

class CCombo : public CObj
{
private:
	int m_iSize;
	vector<int> m_vecCombo;
	int m_iCombo;
	DWORD m_dwComboTime;

public:
	void SetComboTime(DWORD _dwTime) { m_dwComboTime = _dwTime; };
	void AddCombo(void) { ++m_iCombo; };

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CCombo(void);
	virtual ~CCombo(void);
};