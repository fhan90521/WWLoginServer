#pragma once
#include "Network/Session.h"
#include "Container/MyStlContainer.h"
class WWLoginServerProxy
{
private:
	class IOCPServer* _pServer;
public:
	void ReqLogin(SessionInfo sessionInfo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect = false);
	void ReqLogin(const List<SessionInfo>& sessionInfoList, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect = false);

	void ResLogin(SessionInfo sessionInfo, char status, INT64 accountNo, const std::string& loginToken, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, bool bDisconnect = false);
	void ResLogin(const List<SessionInfo>& sessionInfoList, char status, INT64 accountNo, const std::string& loginToken, const Array<WCHAR,16>& gameServerIp, USHORT gameServerPort, bool bDisconnect = false);

	void SignUp(SessionInfo sessionInfo, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect = false);
	void SignUp(const List<SessionInfo>& sessionInfoList, const Array<WCHAR,20>& id, const Array<WCHAR,20>& password, bool bDisconnect = false);

	void ResSignUp(SessionInfo sessionInfo, char status, bool bDisconnect = false);
	void ResSignUp(const List<SessionInfo>& sessionInfoList, char status, bool bDisconnect = false);

	WWLoginServerProxy(class IOCPServer* pServer)
	{
		_pServer = pServer;
	}
};
