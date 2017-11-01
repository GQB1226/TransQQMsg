#pragma once
#include "SendMsg.h"
class CheckToolBar
{
public:
	CheckToolBar();
	~CheckToolBar();
	bool check();
	HWND getHWND();
	bool dealNotify(HWND hWnd);
	//void run(int port);
	static UINT RunThread(LPVOID lpParam);
	static  DWORD WINAPI ThreadWork(LPVOID lpParam);
	struct Data {
		CheckToolBar* ctb;
		CString addr;
		int port;
	};
	bool checkMSTask();
};

