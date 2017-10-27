#include "stdafx.h"
#include "CheckToolBar.h"
#include "TransQQMsgServerDlg.h"

CheckToolBar::CheckToolBar()
{
}


CheckToolBar::~CheckToolBar()
{
}


bool CheckToolBar::check()
{
	HWND hWnd = getHWND();
	if(hWnd==NULL)return false;
	return dealNotify(hWnd);
}


HWND CheckToolBar::getHWND()
{
	HWND hWnd = NULL;
	//ͨ��Spy++�鿴
	hWnd = ::FindWindow("Shell_TrayWnd", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "TrayNotifyWnd", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "SysPager", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "ToolbarWindow32", NULL);
	
	return hWnd;
}

//�ж�ʱ������Ϣ
bool CheckToolBar::dealNotify(HWND hWnd)
{
	DWORD pid = 0;
	::GetWindowThreadProcessId(hWnd, &pid);

	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pid);
	if (hProcess == NULL) {
		return false;
	}
	//�����ַ�ռ�,ʵ�����ڽ���explore.exe������
	LPVOID addr = VirtualAllocEx(hProcess, 0, sizeof(TBBUTTON), MEM_COMMIT, PAGE_READWRITE);
	if (addr == NULL) {
		::AfxMessageBox("�����ַ�ռ�ʧ�ܣ�\nErrorCode 02");
		return false;
	}

	//��ȡ������Ϣ
	int nDataOffset = sizeof(TBBUTTON) - sizeof(INT_PTR) - sizeof(DWORD_PTR) + 4;
	int nStrOffset = 24;
	CString filePath;
	CString title;
	DWORD contentAddr = NULL;
	::SendMessage(hWnd, TB_GETBUTTON, 0, (LPARAM)addr);
	::ReadProcessMemory(hProcess, (LPVOID)((DWORD)addr + nDataOffset), &contentAddr,4, NULL);
	if (contentAddr != -1) {
		BYTE buff[1024] = { 0 };
		::ReadProcessMemory(hProcess, (LPVOID)contentAddr, buff,1024, NULL);
		filePath = (WCHAR *)buff + nStrOffset;
		title = (WCHAR *)buff + nStrOffset + MAX_PATH;
		if (filePath.Right(6).MakeLower() == "qq.exe") {
			if (title.GetLength() == 0) {
				return true;
			}
		}
		else
		{
			::AfxMessageBox("û�з���QQ����\nErrorCode 404");
		}
		return false;

	}

	VirtualFreeEx(hProcess,addr, 4096, MEM_RELEASE);
	CloseHandle(hProcess);

	return false;
}

UINT CheckToolBar::RunThread(LPVOID lpParam) {
	return 0;
}
DWORD WINAPI CheckToolBar::ThreadWork(LPVOID lpParam) {

	Data *data = (Data *)lpParam;
	CheckToolBar *ctb=data->ctb;
	CString addr = data->addr;
	int port = data->port;
	AfxSocketInit();
	CSendMsg client;
	if (!client.Create()) {
		AfxMessageBox("Socket���ִ���\nErrorCode S01");
		return 0;
	}
	if (!client.Connect(addr, port)) {
		AfxMessageBox("Socket���ִ���\nErrorCode S02");
		return 0;
	}
	HWND hWnd =ctb->getHWND();
	if (hWnd == NULL) {
		::AfxMessageBox("δ֪����\nErrorCode 01");
		return 1;
	}
	while (true) {
		if (ctb->dealNotify(hWnd)) {
			//TODO sendMessage
			::AfxMessageBox("����Ϣ��");
			CString str = "�յ���Ϣ";
			client.Send(str, str.GetLength());
			Sleep(60000);
		}
		else
		{
			Sleep(2000);
		}

	}
	return 0;
}
