// SendMsg.cpp : 实现文件
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


// CSendMsg 成员函数


void CSendMsg::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnConnect(nErrorCode);
}


void CSendMsg::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnSend(nErrorCode);
}
