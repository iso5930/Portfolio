#include "StdAfx.h"
#include "BitBmp.h"
#include "Define.h"

CBitBmp::CBitBmp(void)
{

}

CBitBmp::~CBitBmp(void)
{
	Release();
}

CBitBmp* CBitBmp::LoadBmp(PTCHAR pFileName)
{
	m_hdc	= GetDC(g_hwnd);				//도화지를 얻어온다.
	m_MemDc = CreateCompatibleDC(m_hdc);	//또다른 DC를만들어서 덮어씌우기 용도로 사용하는것.
	
	m_bitmap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP,
						0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);		//경로 찾아가서 로드하는부분.

	if(!m_bitmap)
		MessageBox(g_hwnd, pFileName, L"이미지 로드 실패!", NULL);			//만약에 파일이 없으면 활성.

	m_oldbitmap = (HBITMAP)SelectObject(m_MemDc, m_bitmap);

	ReleaseDC(g_hwnd, m_hdc);

	return this;
}

void CBitBmp::Release(void)
{
	SelectObject(m_MemDc, m_oldbitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_MemDc);
}