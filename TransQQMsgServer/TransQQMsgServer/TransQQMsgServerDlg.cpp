
// TransQQMsgServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransQQMsgServer.h"
#include "TransQQMsgServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTransQQMsgServerDlg �Ի���

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


// CTransQQMsgServerDlg ��Ϣ�������

BOOL CTransQQMsgServerDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_PORT)->SetWindowTextA("12260");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTransQQMsgServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

//��������
void CTransQQMsgServerDlg::OnClickedStartServer()
{
	GetDlgItem(IDC_PORT)->EnableWindow(false);
	GetDlgItem(IDC_STARTSER)->EnableWindow(false);
	UpdateData(false);
	CString addr;
	GetDlgItemText(IDC_IPADDR,addr);
	if (addr == "") {
		AfxMessageBox("�ַ���ַû����д��\nErrorCode 01");
		return;
	}
	data.addr = addr;
	int port = GetDlgItemInt(IDC_PORT, NULL, 1);
	data.port = port;
	

	DWORD d1;
	::CreateThread(NULL, 0, CheckToolBar::ThreadWork, &data, 0, &d1);
}
