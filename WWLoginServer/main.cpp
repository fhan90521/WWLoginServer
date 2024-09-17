#include <iostream>
#include "WWLoginServer.h"
int main()
{
    WWLoginServer loginServer;
    loginServer.Run();
    while (loginServer._bShutdown == false)
    {
        loginServer.ServerControl();
        loginServer.Monitor();
        Sleep(1000);
    }
}
