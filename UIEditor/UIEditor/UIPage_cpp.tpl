$[HANDLER_CPP]

$[HANDLER_INCLUDE]
#include "NaviContainer.h"
#include "NaviDocument.h"
#include "ResourceManager.h"
#include "NonMapDraw.h"

$[HANDLER_CONSTRUCTOR_IMP]
{
}

$[HANDLER_DESTRUCTOR_IMP]
{
}

$[HANDLER_INITDRAW_IMP]
{
}

$[HANDLER_ONACTIVATE_IMP]
{
	return true;
}

$[HANDLER_ONDEACTIVATE_IMP]
{
	return true;
}

$[HANDLER_ONINITHANDLER_IMP]
{
	m_pSurface	= psfContainer;

$[BUTTON_INITIALIZE]
}

$[HANDLER_ONERASEBKGND_IMP]
{
}

$[HANDLER_ONDRAW_IMP]
{
	CNaviDocument&		document		= CNaviDocument::GetInstance();
	CResourceManager&	resourceManager	= CResourceManager::GetInstance();

	resourceManager.ResetFlags();
	OnEraseBkgnd();

$[CONTROL_DRAW]

$[BUTTON_DRAW]
}

$[HANDLER_ONSIZE_IMP]
{
	return 1;
}

$[HANDLER_ONLBUTTONDOWN_IMP]
{
	CNaviDocument&		document		= CNaviDocument::GetInstance();
	CResourceManager&	resourceManager	= CResourceManager::GetInstance();
	UInt32				uRet			= 0;

$[BUTTON_LBUTTONDOWN]
	return CHANGEPAGE_UPDATE;
}

$[HANDLER_ONMOUSEMOVE_IMP]
{
$[BUTTON_MOUSEMOVE]
	return CHANGEPAGE_NONE;
}

$[HANDLER_ONLBUTTONUP_IMP]
{
	CNaviDocument&		document	= CNaviDocument::GetInstance();
	CResourceManager&	resource	= CResourceManager::GetInstance();

$[BUTTON_LBUTTONUP]
	return CHANGEPAGE_UPDATE;
}

$[HANDLER_ONKEYINPUT_IMP]
{
	CNaviDocument&	document	= CNaviDocument::GetInstance();

	switch (nKey)
	{
	case SDLK_ESCAPE:
		{
			// �⺻������ Esc Ű�� ���� �������� �����Ѵ�. �ʿ��� ��� ����.
			return CHANGEPAGE_POP1;
		}
	}

	return CHANGEPAGE_NONE;
}

$[HANDLER_ONNAVIUPDATE_IMP]
{
	// ���� ���� �ڵ鷯������ ���
	return CHANGEPAGE_NONE;
}

$[HANDLER_ONTIMERPROC_IMP]
{
	// ���� ���� �ڵ鷯������ ���
	return CHANGEPAGE_NONE;
}
