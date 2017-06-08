#pragma once
#include "stdafx.h"
#include "LoginDlg.h"

CLoginDlg::CLoginDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
}

CLoginDlg::~CLoginDlg()
{
}
//TODO:消息映射
void CLoginDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}
void CLoginDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CLoginDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CLoginDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}
void CLoginDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;

	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");

	if (!pBtnMax || !pBtnRestore) return;

	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}
int CLoginDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}
struct flashtime {
	int timeEnd;
	wchar_t szFlash[50];
}g_flashs[] =
{
	{ 0, L"morning.swf" },
	{ 8,L"noon.swf" },
	{ 12,L"afternoon.swf" },
	{ 18,L"night.swf" }
};
BOOL CLoginDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	//初始化flash控件
	SFlashCtrl * pFlash = FindChildByName2<SFlashCtrl>(L"flash_bkgnd");
	if (pFlash)
	{
		wchar_t szCurDir[MAX_PATH + 1];
		GetCurrentDirectoryW(MAX_PATH, szCurDir);

		time_t long_time;
		time(&long_time);
		struct tm * t = localtime(&long_time);

		wchar_t szFlash[MAX_PATH];
		for (int i = 3; i >= 0; i--)
		{
			if (t->tm_hour >= g_flashs[i].timeEnd)
			{
				swprintf(szFlash, L"%s\\flash\\%s", szCurDir, g_flashs[i].szFlash);
				break;
			}
		}
		pFlash->Play(szFlash);
	}

	return 0;
}