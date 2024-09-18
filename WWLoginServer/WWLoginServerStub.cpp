#include "WWLoginServerStub.h"
#include "DebugTool/Log.h"
bool WWLoginServerStub::PacketProcReqLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf)
{
	Array<WCHAR,20> id;
	Array<WCHAR,20> password;
	try
	{
		buf >> id >> password;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcReqLogin error\n");
		return false;
	}
	ProcReqLogin(sessionInfo, roomID, id, password);
	return true;
}

bool WWLoginServerStub::PacketProcResLogin(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf)
{
	char status;
	INT64 accountNo;
	std::string loginToken;
	Array<WCHAR,16> gameServerIp;
	USHORT gameServerPort;
	try
	{
		buf >> status >> accountNo >> loginToken >> gameServerIp >> gameServerPort;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcResLogin error\n");
		return false;
	}
	ProcResLogin(sessionInfo, roomID, status, accountNo, loginToken, gameServerIp, gameServerPort);
	return true;
}

bool WWLoginServerStub::PacketProcSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf)
{
	Array<WCHAR,20> id;
	Array<WCHAR,20> password;
	try
	{
		buf >> id >> password;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcSignUp error\n");
		return false;
	}
	ProcSignUp(sessionInfo, roomID, id, password);
	return true;
}

bool WWLoginServerStub::PacketProcResSignUp(SessionInfo sessionInfo, int roomID, CRecvBuffer& buf)
{
	char status;
	try
	{
		buf >> status;
	}
	catch(int useSize)
	{
		Log::LogOnFile(Log::DEBUG_LEVEL, "PacketProcResSignUp error\n");
		return false;
	}
	ProcResSignUp(sessionInfo, roomID, status);
	return true;
}

bool WWLoginServerStub::PacketProc(SessionInfo sessionInfo,int roomID, CRecvBuffer& buf)
{
	short packetType;
	try
	{
		buf >> packetType;
	}
	catch(int remainSize)
	{
		return false;
	}
	switch(packetType)
	{
	case PKT_TYPE_ReqLogin:
	{
		return PacketProcReqLogin(sessionInfo,roomID, buf);
		break;
	}
	case PKT_TYPE_ResLogin:
	{
		return PacketProcResLogin(sessionInfo,roomID, buf);
		break;
	}
	case PKT_TYPE_SignUp:
	{
		return PacketProcSignUp(sessionInfo,roomID, buf);
		break;
	}
	case PKT_TYPE_ResSignUp:
	{
		return PacketProcResSignUp(sessionInfo,roomID, buf);
		break;
	}
	default:
	{
		return false;
	}
	}
}
