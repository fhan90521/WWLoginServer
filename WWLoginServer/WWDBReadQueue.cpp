#include "WWDBReadQueue.h"
#include "WWLoginServer.h"
#include "DebugTool/Log.h"
#include "DBHelper/MYSQLHelper.h"
#include "DBHelper/RedisHelper.h"
#include "WWLoginEnum.h"
void WWDBReadQueue::ProcReqLogin(SessionInfo sessionInfo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& password)
{
	//DB 읽기

	//Token 저장
	ULONG64 accountNo;
	auto loginToken = _wwLoginServer->MakeLoginToken();
	_loginTokenRedis.GetRedisConnection()->setex(std::to_string(accountNo), 30, loginToken, [this, sessionInfo, accountNo, loginToken](cpp_redis::reply& reply) mutable
	{
			if (reply.is_simple_string() == true)
			{
				_wwLoginServer->ResLogin(sessionInfo, LOGIN_SUCESS ,accountNo, loginToken, _wwLoginServer->GetGameServerIp(), _wwLoginServer->GetGameServerPort(), true);
				_wwLoginServer->IncrementLoginReqCnt();
			}
			else
			{
				Log::LogOnFile(Log::SYSTEM_LEVEL, "redis set fail\n");
			}
		}
	);
	_loginTokenRedis.GetRedisConnection()->commit();
}

WWDBReadQueue::WWDBReadQueue(WWLoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB, RedisHelper& loginTokenRedis):
	_wwLoginServer(loginServer),
	JobQueue(hCompletionPort) ,
	_accountDB(accountDB),
	_loginTokenRedis(loginTokenRedis)
{

}
