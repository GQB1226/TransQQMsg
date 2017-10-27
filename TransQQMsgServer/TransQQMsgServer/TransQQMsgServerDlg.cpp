
// TransQQMsgServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TransQQMsgServer.h"
#include "TransQQMsgServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTransQQMsgServerDlg 对话框

BEGIN_DHTML_EVENT_MAP(CTransQQMsgServerDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CTransQQMsgServerDlg::CTransQQMsgServerDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_TRANSQQMSGSERVER_DIALOG, IDR_HTML_TRANSQQMSGSERVER_DIALOG, pParent)
	, pThread(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  port = 0;
}

void CTransQQMsgServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, port);
	//  DDX_Text(pDX, IDC_EDIT1, port);
	//  DDX_Control(pDX, IDC_EDIT1, inputPOrt);
	DDX_Control(pDX, IDC_PORT, inputPort);
	DDX_Control(pDX, IDC_IPADDR, m_addr);
}

BEGIN_MESSAGE_MAP(CTransQQMsgServerDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_STARTSER, &CTransQQMsgServerDlg::OnClickedStartServer)
END_MESSAGE_MAP()


// CTransQQMsgServerDlg 消息处理程序

BOOL CTransQQMsgServerDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT)->SetWindowTextA("12260");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTransQQMsgServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTransQQMsgServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTransQQMsgServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CTransQQMsgServerDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CTransQQMsgServerDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

//启动服务
void CTransQQMsgServerDlg::OnClickedStartServer()
{
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_STARTSER)->EnableWindow(false);
	UpdateData(false);
	CString addr;
	GetDlgItemText(IDC_IPADDR,addr);
	if (addr == "") {
		AfxMessageBox("分发地址没有填写！\nErrorCode 01");
		return;
	}
	data.addr = addr;
	int port = GetDlgItemInt(IDC_PORT, NULL, 1);
	data.port = port;
	

	DWORD d1;
	::CreateThread(NULL, 0, CheckToolBar::ThreadWork, &data, 0, &d1);
}
