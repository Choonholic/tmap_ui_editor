// UIStruct.h

#pragma once

// Structure of UI Resource File:
// UI_HEADER
// UI_GROUP * dwGroups
// UI_PAGEC * dwPages
// UI_CTRLC * dwControls
// UI_IMAGEC * Images
// UI_PAGES * dwGroups * dwPages
// UI_CTRLS * dwGroups * dwControls
// (UI_IMAGES + ImageData) * dwGroups * dwImages

// Default Constants
#define	UI_MAX_NAMELEN		MAX_PATH	// Maximum Length of Name
#define	UI_MAX_NOTELEN		64			// Maximum Length of Note
#define	UI_MAX_TEXTLEN		32			// Maximum Length of Alternative Text

#define	UI_HEADER_ID		0x49554F53
#define	UI_VERSION			0x00020000
#define	UI_MAX_ID			0x00FFFFFF

// Error Codes
#ifndef	UI_ERRORCODES
#define	UI_ERRORCODES
#define	UI_INVALIDID		0x01000000	// Invalid ID for sentinel
#define	UI_NOMOREID			0x01000001	// No ID are available
#endif

// Item Types
#ifndef	UI_ITEMTYPES
#define	UI_ITEMTYPES
#define	UI_ITEM_NONE		0x0000		// None
#define	UI_ITEM_GROUP		0x0001		// Group
#define	UI_ITEM_PAGE		0x0002		// Page
#define	UI_ITEM_CTRL		0x0003		// Control
#define	UI_ITEM_IMAGE		0x0004		// Image
#endif

// Control Types
#ifndef	UI_CTRLTYPES
#define	UI_CTRLTYPES
#define	UI_CTRL_IMAGE		0x0001		// Image
#define	UI_CTRL_BUTTON		0x0002		// Button
#define	UI_CTRL_LISTBOX		0x0003		// List Box
#define	UI_CTRL_EDITBOX		0x0004		// Edit Box
#define	UI_CTRL_COMBOBOX	0x0005		// Combo Box
#define	UI_CTRL_REGION		0x0006		// Region
#endif

// Pin Types
#ifndef	UI_PINTYPES
#define	UI_PINTYPES
#define	UI_PIN_ALL			0x0000		// Absolute Coordinates
#define	UI_PIN_LEFT			0x0001		// Float Left Distance
#define	UI_PIN_TOP			0x0001		// Float Top Distance
#define	UI_PIN_RIGHT		0x0002		// Float Right Distance
#define	UI_PIN_BOTTOM		0x0002		// Float Bottom Distance
#endif

// Image Types
#ifndef	UI_IMAGETYPES
#define	UI_IMAGETYPES
#define	UI_IMAGE_BMP		0x0010		// BMP Mask
#define	UI_IMAGE_BMP32		0x0011		// 32 Bits BMP with Alpha Blending Mask
#define	UI_IMAGE_BMP24		0x0012		// 24 Bits BMP
#define	UI_IMAGE_BMP16		0x0013		// 16 Bits BMP
#define	UI_IMAGE_BMP08		0x0014		// 8 Bits BMP
#define	UI_IMAGE_PNG		0x0020		// PNG Mask
#define	UI_IMAGE_PNG32		0x0021		// 32 Bits PNG with Alpha Blending Mask
#define	UI_IMAGE_PNG24		0x0022		// 24 Bits PNG
#define	UI_IMAGE_JPG		0x0030		// JPG Mask
#define	UI_IMAGE_JPG24		0x0031		// 24 Bits JPG
#define	UI_IMAGE_GIF		0x0040		// GIF Mask
#define	UI_IMAGE_GIF08		0x0041		// 8 Bits GIF
#define	UI_IMAGE_TYPE		0x00F0		// Type Mask
#define	UI_IMAGE_UNKNOWN	0xFFFF		// Unknown
#endif

// Alpha Blending Gradient Types
#ifndef	UI_ABGTYPES
#define	UI_ABGTYPES
#define	UI_ABG_NONE			0x0000		// None
#define	UI_ABG_UPDOWN		0x0001		// Up-Down
#define	UI_ABG_LEFTRIGHT	0x0002		// Left-Right
#define	UI_ABG_VERTICAL		0x0001		// Vertical
#define	UI_ABG_HORIZONTAL	0x0002		// Horizontal
#endif

