// PropertiesBar.h

#pragma once

#ifndef PROP_IDS
#define	PROP_IDS			0x0000	// N/A
#define	PROP_GROUP_ID		0x0100
#define PROP_GROUP_NAME		0x0101
#define	PROP_GROUP_NOTE		0x0102
#define	PROP_GROUP_WIDTH	0x0103
#define	PROP_GROUP_HEIGHT	0x0104
#define	PROP_PAGE_ID		0x0200
#define	PROP_PAGE_NAME		0x0201
#define	PROP_PAGE_NOTE		0x0202
#define	PROP_PAGE_ENABLE	0x0203
#define	PROP_CTRL_ID		0x0300
#define	PROP_CTRL_NAME		0x0301
#define	PROP_CTRL_NOTE		0x0302
#define	PROP_CTRL_TEXT		0x0303
#define	PROP_CTRL_ENABLE	0x0304
#define	PROP_CTRL_TYPE		0x0305
#define PROP_CTRL_COMMON	0x0306
#define	PROP_CTRL_BG		0x0307
#define	PROP_CTRL_LEFT		0x0308
#define	PROP_CTRL_TOP		0x0309
#define	PROP_CTRL_WIDTH		0x030A
#define	PROP_CTRL_HEIGHT	0x030B
#define	PROP_CTRL_PINLEFT	0x030C
#define	PROP_CTRL_PINTOP	0x030D
#define	PROP_CTRL_PINRIGHT	0x030E
#define	PROP_CTRL_PINBOTTOM	0x030F
#define	PROP_CTRL_IDLEFT	0x0310
#define	PROP_CTRL_IDUP		0x0311
#define	PROP_CTRL_IDRIGHT	0x0312
#define	PROP_CTRL_IDDOWN	0x0313
#define	PROP_CTRL_IDENTER	0x0314
#define	PROP_IMAGE_ID		0x0400
#define	PROP_IMAGE_NAME		0x0401
#define	PROP_IMAGE_TYPE		0x0402
#define	PROP_IMAGE_WIDTH	0x0403
#define	PROP_IMAGE_HEIGHT	0x0404
#define	PROP_IMAGE_SIZE		0x0405
#define	PROP_IMAGE_MASKSIZE	0x0406
#define	PROP_IMAGE_ALPHA	0x0407
#define	PROP_IMAGE_FOPACITY	0x0408
#define	PROP_IMAGE_LOPACITY	0x0409
#endif

class CPropertiesBar : public CBCGPDockingControlBar
{
public:
	CPropertiesBar();
	virtual	~CPropertiesBar();

	void	InitPropList();

protected:
	CBCGPPropList	m_wndPropList;
	CFont			m_fntPropList;

	afx_msg	int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg	void	OnSize(UINT nType, int cx, int cy);
	afx_msg	void	OnPaint();
	afx_msg	LRESULT	OnPropertyChanged(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void	ResetPropList();
	void	SetPropListFont();
};
