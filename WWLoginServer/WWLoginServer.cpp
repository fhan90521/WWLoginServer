#include "WWLoginServer.h"
#include "Memory/MyNew.h"
#include "Memory/MakeShared.h"
#include "rapidjson/ParseJson.h"
#include "DebugTool/Log.h"

#include "WWDBReadQueue.h"
#include "WWDBWriteQueue.h"
#include <format>
const WString& WWLoginServer::GetGameServerIp()
{
	return _gameServerIp;
}
USHORT WWLoginServer::GetGameServerPort()
{
	return _gameServerPort;
}
void WWLoginServer::IncrementLoginReqCnt()
{
	InterlockedIncrement(&_procLoginReqCnt);
}
LONG WWLoginServer::GetProcLoginReqCnt()
{
	int ret = _procLoginReqCnt;
	InterlockedExchange(&_procLoginReqCnt, 0);
	return ret;
}
void WWLoginServer::CheckLastRecvTime(std::stop_token stoken)
{
	while (stoken.stop_requested()==false)
	{
		SHARED_LOCK;
		ULONG64 curTime = GetTickCount64();
		for (auto& sessionID : _sessions)
		{
			ULONG64 lastRecvTime = GetLastRecvTime(sessionID);
			if (curTime - lastRecvTime > RECV_TIME_OUT)
			{
				Disconnect(sessionID);
			}
		}
	}
}

bool WWLoginServer::OnAcceptRequest(const char* ip, USHORT port)
{
	return true;
}
void WWLoginServer::OnAccept(SessionInfo sessionInfo)
{
	InterlockedIncrement64(&_onConnectCnt);
	EXCLUSIVE_LOCK;
	_sessions.insert(sessionInfo.Id());
	return;
}
void WWLoginServer::OnDisconnect(SessionInfo sessionInfo)
{
	EXCLUSIVE_LOCK;
	_sessions.erase(sessionInfo.Id());
	return;
}
void WWLoginServer::OnRecv(SessionInfo sessionInfo,int roomID, CRecvBuffer& buf)
{
	if (PacketProc(sessionInfo,roomID, buf) == false)
	{
		Disconnect(sessionInfo);
	}
}

void WWLoginServer::Run()
{
	IOCPRun();
}

void WWLoginServer::ProcReqLogin(SessionInfo sessionInfo, int roomID, WString& id, WString& password)
{
	unsigned int index = (_dbReadQueuesIndex++) % _dbReadQueues.size();
}
void WWLoginServer::ProcSignUp(SessionInfo sessionInfo, int roomID, WString& id, WString& password)
{
}

void WWLoginServer::Monitor()
{
	int bufAllocCnt = CSendBuffer::GetAllocCnt();
	std::cout << std::format(R"(
-------------------------------------
SessionNum: {}
Accept Total: {}                                   
Accept Tps: {}
RecvMessageTps: {}
SendMessageTps: {}
)", GetConnectingSessionCnt(), _onConnectCnt, GetAcceptCnt(), GetRecvCnt(), GetSendCnt());
}

WWLoginServer::~WWLoginServer()
{
	_checkRecvTimeThread->request_stop();
	delete _checkRecvTimeThread;
	CloseServer();
	delete _dbWorkThreadPool;
}

WWLoginServer::WWLoginServer() : WWLoginServerProxy(this), IOCPServer("WWLoginServerSetting.json"),
_accountDB("WWLoginServerSetting.json"),
_loginTokenRedis("WWLoginServerSetting.json")
{
	Document serverSetValues = ParseJson("LoginServerSetting.json");
	std::string gameServerIp = serverSetValues["GameServerIp"].GetString();
	_gameServerIp.assign(gameServerIp.begin(), gameServerIp.end());
	
	_dbWorkThreadPool = new WorkThreadPool(_dbConcurrentWorkThreadCnt, _dbConcurrentWorkThreadCnt);
	for (int i = 0; i < _dbConcurrentWorkThreadCnt-1; i++)
	{
		_dbReadQueues.push_back(MakeShared<WWDBReadQueue>(this, _dbWorkThreadPool->GetCompletionPortHandle(), _accountDB, _loginTokenRedis));
	}
	_dbWriteQueue = MakeShared<WWDBWriteQueue>(this, _dbWorkThreadPool->GetCompletionPortHandle(), _accountDB);
	_gameServerPort = serverSetValues["GameServerPort"].GetInt();
	_checkRecvTimeThread = new std::jthread([this](std::stop_token stoken) {this->CheckLastRecvTime(stoken);});
}