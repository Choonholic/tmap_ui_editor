$[HANDLER_HEADER]

$[HANDLER_IFNDEF]
$[HANDLER_DEFINE]

#include "Handler.h"
#include "UIButton.h"

$[HANDLER_CLASS]
{
public:
$[HANDLER_CONSTRUCTOR]
$[HANDLER_DESTRUCTOR]

protected:
	virtual	void	InitDraw();
	virtual	Bool	OnActivate();
	virtual	Bool	OnDeactivate();
	virtual	void	OnInitHandler(SDL_Surface* psfContainer, void* pParam1, void* pParam2);
	virtual	void	OnEraseBkgnd();
	virtual	void	OnDraw();
	virtual	Int32	OnSize(Int32 cx, Int32 cy);
	virtual	UInt32	OnLButtonDown(Int32 x, Int32 y, UInt32 uFlag);
	virtual	UInt32	OnMouseMove(Int32 x, Int32 y, UInt32 uFlag);
	virtual	UInt32	OnLButtonUp(Int32 x, Int32 y, UInt32 uFlag);
	virtual	UInt32	OnKeyInput(Int32 nKey, UInt32 uKeyModify);
	virtual	UInt32	OnNaviUpdate(UInt32 msg, Long lParam1, Long lParam2, Long lParam3);
	virtual	UInt32	OnTimerProc();
	virtual	UInt32	OnReceiveMsg(UInt32 msg, void *pData) {return CHANGEPAGE_NONE;};

$[BUTTON_LIST]
};

$[HANDLER_ENDIF]
