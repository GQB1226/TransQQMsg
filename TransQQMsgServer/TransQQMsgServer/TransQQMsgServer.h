
// TransQQMsgServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTransQQMsgServerApp: 
// �йش����ʵ�֣������ TransQQMsgServer.cpp
//

class CTransQQMsgServerApp : public CWinApp
{
public:
	CTransQQMsgServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTransQQMsgServerApp theApp;