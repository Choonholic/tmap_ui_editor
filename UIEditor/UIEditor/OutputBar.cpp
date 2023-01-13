// OutputBar.cpp

#include "stdafx.h"
#include "UIEditor.h"
#include "OutputBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const	int	nBorderSize		= 1;
const	int	nFunctionLen	= 128;
const	int	nStringLen		= 256;

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

COutputBar::COutputBar()
{
	m_bMultipleAdd	= FALSE;
}

COutputBar::~COutputBar()
{
}

void COutputBar::SetMultipleAdd(BOOL bSet, BOOL bUpdateNow)
{
	m_bMultipleAdd	= bSet;

	if (bUpdateNow)
	{
		int	nCount	= m_wndList.GetCount();

		if (nCount > 0)
		{
			m_wndList.SetCurSel(m_wndList.GetCount() - 1);
		}
		
		m_wndList.UpdateWindow();
	}
}

int COutputBar::AddString(LPCSTR lpszFunction, LPCTSTR lpszFormat, ...)
{
	TCHAR	szString[nFunctionLen + nStringLen];
	TCHAR	szFunction[nFunctionLen];
	TCHAR	szBuffer[nStringLen];
	va_list	args;
	int		nLength;

	va_start(args, lpszFormat);

#ifdef _UNICODE
	nLength	= _vsnwprintf_s(szBuffer, nStringLen, nStringLen - 1, lpszFormat, args);

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpszFunction, -1, szFunction, nFunctionLen);
	wsprintf(szString, _T("%s - %s"), szFunction, szBuffer);
#else
	nLength	= _vsnprintf_s(szBuffer, nStringLen, nStringLen - 1, lpszFormat, args);

	strcpy_s(szFunction, nFunctionLen, lpszFunction);
	sprintf(szString, "%s - %s", szFunction, szBuffer);
#endif

	va_end(args);

	if (AddStringInternal(szString) != LB_ERR)
	{
		return nLength;
	}

	return 0;
}

BOOL COutputBar::IsEmpty()
{
	return ((BOOL)(m_wndList.GetCount() == 0));
}

void COutputBar::Clean()
{
	if (!IsEmpty())
	{
		m_wndList.ResetContent();
		UpdateWindow();
	}
}

BOOL COutputBar::Save(LPCTSTR lpszFileName)
{
	HANDLE	hFile;
	TCHAR	szBuffer[nStringLen + 3];
	int		lp;
	int		nLen;
	DWORD	dwWritten;

	hFile	= CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	szBuffer[0] = 0xFEFF;

	WriteFile(hFile, szBuffer, sizeof(TCHAR), &dwWritten, NULL);

	for (lp = 0; lp < m_wndList.GetCount(); lp++)
	{
		m_wndList.GetText(lp, szBuffer);

		nLen	= static_cast<int>(_tcslen(szBuffer));

		szBuffer[nLen + 0]	= _T('\r');
		szBuffer[nLen + 1]	= _T('\n');
		szBuffer[nLen + 2]	= NULL;

		nLen	+= 2;

		WriteFile(hFile, szBuffer, sizeof(TCHAR) * nLen, &dwWritten, NULL);
	}

	FlushFileBuffers(hFile);
	CloseHandle(hFile);

	return TRUE;
}

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	CRect	rectDummy;

	rectDummy.SetRectEmpty();

	const	DWORD	dwViewStyle	= LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	
	if (!m_wndList.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Output View\n");
		return -1;
	}

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_wndList.SetWindowPos(NULL, nBorderSize, nBorderSize, cx - 2 * nBorderSize, cy - 2 * nBorderSize, SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::OnPaint() 
{
	CPaintDC	dc(this);
	CRect		rectList;

	m_wndList.GetWindowRect(rectList);
	ScreenToClient(rectList);
	rectList.InflateRect(1, 1);
	dc.Draw3dRect(rectList, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

int COutputBar::AddStringInternal(LPCTSTR lpszString)
{
	if (lpszString == NULL)
	{
		return LB_ERR;
	}

	int	nCurrent	= m_wndList.AddString(lpszString);

	if (nCurrent != LB_ERR)
	{
		if (m_bMultipleAdd == FALSE)
		{
			m_wndList.SetCurSel(nCurrent);
			m_wndList.UpdateWindow();
		}
	}

#ifdef _DEBUG
	::OutputDebugString(lpszString);
	::OutputDebugString(_T("\n"));
#endif

	return nCurrent;
}
