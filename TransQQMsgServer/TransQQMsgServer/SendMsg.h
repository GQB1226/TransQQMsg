#pragma once

// CSendMsg ����Ŀ��

class CSendMsg : public CSocket
{
public:
	CSendMsg();
	virtual ~CSendMsg();
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};


