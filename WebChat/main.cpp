#include <time.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <errno.h>
#include "Encrypt/sha1.h"
#include "Encrypt/base64.h" 

//监听端口号
static const int s_listen_port = 9800;

using namespace std;


void setTime(char *outStr);
void setExchangeHead(char *outStr, const string &clientHead);
void getValueFromPairs(const char *str);
char* Base64Code(const char* Message, int len);
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);

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
    listenAddr.sin_port = htons(s_listen_port);
    bind(listenfd, (sockaddr*) &listenAddr, sizeof(sockaddr_in));

    listen(listenfd, 8);

    while(true)
    {
        struct sockaddr_in client = {0};
        socklen_t clientlen = sizeof(client);
        int confd = accept(listenfd, (sockaddr*)&client, &clientlen);
        if (confd != 0)
        {
            cout << "connect: " << inet_ntoa(client.sin_addr) << endl;
        }
		else if (confd == -1)
		{
			cout << "accept failed"	<< endl;
		}
	
		int conPID = 0;
		if ((conPID = fork() > 0))
		{
			close(confd);
		}
		//子进程
		else
		{				
			int msgLen = 0;
			char buff[512];
			bzero(buff, sizeof(buff));
			
			while ((msgLen = read(confd, buff, 512)))
			{
				cout << "msg size: " << msgLen << endl;
				if (msgLen == -1)
				{
					cout << "read error: " << errno << endl;
					break;	
				}
				
				puts("-------------csmsg---------------");
				puts(buff);
				puts("------------ csmsg end-------------");

				char sendBuff[512] = {0};
				setExchangeHead(sendBuff,buff);

				puts("---------scmsg----------------");
				//setTime(sendBuff);
				puts(sendBuff);
				puts("---------scmsg end----------------");
				write(confd, sendBuff, strlen(sendBuff));
				cout << "write size: " << strlen(sendBuff) << endl;
			}

			close(confd);
			return 0;
		}
	}

    return 0;
}

void setExchangeHead(char *outStr, const string &clientHead)
{
	strcat(outStr, "HTTP/1.1 101 Switching Protocols\r\n");
	strcat(outStr, "Upgrade: websocket\r\n");
	strcat(outStr, "Connection: Upgrade\r\n");
	
	const string _keyID = "Sec-WebSocket-Key: ";
	int keyPos = clientHead.find(_keyID);

	//clientKey
	string clientKey = clientHead.substr(keyPos+_keyID.size(), 24);
	cout << "clientKye: " << clientKey << endl;

	clientKey += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

	SHA1 sha;
	sha.Reset();
	sha.Input((const unsigned char *)clientKey.c_str(), clientKey.size());

	unsigned int message_digest[5];
	if (!sha.Result(message_digest))
	{
		cout << "sha1 error" << endl;
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		message_digest[i] = htonl(message_digest[i]);
	}

	string base64Str = base64_encode((const unsigned char *)message_digest, 20);
	cout << "after base64:" << endl;
	cout << base64Str << endl;
	
	strcat(outStr, "Sec-WebSocket-Accept: ");
	strcat(outStr, base64Str.c_str());
	strcat(outStr, "\r\n");
	strcat(outStr, "\r\n");
}

void setTime(char *outStr)
{
		char buff[32] = {0};
        time_t ticks = time(0);

        snprintf(buff, sizeof(buff), "%.24s\n", ctime(&ticks));
		strncat(outStr, buff, 32);
}

