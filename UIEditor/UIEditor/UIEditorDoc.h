// UIEditorDoc.h

#pragma once

#include "UIStruct.h"
#include "ArrayX.h"

#ifndef	WSU_TYPES
#define WSU_TYPES
#define	WSU_FULL		0x00
#define WSU_SELECT		0x01
#define	WSU_STATE		0x02
#define WSU_DELETE		0x03
#endif

class CUIEditorDoc : public CDocument
{
	DECLARE_DYNCREATE(CUIEditorDoc)

protected:
	CUIEditorDoc();

public:
	virtual	~CUIEditorDoc();

	static	CUIEditorDoc*	GetUIDocument();

	virtual	BOOL	OnNewDocument();
	virtual	BOOL	OnOpenDocument(LPCTSTR lpszPathName);
	virtual	BOOL	OnSaveDocument(LPCTSTR lpszPathName);
	virtual	void	Serialize(CArchive& ar);
	virtual	void	DeleteContents();

	void	Initialize();

	DWORD	GetNewGroupID();
	DWORD	GetNewPageID();
	DWORD	GetNewCtrlID();
	DWORD	GetNewImageID();

	DWORD	GetGroupByID(DWORD dwID);
	DWORD	GetPageByID(DWORD dwID);
	DWORD	GetCtrlByID(DWORD dwID);
	DWORD	GetImageByID(DWORD dwID);
	BOOL	GetImageFullPath(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS, BOOL bMustExist);
	BOOL	GetImageFileName(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS);

	DWORD	GetMGroupByID(DWORD dwID);
	DWORD	GetMPageByID(DWORD dwID);
	DWORD	GetMCtrlByID(DWORD dwID);
	DWORD	GetMImageByID(DWORD dwID);
	BOOL	GetMImageFullPath(CString& strImageName, UI_IMAGEC& UIImageC, UI_IMAGES& UIImageS, BOOL bMustExist);

	BOOL	AddGroup(USHORT uWidth, USHORT uHeight, DWORD dwBaseID = UI_INVALIDID);
	BOOL	DeleteGroup();
	BOOL	RenameGroup(LPCTSTR lpszNewName);

	BOOL	AddPage();
	BOOL	DeletePage();
	BOOL	RenamePage(LPCTSTR lpszNewName);
	BOOL	MovePageToTop();
	BOOL	MovePageUp();
	BOOL	MovePageDown();
	BOOL	MovePageToBottom();
	BOOL	GeneratePage();

	BOOL	AddCtrl();
	BOOL	DeleteCtrl();
	BOOL	RenameCtrl(LPCTSTR lpszNewName);
	BOOL	MoveCtrlToTop();
	BOOL	MoveCtrlUp();
	BOOL	MoveCtrlDown();
	BOOL	MoveCtrlToBottom();

	BOOL	AddImage(LPCTSTR lpszImageFile);
	BOOL	DeleteImage();
	BOOL	RenameImage(LPCTSTR lpszNewName);
	BOOL	MoveImageToTop();
	BOOL	MoveImageUp();
	BOOL	MoveImageDown();
	BOOL	MoveImageToBottom();

	void	UpdateWorkspace(int nUpdateType);
	void	UpdateProperties();

	BOOL	SaveImageBuffer(CArchive &ar, LPCTSTR lpszFileName, int nType, DWORD dwSize);
	BOOL	LoadImageBuffer(CArchive &ar, LPCTSTR lpszFileName, int nType, DWORD dwSize);

	BOOL	SaveImageBuffer(CFile &file, LPCTSTR lpszFileName, int nType, DWORD dwSize);
	BOOL	LoadImageBuffer(CFile &file, LPCTSTR lpszFileName, int nType, DWORD dwSize);

	BOOL	ResizeImage(LPCTSTR lpszNewFileName, LPCTSTR lpszOldFileName, int nType, int nNewWidth, int nNewHeight, DWORD &dwSize, DWORD &dwMaskSize);

	BOOL	SaveDatabaseImage(HANDLE hStream, LPCTSTR lpszFileName, int nType, UINT &uSize, UINT &uMaskSize, BOOL bCompress = TRUE);

	void	ClearSelection();
	void	ClearClipboard();
	void	ClearMergeData();

