#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <iostream>

#define PORT 8080

int main()
{
    struct sockaddr_in addr;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
        std::cout << "Client: socket error\n";
        return -1;
    }

	std::memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl((127 << 24) + (0 << 16) + (0 << 8) + 1);
 
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cout << "Client: connect error\n";
        return -1;
    }

	std::string	msg = "This is a client message\r\n\r\n";
//	std::string	msg = "GET /avarnier HTTP/1.1\r\n\r\n";
    send(sock, msg.c_str(), msg.size(), 0);
	char buff[10240];
	recv(sock, buff, 10240, 0);
	std::cerr << "receive by client = " << buff << '\n';
    return (0);
}
