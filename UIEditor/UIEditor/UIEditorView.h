// UIEditorView.h

#pragma once

#ifndef OBJSEL_TYPE
#define	OBJSEL_TYPE
#define	OBJSEL_NORMAL		0x00
#define	OBJSEL_CURRENT		0x01
#define	OBJSEL_HIDDEN		0x02
#endif

#ifndef	EDGE_TYPE
#define	EDGE_TYPE
#define	EDGE_LEFTTOP		0x00
#define	EDGE_TOP			0x01
#define	EDGE_RIGHTTOP		0x02
#define	EDGE_RIGHT			0x03
#define	EDGE_RIGHTBOTTOM	0x04
#define	EDGE_BOTTOM			0x05
#define	EDGE_LEFTBOTTOM		0x06
#define	EDGE_LEFT			0x07
#define	EDGE_NONE			0xFF
#endif

class CUIEditorView : public CScrollView
{
	DECLARE_DYNCREATE(CUIEditorView)

protected:
	CUIEditorView();

	virtual	void	OnInitialUpdate();

public:
	virtual	~CUIEditorView();

	CUIEditorDoc*			GetDocument()	const;
	static	CUIEditorView*	GetUIView();

	virtual	void	OnDraw(CDC* pDC);
	virtual	BOOL	PreCreateWindow(CREATESTRUCT& cs);

	afx_msg	BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg	void	OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg	void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg	void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg	void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg	void	OnDropFiles(HDROP hDropInfo);

#ifdef _DEBUG
	virtual	void	AssertValid() const;
	virtual	void	Dump(CDumpContext& dc) const;
#endif

	void	DrawSelector(CDC* pDC, LPRECT lprc, int nType = OBJSEL_NORMAL);
	int		FindItemByPos(int x, int y, DWORD &dwCtrlID);
	int		IsOnEdge(int x, int y);
	void	DrawBitmap(CDC* pDC, LPCTSTR lpszFileName, int nType, LPRECT lprc);

	COLORREF	m_crView;
	COLORREF	m_crCanvas;
	COLORREF	m_crCtrl;

	BOOL		m_bShowBorder;
	BOOL		m_bShowID;
	BOOL		m_bShowText;
	BOOL		m_bFillCtrl;

	HCURSOR		m_hCursor;
	int			m_nResizeEdge;
	BOOL		m_bMove;
	BOOL		m_bResize;
	POINT		m_ptOldMove;
	POINT		m_ptOldResize;

protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CUIEditorDoc* CUIEditorView::GetDocument() const
{
	return reinterpret_cast<CUIEditorDoc*>(m_pDocument);
}
#endif
