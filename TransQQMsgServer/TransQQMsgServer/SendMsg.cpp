// SendMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransQQMsgServer.h"
#include "SendMsg.h"


// CSendMsg

CSendMsg::CSendMsg()
{
}

CSendMsg::~CSendMsg()
{
}


// CSendMsg ��Ա����


void CSendMsg::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnConnect(nErrorCode);
}


void CSendMsg::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnSend(nErrorCode);
}
