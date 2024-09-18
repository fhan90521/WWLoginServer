#pragma once
#include "Network/Session.h"
#include "Buffer/CRecvBuffer.h"
#include "Container/MyStlContainer.h"
#include "WWLoginPKT_TYPE.h"
class WWLoginServerStub
{
public:
	bool PacketProcReqLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcReqLogin(SessionInfo sessionInfo, int roomID, WString& id, WString& password) {}

	bool PacketProcResLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcResLogin(SessionInfo sessionInfo, int roomID, char status, INT64 accountNo, std::string& loginToken, WString& gameServerIp, USHORT gameServerPort) {}

	bool PacketProcSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcSignUp(SessionInfo sessionInfo, int roomID, WString& id, WString& password) {}

	bool PacketProcResSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
	virtual void ProcResSignUp(SessionInfo sessionInfo, int roomID, char status) {}

	bool PacketProc(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf);
};