// UI Header
typedef struct tUIHeader
{
	DWORD	dwHeaderID;					// SOUI: SK OCBS UI
	DWORD	dwUIVersion;				// 0x00020000 (2.0)
	DWORD	dwSaveCount;				// Save Count
	DWORD	dwExportCount;				// Export Count
	DWORD	dwGroups;					// Number of Groups
	DWORD	dwPages;					// Number of Pages (per Group)
	DWORD	dwCtrls;					// Number of Controls (per Group)
	DWORD	dwImages;					// Number of Images (per Group)
	int		nCType;						// Selected Type
	DWORD	dwCGroupID;					// Current Group ID
	DWORD	dwCPageID;					// Current Page ID
	DWORD	dwCCtrlID;					// Current Control ID
	DWORD	dwCImageID;					// Current Image ID
	BYTE	cReserved[76];				// Reserved
} UI_HEADER, *PUI_HEADER, FAR *LPUI_HEADER;

// Group Information
typedef struct tUIGroup
{
	DWORD	dwGroupID;					// Group ID
	TCHAR	szName[UI_MAX_NAMELEN];		// Group Name
	TCHAR	szNote[UI_MAX_NOTELEN];		// Group Note
	USHORT	uWidth;						// Width of Group (by Pixel)
	USHORT	uHeight;					// Height of Group (by Pixel)
	BYTE	cReserved[32];				// Reserved
} UI_GROUP, *PUI_GROUP, FAR *LPUI_GROUP;

// Page Information: Common
typedef struct tUIPageC
{
	DWORD	dwPageID;					// Page ID
	TCHAR	szName[UI_MAX_NAMELEN];		// Page Name
	TCHAR	szNote[UI_MAX_NOTELEN];		// Page Note
} UI_PAGEC, *PUI_PAGEC, FAR *LPUI_PAGEC;

// Page Information: Specified
typedef struct tUIPageS
{
	DWORD	dwPageID;					// Page ID
	DWORD	dwGroupID;					// Group ID
	BOOL	bEnable;					// Enable Flag
	BYTE	cReserved[32];				// Reserved
} UI_PAGES, *PUI_PAGES, FAR *LPUI_PAGES;

// Control Information: Common
typedef struct tUICtrlC
{
	DWORD	dwCtrlID;					// Control ID
	DWORD	dwPageID;					// Parent Page ID
	TCHAR	szName[UI_MAX_NAMELEN];		// Control Name
	TCHAR	szNote[UI_MAX_NOTELEN];		// Control Note
	TCHAR	szText[UI_MAX_TEXTLEN];		// Control Alternative Text
} UI_CTRLC, *PUI_CTRLC, FAR *LPUI_CTRLC;

// Control Information: Specified
typedef struct tUICtrlS
{
	DWORD	dwCtrlID;					// Control ID
	DWORD	dwGroupID;					// Group ID
	BOOL	bEnable;					// Enable Flag
	int		nType;						// Type of Control
	BOOL	bCommon;					// Common Control Flag
	BOOL	bBackground;				// Background Control Flag
	RECT	rcWindow;					// Rectangle Area of Control (by Pixel)
	USHORT	uWidth;						// Width of Control (by Pixel)
	USHORT	uHeight;					// Height of Control (by Pixel)
	USHORT	uPinLeft;					// Pin Left Flag
	USHORT	uPinTop;					// Pin Top Flag
	USHORT	uPinRight;					// Pin Right Flag
	USHORT	uPinBottom;					// Pin Bottom Flag
	USHORT	uIDLeft;					// Remote Left Button ID
	USHORT	uIDUp;						// Remote Up Button ID
	USHORT	uIDRight;					// Remote Right Button ID
	USHORT	uIDDown;					// Remote Down Button ID
	USHORT	uIDEnter;					// Remote Enter Button ID
	BYTE	cReserved[28];				// Reserved
} UI_CTRLS, *PUI_CTRLS, FAR *LPUI_CTRLS;

// Image Information: Common
typedef struct tUIImageC
{
	DWORD	dwImageID;					// Image ID
	DWORD	dwCtrlID;					// Parent Control ID
	DWORD	dwPageID;					// Parent Page ID
	TCHAR	szName[UI_MAX_NAMELEN];		// Image Name (Not Filename)
} UI_IMAGEC, *PUI_IMAGEC, FAR *LPUI_IMAGEC;

// Image Information: Specified
typedef struct tUIImageS
{
	DWORD	dwImageID;					// Image ID
	DWORD	dwGroupID;					// Group ID
	int		nType;						// Image Type
	USHORT	uWidth;						// Width of Image
	USHORT	uHeight;					// Height of Image
	DWORD	dwSize;						// Image Buffer Size (Uncompressed)
	DWORD	dwMaskSize;					// Mask Buffer Size (Uncompressed) = uWidth * uHeight
	int		nAlphaType;					// Alpha Blending Type
	USHORT	uFirstOpacity;				// First Opacity of Alpha Blending Gradient
	USHORT	uLastOpacity;				// Last Opacity of Alpha Blending Gradient
	BYTE	cReserved[32];				// Reserved
} UI_IMAGES, *PUI_IMAGES, FAR *LPUI_IMAGES;
