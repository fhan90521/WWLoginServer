#pragma once
#include "Job/JobQueue.h"
#include "Network/Session.h"
class WWDBWriteQueue : public JobQueue
{
public:
	class WWLoginServer* _wwLoginServer = nullptr;
	class MYSQLHelper& _accountDB;
	void SignUp(SessionInfo sessionInfo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& password);
	WWDBWriteQueue(class WWLoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB);
};