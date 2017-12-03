#pragma once
#include "obj.h"

class CInterFace : public CObj
{
private:
	DWORD m_dwTime;
	vector<int> m_vecDamage;
	int m_iDamage;
	bool m_bCri;
	int m_iSize;

	Frame m_Frame;

public:
	void SetDamage(int _Damage) { m_iDamage = _Damage; };
	vector<int>* GetDamage(void) { return &m_vecDamage; };
	void SetCri(bool _Cri) { m_bCri = _Cri; };

public:
	virtual void Init(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CInterFace(void);
	virtual ~CInterFace(void);
};