// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9FF1ADB4_0CE8_4F55_8E2D_9BA4F823B332__INCLUDED_)
#define AFX_STDAFX_H__9FF1ADB4_0CE8_4F55_8E2D_9BA4F823B332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WINVER 0x500

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//disable warning 4786 & 4355
#pragma warning( disable : 4786)
#pragma warning( disable : 4355)

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//include STL header files
#include <string>
#include <map>
#include <vector>
#include <list>
#include <cassert>
#include <cmath>
#include <algorithm>


//include user header files
#include "..\speedsim\SpeedKernel\SpeedKernel.h"
#include "xgame_common.hpp"
#include "ecfile.hpp"
#include "game_algo.hpp"

//check is using Skin++ lib
#ifdef USING_SKINPLUSPLUS  
  #include "SkinPlusPlus.h"
  #pragma comment(lib, "..\\lib\\SkinPlusPlusDLL.lib")
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9FF1ADB4_0CE8_4F55_8E2D_9BA4F823B332__INCLUDED_)
