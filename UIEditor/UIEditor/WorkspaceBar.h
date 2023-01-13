// WorkspaceBar.h

#pragma once

#ifndef	WSI_ICONS
#define	WSI_ICONS
#define	WSI_GROUP			0x00
#define	WSI_PAGE			0x01
#define	WSI_CTRL_ENABLE		0x02
#define	WSI_IMAGE			0x03
#define	WSI_CTRL_DISABLE	0x04
#define	WSI_INVALID			0xFF
#endif

class CWorkspaceBar : public CBCGPDockingControlBar
{
public:
	CWorkspaceBar();
	virtual	~CWorkspaceBar();

	void		BuildTree();
	void		FindItem(DWORD dwData, HTREEITEM &hFound, HTREEITEM hRoot = NULL);
	void		FindItem(LPCTSTR lpszItem, HTREEITEM &hFound, HTREEITEM hRoot = NULL);

	HTREEITEM	FindCurrentItem();
	BOOL		Select(DWORD dwItem);

	void		SelectItem();
	void		UpdateItem(LPCTSTR lpszItem, int nImage = WSI_INVALID);
	void		DeleteItem();

protected:
	CTreeCtrl	m_wndTree;
	CImageList	m_lstTree;

	afx_msg	int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg	void	OnSize(UINT nType, int cx, int cy);
	afx_msg	void	OnPaint();
	afx_msg	void	OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg	void	OnTvnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};
