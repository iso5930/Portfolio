#pragma once
#include "Define.h"
#include "BitBmp.h"

class CImageMgr
{
private:
	static CImageMgr* m_pInstance;

public:
	static CImageMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CImageMgr;

		return m_pInstance;
	}

	static void DestroyInstance(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	map<string,Image*> m_ImageMap;
	map<string,CBitBmp*> m_BmpMap;
	Graphics graphics;
	GdiplusStartupInput m_GdiplusStartupInput;
	ULONG_PTR m_GdiplusToken;

public:
	map<string,CBitBmp*>* GetBmpMap(void) { return &m_BmpMap; };
	void LoadBmp(string _pName, PTCHAR _Name)
	{
		m_BmpMap.insert( make_pair(_pName, (new CBitBmp)->LoadBmp(_Name)));
	}

	void LoadImage(string _pName, PTCHAR _Name)
	{
		m_ImageMap.insert(make_pair(_pName,new Image(_Name)));
	}

	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize)
	{
		Graphics graphics2(_hdc);
		graphics2.DrawImage(&(*m_ImageMap[_pName]), _ImageSize, 0, 0, _ImageSize.Width, _ImageSize.Height, UnitPixel);
	}

	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize, int _iX, int _iY)
	{
		Graphics graphics2(_hdc);
		graphics2.DrawImage(&(*m_ImageMap[_pName]), _ImageSize, _iX * _ImageSize.Width, _iY * _ImageSize.Height, _ImageSize.Width, _ImageSize.Height, UnitPixel);
	}

	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize, int _iX, int _iY, int _Wihth, int _Height)
	{
		Graphics graphics2(_hdc);
		graphics2.DrawImage(&(*m_ImageMap[_pName]), _ImageSize, _iX * _Wihth, _iY * _Height, _Wihth, _Height, UnitPixel);
	}
	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize, int _iXsrc, int _iYsrc, int _R, int _G, int _B)
	{
		TransparentBlt(_hdc, (int)_ImageSize.X, (int)_ImageSize.Y, (int)_ImageSize.Width, (int)_ImageSize.Height, m_BmpMap[_pName]->GetMemDC(), int(_iXsrc * _ImageSize.Width), int(_iYsrc * _ImageSize.Height), (int)_ImageSize.Width, (int)_ImageSize.Height, RGB(_R,_G,_B));
	}

	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize, int _iXsrc, int _iYsrc, int _iWidth, int _iHeight, int _R, int _G, int _B)
	{
		TransparentBlt(_hdc, (int)_ImageSize.X, (int)_ImageSize.Y, (int)_ImageSize.Width, (int)_ImageSize.Height, m_BmpMap[_pName]->GetMemDC(), int(_iXsrc), int(_iYsrc), (int)_iWidth, (int)_iHeight, RGB(_R,_G,_B));
	}

	void ImageRender(HDC _hdc, string _pName, Rect _ImageSize, int _iXsrc, int _iYsrc, int _iWidth, int _iHeight, int _R, int _G, int _B, bool _yes)
	{
		TransparentBlt(_hdc, (int)_ImageSize.X, (int)_ImageSize.Y, (int)_ImageSize.Width, (int)_ImageSize.Height, m_BmpMap[_pName]->GetMemDC(), int(_iXsrc) * _iWidth, int(_iYsrc) * _iHeight, (int)_iWidth, (int)_iHeight, RGB(_R,_G,_B));
	}

public:
	void Init();
	int Progress();
	void Render();
	void Release();
	
private:
	CImageMgr(void);

public:
	~CImageMgr(void);
};