	afx_msg	void	OnFileMerge();
	afx_msg	void	OnFileDBExport();
	afx_msg void	OnFileImageExport();
	afx_msg void	OnFileImageImport();
	afx_msg	void	OnEditCopy();
	afx_msg	void	OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg	void	OnEditPaste();
	afx_msg	void	OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg	void	OnEditClear();
	afx_msg	void	OnUpdateEditClear(CCmdUI* pCmdUI);
	afx_msg	void	OnActionGroupAdd();
	afx_msg	void	OnActionGroupDelete();
	afx_msg	void	OnUpdateActionGroupDelete(CCmdUI* pCmdUI);
	afx_msg	void	OnActionGroupActive();
	afx_msg	void	OnUpdateActionGroupActive(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageAdd();
	afx_msg	void	OnUpdateActionPageAdd(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageDelete();
	afx_msg	void	OnUpdateActionPageDelete(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageMoveTop();
	afx_msg	void	OnUpdateActionPageMoveTop(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageMoveUp();
	afx_msg	void	OnUpdateActionPageMoveUp(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageMoveDown();
	afx_msg	void	OnUpdateActionPageMoveDown(CCmdUI* pCmdUI);
	afx_msg void	OnActionPageMoveBottom();
	afx_msg	void	OnUpdateActionPageMoveBottom(CCmdUI* pCmdUI);
	afx_msg	void	OnActionPageGenerate();
	afx_msg	void	OnUpdateActionPageGenerate(CCmdUI* pCmdUI);
	afx_msg	void	OnActionCtrlAdd();
	afx_msg	void	OnUpdateActionCtrlAdd(CCmdUI* pCmdUI);
	afx_msg void	OnActionCtrlDelete();
	afx_msg	void	OnUpdateActionCtrlDelete(CCmdUI* pCmdUI);
	afx_msg void	OnActionCtrlMoveTop();
	afx_msg	void	OnUpdateActionCtrlMoveTop(CCmdUI* pCmdUI);
	afx_msg void	OnActionCtrlMoveUp();
	afx_msg	void	OnUpdateActionCtrlMoveUp(CCmdUI* pCmdUI);
	afx_msg void	OnActionCtrlMoveDown();
	afx_msg	void	OnUpdateActionCtrlMoveDown(CCmdUI* pCmdUI);
	afx_msg void	OnActionCtrlMoveBottom();
	afx_msg	void	OnUpdateActionCtrlMoveBottom(CCmdUI* pCmdUI);
	afx_msg	void	OnActionImageAdd();
	afx_msg	void	OnUpdateActionImageAdd(CCmdUI* pCmdUI);
	afx_msg void	OnActionImageDelete();
	afx_msg	void	OnUpdateActionImageDelete(CCmdUI* pCmdUI);
	afx_msg void	OnActionImageMoveTop();
	afx_msg	void	OnUpdateActionImageMoveTop(CCmdUI* pCmdUI);
	afx_msg void	OnActionImageMoveUp();
	afx_msg	void	OnUpdateActionImageMoveUp(CCmdUI* pCmdUI);
	afx_msg void	OnActionImageMoveDown();
	afx_msg	void	OnUpdateActionImageMoveDown(CCmdUI* pCmdUI);
	afx_msg void	OnActionImageMoveBottom();
	afx_msg	void	OnUpdateActionImageMoveBottom(CCmdUI* pCmdUI);
	afx_msg	void	OnToolsLogSave();
	afx_msg	void	OnUpdateToolsLogSave(CCmdUI* pCmdUI);
	afx_msg void	OnToolsLogClean();
	afx_msg	void	OnUpdateToolsLogClean(CCmdUI* pCmdUI);
	afx_msg void	OnToolsCheck();
	afx_msg	void	OnUpdateToolsCheck(CCmdUI* pCmdUI);

#ifdef _DEBUG
	virtual	void	AssertValid() const;
	virtual	void	Dump(CDumpContext& dc) const;
#endif

	// Database
	CString	m_strFolder;
	CString	m_strFileName;

	UI_HEADER						m_tUIHeader;
	DWORD							m_dwCGroupID;
	DWORD							m_dwCPageID;
	DWORD							m_dwCCtrlID;
	DWORD							m_dwCImageID;
	int								m_nCType;
	CArray<UI_GROUP, UI_GROUP>		m_arrUIGroup;
	CArrayX<UI_PAGEC, UI_PAGEC>		m_arrUIPageC;
	CArray<UI_PAGES, UI_PAGES>		m_arrUIPageS;
	CArray<UI_CTRLC, UI_CTRLC>		m_arrUICtrlC;
	CArray<UI_CTRLS, UI_CTRLS>		m_arrUICtrlS;
	CArray<UI_IMAGEC, UI_IMAGEC>	m_arrUIImageC;
	CArray<UI_IMAGES, UI_IMAGES>	m_arrUIImageS;

	// Selection
	int								m_nSLType;
	DWORD							m_dwSLPageID;
	CDWordArray						m_arrSLCtrlID;

	// Clipboard
	int								m_nCBType;
	UI_PAGEC						m_tCBPageC;
	CArray<UI_PAGES, UI_PAGES>		m_arrCBPageS;
	CArray<UI_CTRLC, UI_CTRLC>		m_arrCBCtrlC;
	CArray<UI_CTRLS, UI_CTRLS>		m_arrCBCtrlS;
	CArray<UI_IMAGEC, UI_IMAGEC>	m_arrCBImageC;
	CArray<UI_IMAGES, UI_IMAGES>	m_arrCBImageS;

	// Merge Database
	CString	m_strMFolder;
	CString	m_strMFileName;

	UI_HEADER						m_tMUIHeader;
	CArray<UI_GROUP, UI_GROUP>		m_arrMUIGroup;
	CArray<UI_PAGEC, UI_PAGEC>		m_arrMUIPageC;
	CArray<UI_PAGES, UI_PAGES>		m_arrMUIPageS;
	CArray<UI_CTRLC, UI_CTRLC>		m_arrMUICtrlC;
	CArray<UI_CTRLS, UI_CTRLS>		m_arrMUICtrlS;
	CArray<UI_IMAGEC, UI_IMAGEC>	m_arrMUIImageC;
	CArray<UI_IMAGES, UI_IMAGES>	m_arrMUIImageS;

	DECLARE_MESSAGE_MAP()
};
