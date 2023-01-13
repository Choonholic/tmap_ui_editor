// OldStruct.h

#pragma once

// Structure of UI Resource File:
// OLD_UI_HEADER
// OLD_UI_GROUP * dwGroups
// OLD_UI_PAGEC * dwPages
// OLD_UI_CTRLC * dwControls
// OLD_UI_IMAGEC * Images
// OLD_UI_PAGES * dwGroups * dwPages
// OLD_UI_CTRLS * dwGroups * dwControls
// (OLD_UI_IMAGES + ImageData) * dwGroups * dwImages

// Default Constants
#define	OLD_UI_MAX_NAMELEN		MAX_PATH	// Maximum Length of Name
#define	OLD_UI_MAX_NOTELEN		64			// Maximum Length of Note
#define	OLD_UI_MAX_TEXTLEN		32			// Maximum Length of Alternative Text

#define	OLD_UI_HEADER_ID		0x49554F53
#define	OLD_UI_VERSION			0x00020000
#define	OLD_UI_MAX_ID			0x00FFFFFF

// Error Codes
#ifndef	OLD_UI_ERRORCODES
#define	OLD_UI_ERRORCODES
#define	OLD_UI_INVALIDID		0x01000000	// Invalid ID for sentinel
#define	OLD_UI_NOMOREID			0x01000001	// No ID are available
#endif

// Item Types
#ifndef	OLD_UI_ITEMTYPES
#define	OLD_UI_ITEMTYPES
#define	OLD_UI_ITEM_NONE		0x0000	// None
#define	OLD_UI_ITEM_GROUP		0x0001	// Group
#define	OLD_UI_ITEM_PAGE		0x0002	// Page
#define	OLD_UI_ITEM_CTRL		0x0003	// Control
#define	OLD_UI_ITEM_IMAGE		0x0004	// Image
#endif

// Control Types
#ifndef	OLD_UI_CTRLTYPES
#define	OLD_UI_CTRLTYPES
#define	OLD_UI_CTRL_IMAGE		0x0001	// Image
#define	OLD_UI_CTRL_BUTTON		0x0002	// Button
#define	OLD_UI_CTRL_LISTBOX		0x0003	// List Box
#define	OLD_UI_CTRL_EDITBOX		0x0004	// Edit Box
#define	OLD_UI_CTRL_COMBOBOX	0x0005	// Combo Box
#define	OLD_UI_CTRL_REGION		0x0006	// Region
#endif

// Pin Types
#ifndef	OLD_UI_PINTYPES
#define	OLD_UI_PINTYPES
#define	OLD_UI_PIN_ALL			0x0000	// Absolute Coordinates
#define	OLD_UI_PIN_LEFT			0x0001	// Float Left Distance
#define	OLD_UI_PIN_TOP			0x0001	// Float Top Distance
#define	OLD_UI_PIN_RIGHT		0x0002	// Float Right Distance
#define	OLD_UI_PIN_BOTTOM		0x0002	// Float Bottom Distance
#endif

// Image Types
#ifndef	OLD_UI_IMAGETYPES
#define	OLD_UI_IMAGETYPES
#define	OLD_UI_IMAGE_BMP		0x0010	// BMP Mask
#define	OLD_UI_IMAGE_BMP32		0x0011	// 32 Bits BMP with Alpha Blending Mask
#define	OLD_UI_IMAGE_BMP24		0x0012	// 24 Bits BMP
#define	OLD_UI_IMAGE_BMP16		0x0013	// 16 Bits BMP
#define	OLD_UI_IMAGE_BMP08		0x0014	// 8 Bits BMP
#define	OLD_UI_IMAGE_PNG		0x0020	// PNG Mask
#define	OLD_UI_IMAGE_PNG32		0x0021	// 32 Bits PNG with Alpha Blending Mask
#define	OLD_UI_IMAGE_PNG24		0x0022	// 24 Bits PNG
#define	OLD_UI_IMAGE_JPG		0x0030	// JPG Mask
#define	OLD_UI_IMAGE_JPG24		0x0031	// 24 Bits JPG
#define	OLD_UI_IMAGE_GIF		0x0040	// GIF Mask
#define	OLD_UI_IMAGE_GIF08		0x0041	// 8 Bits GIF
#define	OLD_UI_IMAGE_TYPE		0x00F0	// Type Mask
#define	OLD_UI_IMAGE_UNKNOWN	0xFFFF	// Unknown
#endif

