
// TTPDF.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

class TTPDFWorker;

// TTPDFApp:
// �� Ŭ������ ������ ���ؼ��� TTPDF.cpp�� �����Ͻʽÿ�.
//

class TTPDFApp : public CWinApp
{
public:
	TTPDFApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern TTPDFApp theApp;
extern TTPDFWorker thePDFWorker;