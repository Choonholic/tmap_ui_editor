// OutputBar.h

#pragma once

class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();
	virtual	~COutputBar();

	void	SetMultipleAdd(BOOL bSet = FALSE, BOOL bUpdateNow = TRUE);
	int		AddString(LPCSTR lpszFunction, LPCTSTR lpszFormat, ...);
	BOOL	IsEmpty();
	void	Clean();
	BOOL	Save(LPCTSTR lpszFileName);

protected:
	CListBox	m_wndList;
	BOOL		m_bMultipleAdd;

	afx_msg	int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg	void	OnSize(UINT nType, int cx, int cy);
	afx_msg	void	OnPaint();

	int	AddStringInternal(LPCTSTR lpszString);

	DECLARE_MESSAGE_MAP()
};