// Alpha Blending Gradient Types
#ifndef	OLD_UI_ABGTYPES
#define	OLD_UI_ABGTYPES
#define	OLD_UI_ABG_NONE			0x0000	// None
#define	OLD_UI_ABG_UPDOWN		0x0001	// Up-Down
#define	OLD_UI_ABG_LEFTRIGHT	0x0002	// Left-Right
#define	OLD_UI_ABG_VERTICAL		0x0001	// Vertical
#define	OLD_UI_ABG_HORIZONTAL	0x0002	// Horizontal
#endif

// UI Header
typedef struct tOldUIHeader
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
} OLD_UI_HEADER, *POLD_UI_HEADER, FAR *LPOLD_UI_HEADER;

// Group Information
typedef struct tOldUIGroup
{
	DWORD	dwGroupID;					// Group ID
	TCHAR	szName[OLD_UI_MAX_NAMELEN];	// Group Name
	TCHAR	szNote[OLD_UI_MAX_NOTELEN];	// Group Note
	USHORT	uWidth;						// Width of Group (by Pixel)
	USHORT	uHeight;					// Height of Group (by Pixel)
} OLD_UI_GROUP, *POLD_UI_GROUP, FAR *LPOLD_UI_GROUP;

// Page Information: Common
typedef struct tOldUIPageC
{
	DWORD	dwPageID;					// Page ID
	TCHAR	szName[OLD_UI_MAX_NAMELEN];	// Page Name
	TCHAR	szNote[OLD_UI_MAX_NOTELEN];	// Page Note
} OLD_UI_PAGEC, *POLD_UI_PAGEC, FAR *LPOLD_UI_PAGEC;

// Page Information: Specified
typedef struct tOldUIPageS
{
	DWORD	dwPageID;					// Page ID
	DWORD	dwGroupID;					// Group ID
	BOOL	bEnable;					// Enable Flag
} OLD_UI_PAGES, *POLD_UI_PAGES, FAR *LPOLD_UI_PAGES;

// Control Information: Common
typedef struct tOldUICtrlC
{
	DWORD	dwCtrlID;					// Control ID
	DWORD	dwPageID;					// Parent Page ID
	TCHAR	szName[OLD_UI_MAX_NAMELEN];	// Control Name
	TCHAR	szNote[OLD_UI_MAX_NOTELEN];	// Control Note
	TCHAR	szText[OLD_UI_MAX_TEXTLEN];	// Control Alternative Text
} OLD_UI_CTRLC, *POLD_UI_CTRLC, FAR *LPOLD_UI_CTRLC;

// Control Information: Specified
typedef struct tOldUICtrlS
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
	USHORT	uIDRight;					// Remote Right Button ID
	USHORT	uIDLeft;					// Remote Left Button ID
	USHORT	uIDUp;						// Remote Up Button ID
	USHORT	uIDDown;					// Remote Down Button ID
} OLD_UI_CTRLS, *POLD_UI_CTRLS, FAR *LPOLD_UI_CTRLS;

// Image Information: Common
typedef struct tOldUIImageC
{
	DWORD	dwImageID;					// Image ID
	DWORD	dwCtrlID;					// Parent Control ID
	DWORD	dwPageID;					// Parent Page ID
	TCHAR	szName[OLD_UI_MAX_NAMELEN];	// Image Name (Not Filename)
} OLD_UI_IMAGEC, *POLD_UI_IMAGEC, FAR *LPOLD_UI_IMAGEC;

// Image Information: Specified
typedef struct tOldUIImageS
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
} OLD_UI_IMAGES, *POLD_UI_IMAGES, FAR *LPOLD_UI_IMAGES;
