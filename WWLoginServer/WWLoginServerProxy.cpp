#include "WWLoginServerProxy.h"
#include "WWLoginPKT_TYPE.h"
#include "Network/IOCPServer.h"
void WWLoginServerProxy::ReqLogin(SessionInfo sessionInfo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLogin << id << password;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::ReqLogin(const List<SessionInfo>& sessionInfoList, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ReqLogin << id << password;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::ResLogin(SessionInfo sessionInfo, char status, INT64 accountNo, const Array<char,64>& loginToken, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLogin << status << accountNo << loginToken << gameServerIp << gameServerPort;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::ResLogin(const List<SessionInfo>& sessionInfoList, char status, INT64 accountNo, const Array<char,64>& loginToken, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResLogin << status << accountNo << loginToken << gameServerIp << gameServerPort;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::SignUp(SessionInfo sessionInfo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_SignUp << id << password;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::SignUp(const List<SessionInfo>& sessionInfoList, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_SignUp << id << password;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::ResSignUp(SessionInfo sessionInfo, char status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResSignUp << status;
	}
	catch(int useSize)
	{
	}
	_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	pBuf->DecrementRefCnt();
}
void WWLoginServerProxy::ResSignUp(const List<SessionInfo>& sessionInfoList, char status, bool bDisconnect)
{
	CSendBuffer* pBuf = CSendBuffer::Alloc();
	pBuf->IncrementRefCnt();
	try
	{
		*pBuf << PKT_TYPE_ResSignUp << status;
	}
	catch(int useSize)
	{
	}
	for(SessionInfo sessionInfo: sessionInfoList)
	{
		_pServer->Unicast(sessionInfo, pBuf, bDisconnect);
	}
	pBuf->DecrementRefCnt();
}
