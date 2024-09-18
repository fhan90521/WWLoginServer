#include "WWDBWriteQueue.h"
#include "libsodium/include/sodium.h"
#include "Encrypt/Encrptor.h"
void WWDBWriteQueue::SignUp(SessionInfo sessionInfo, WString& id, WString& password)
{
	
	//DB¾²±â

}

WWDBWriteQueue::WWDBWriteQueue(WWLoginServer* loginServer, HANDLE hCompletionPort, MYSQLHelper& accountDB):
	_wwLoginServer(loginServer),
	JobQueue(hCompletionPort),
	_accountDB(accountDB)
{
}
