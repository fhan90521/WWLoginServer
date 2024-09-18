#pragma once
#include "Job/JobQueue.h"
#include "Network/Session.h"
class WWDBReadQueue : public JobQueue
{
public:
	class WWLoginServer* _wwLoginServer=nullptr;
	class MYSQLHelper& _accountDB;
	class RedisHelper& _loginTokenRedis;
	void ProcReqLogin(SessionInfo sessionInfo, WString& id, WString& password);
	WWDBReadQueue(class WWLoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB, RedisHelper& loginTokenRedis);
};