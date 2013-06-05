#include <time.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    int listenfd = 0;
    if (!(listenfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        cout << "create socket error" << endl;
        return 0;
    }

    cout << "start up" << endl;

    struct sockaddr_in listenAddr = {0};
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenAddr.sin_port = htons(9800);
    bind(listenfd, (sockaddr*) &listenAddr, sizeof(sockaddr_in));

    listen(listenfd, 8);

    char buff[255] = {0};
    while(true)
    {
        struct sockaddr_in client = {0};
        socklen_t clientlen = sizeof(client);
        int confd = accept(listenfd, (sockaddr*)&client, &clientlen);
        if (confd != 0)
        {
            cout << "connect: " << inet_ntoa(client.sin_addr) << endl;
        }

        time_t ticks = time(0);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(confd, buff, strlen(buff));
        close(confd);
    }

    return 0;
}
