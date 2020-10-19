// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(_STDAFX_H_)
#define _STDAFX_H_
#pragma warning(disable:4996)
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>

//#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <afxdtctl.h>
#include "polydb.h"
#include "TOOLSCATEGORY.H"
#include "polytools.h"
#include "AfxDao.h"		// For DAO work
#include "eventimp.h"
#include "Category.h"
#include "CommonCategory.h"
#include "firstdatabaseprivilegetool.h"
#include "Connection.h"
#include "WaitWnd.h"
#include <afxctl.h >
#include <afxext.h>         // MFC extensions
//#include "..\\ADMN.EXE\\resource.h"

#import "FDesktop.dll" no_namespace 
#import "RepModule.dll" no_namespace
#import <RegistryHandle.dll> no_namespace
#import "VBALib.dll" no_namespace
#import "CPMSTools.dll" no_namespace

#define	APP_CODE		99
#define	STR_APP_CODE	"99"

#endif // !defined(AFX_STDAFX_H__51FA7D18_82F3_11D2_A9BC_444553540000__INCLUDED)
