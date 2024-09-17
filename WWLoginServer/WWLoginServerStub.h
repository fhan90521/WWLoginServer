#pragma once
#include "Network/Session.h"
#include "Buffer/CRecvBuffer.h"
#include "Container/MyStlContainer.h"
#include "WWLoginPKT_TYPE.h"
class WWLoginServerStub
{
public:
	bool PacketProcReqLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcReqLogin(SessionInfo sessionInfo, int roomID, Array<WCHAR,20>& id, Array<WCHAR,20>& password) {}

	bool PacketProcResLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcResLogin(SessionInfo sessionInfo, int roomID, char status, INT64 accountNo, Array<char,64>& loginToken, Array<WCHAR,16>& gameServerIp, USHORT gameServerPort) {}

	bool PacketProcSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcSignUp(SessionInfo sessionInfo, int roomID, Array<WCHAR,20>& id, Array<WCHAR,20>& password) {}

	bool PacketProcResSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcResSignUp(SessionInfo sessionInfo, int roomID, char status) {}

	bool PacketProc(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
};
