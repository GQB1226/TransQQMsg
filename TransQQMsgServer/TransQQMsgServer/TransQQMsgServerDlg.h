
// TransQQMsgServerDlg.h : 头文件
//

#pragma once
#include "CheckToolBar.h"
#include "SendMsg.h"
#include "afxwin.h"

// CTransQQMsgServerDlg 对话框
class CTransQQMsgServerDlg : public CDHtmlDialog
{
// 构造
public:
	CTransQQMsgServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSQQMSGSERVER_DIALOG, IDH = IDR_HTML_TRANSQQMSGSERVER_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	afx_msg void OnClickedStartServer();
//	CString port;
	afx_msg void OnBnClickedStartser();
	CEdit inputPort;
	struct Data {
		CheckToolBar* ctb;
		//CSendMsg* client;
		CString addr;
		int port;
	}data;
protected:
	CWinThread* pThread;
public:
	CEdit m_addr;
};
