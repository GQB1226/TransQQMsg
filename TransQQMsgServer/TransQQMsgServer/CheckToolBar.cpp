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
	//通过Spy++查看
	hWnd = ::FindWindow("Shell_TrayWnd", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "TrayNotifyWnd", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "SysPager", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "ToolbarWindow32", NULL);
	
	return hWnd;
}

//判断时候有消息
bool CheckToolBar::dealNotify(HWND hWnd)
{
	DWORD pid = 0;
	::GetWindowThreadProcessId(hWnd, &pid);

	HANDLE hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pid);
	if (hProcess == NULL) {
		return false;
	}
	//申请地址空间,实际是在进程explore.exe中申请
	LPVOID addr = VirtualAllocEx(hProcess, 0, sizeof(TBBUTTON), MEM_COMMIT, PAGE_READWRITE);
	if (addr == NULL) {
		::AfxMessageBox("申请地址空间失败！\nErrorCode 02");
		return false;
	}

	//获取具体信息
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
			::AfxMessageBox("没有发现QQ程序！\nErrorCode 404");
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
		AfxMessageBox("Socket出现错误！\nErrorCode S01");
		return 0;
	}
	if (!client.Connect(addr, port)) {
		AfxMessageBox("Socket出现错误！\nErrorCode S02");
		return 0;
	}
	HWND hWnd =ctb->getHWND();
	if (hWnd == NULL) {
		::AfxMessageBox("未知错误！\nErrorCode 01");
		return 1;
	}
	while (true) {
		//TODO 还需要检测MSTaskListWClass里面的图标是否变亮
		if (ctb->dealNotify(hWnd) || ctb->checkMSTask()) {
			//TODO sendMessage
			//::AfxMessageBox("有消息！");
			CString str = "收到消息";
			client.Send(str, str.GetLength());
			Sleep(60000);
		}
		else
		{
			Sleep(5000);
			//发送心跳包
			srand((unsigned)time(NULL)); 
			int num = rand() % 122600;
			CString hbp = "hb:dfadsfasdfa";
			client.Send(hbp,hbp.GetLength());
			char *rec =NULL;
			rec = new char[1024];
			if (client.Receive(rec, sizeof(char) * 1024) != SOCKET_ERROR) {
				CString pData = rec;
				if (rec == pData) {
					continue;
				}
			}
			else {
				if (!client.Connect(addr, port)) {
					AfxMessageBox("Socket出现错误！\nErrorCode S02");
					return 0;
				}
			}

		}

	}
	return 0;
}


bool CheckToolBar::checkMSTask()
{
	CDC *pDC;//窗口DC
	CRect rect;

	//获取当前设备
	//任务窗口每次可能都有更新，所以需要刷新
	HWND hWnd = FindWindow("Shell_TrayWnd", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "ReBarWindow32", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "MSTaskSwWClass", NULL);
	hWnd = ::FindWindowEx(hWnd, NULL, "MSTaskListWClass", NULL);

	HDC hDC = ::GetDC(hWnd);
	::GetWindowRect(hWnd,&rect);

	pDC = CDC::FromHandle(hDC);  //获取当前窗口DC
	int BitPerPixel = pDC->GetDeviceCaps(BITSPIXEL);//获得颜色模式
	for (int i = 0; i < rect.Width(); i += 48.75) {
		COLORREF color = ::GetPixel(hDC, i, 7);
		BYTE r = GetRValue(color);
		BYTE g = GetGValue(color);
		BYTE b = GetBValue(color);
		//此处颜色可能有色差，注意和本机情况结合
		if ((r <= 154 && r >= 152) && (g <= 90 && g >= 80) && (b <= 35 && b >= 20)) {
			return true;
		}
	}
	return false;
}