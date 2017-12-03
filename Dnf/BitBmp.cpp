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
	m_hdc	= GetDC(g_hwnd);				//��ȭ���� ���´�.
	m_MemDc = CreateCompatibleDC(m_hdc);	//�Ǵٸ� DC������ ������ �뵵�� ����ϴ°�.
	
	m_bitmap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP,
						0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);		//��� ã�ư��� �ε��ϴºκ�.

	if(!m_bitmap)
		MessageBox(g_hwnd, pFileName, L"�̹��� �ε� ����!", NULL);			//���࿡ ������ ������ Ȱ��.

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