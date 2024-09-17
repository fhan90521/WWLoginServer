#include "WWDBWriteQueue.h"

void WWDBWriteQueue::SignUp(SessionInfo sessionInfo, Array<WCHAR, 20>& id, Array<WCHAR, 20>& password)
{
	//DB¾²±â
}

WWDBWriteQueue::WWDBWriteQueue(WWLoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB):
	_wwLoginServer(loginServer),
	JobQueue(hCompletionPort),
	_accountDB(accountDB)
{
}
