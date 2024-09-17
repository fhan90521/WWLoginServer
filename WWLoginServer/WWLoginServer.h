#pragma once
#include "Network/IOCPServer.h"
#include "Container/MyStlContainer.h"
#include "Profiler/PerformanceMonitor.h"
#include "Job/WorkThreadPool.h"
#include "DBHelper/MYSQLHelper.h"
#include "DBHelper/RedisHelper.h"
#include <atomic>
#include <thread>
#include <random>
#include "WWLoginServerStub.h"
#include "WWLoginServerProxy.h"
class WWLoginServer: public IOCPServer, public  WWLoginServerProxy, private WWLoginServerStub
{
private:
	MYSQLHelper _accountDB;
	RedisHelper _loginTokenRedis;
	Array<WCHAR, 16> _gameServerIp;
	USHORT _gameServerPort;
	LONG64 _onConnectCnt = 0;
	LONG _procLoginReqCnt = 0;
	std::random_device _rd;
	std::mt19937 _rnGenerator;
	std::uniform_int_distribution<uint64_t> _dis;

	LONG GetProcLoginReqCnt();
public:
	const Array<WCHAR, 16>& GetGameServerIp();
	USHORT GetGameServerPort();
	void IncrementLoginReqCnt();
private:
	enum
	{
		RECV_TIME_OUT = 30000
	};
	std::jthread* _checkRecvTimeThread;
	HashSet<SessionInfo::ID> _sessions;
	USE_LOCK;
	void CheckLastRecvTime(std::stop_token stoken);

	WorkThreadPool* _dbWorkThreadPool;
	int _dbConcurrentWorkThreadCnt = 2;
	Vector<SharedPtr<class WWDBReadQueue>> _dbReadQueues;
	unsigned int _dbReadQueuesIndex = 0;
	SharedPtr<class WWDBWriteQueue> _dbWriteQueue;
	virtual bool OnAcceptRequest(const char* ip, USHORT port) override;
	virtual void OnAccept(SessionInfo sessionInfo) override;
	virtual void OnDisconnect(SessionInfo sessionInfo) override;
	virtual void OnRecv(SessionInfo sessionInfo,int roomID ,CRecvBuffer& buf) override;
private:
	virtual void ProcReqLogin(SessionInfo sessionInfo, int roomID, Array<WCHAR, 20>& id, Array<WCHAR, 20>& password) override;
	virtual void ProcSignUp(SessionInfo sessionInfo, int roomID, Array<WCHAR, 20>& id, Array<WCHAR, 20>& password) override;
public:
	Array<char, 64> MakeLoginToken();
	virtual void Run() override;
	void Monitor();
	WWLoginServer();
	~WWLoginServer();

};