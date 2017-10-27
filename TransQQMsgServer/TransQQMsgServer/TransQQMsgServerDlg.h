
// TransQQMsgServerDlg.h : ͷ�ļ�
//

#pragma once
#include "CheckToolBar.h"
#include "SendMsg.h"
#include "afxwin.h"

// CTransQQMsgServerDlg �Ի���
class CTransQQMsgServerDlg : public CDHtmlDialog
{
// ����
public:
	CTransQQMsgServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSQQMSGSERVER_DIALOG, IDH = IDR_HTML_TRANSQQMSGSERVER_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
