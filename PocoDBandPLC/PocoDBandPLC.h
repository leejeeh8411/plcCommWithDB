
// PocoDBandPLC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPocoDBandPLCApp:
// �� Ŭ������ ������ ���ؼ��� PocoDBandPLC.cpp�� �����Ͻʽÿ�.
//

class CPocoDBandPLCApp : public CWinApp
{
public:
	CPocoDBandPLCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPocoDBandPLCApp theApp;