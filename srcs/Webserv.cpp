/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:41:02 by hlevi             #+#    #+#             */
/*   Updated: 2023/03/07 19:06:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Webserv.hpp"




#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../incs/Request.hpp"
#include <fcntl.h>
const int PORT = 8080;

namespace ft {

////////////////////////////////////////////////////////////////////////////////
//                                constructor                                 //
////////////////////////////////////////////////////////////////////////////////

Webserv::Webserv(std::string filename)
{
	this->parser.parsing(filename, this->servers);

	server_start();
	// for (std::vector<Server>::const_iterator it = this->servers.begin();
	// it != this->servers.end(); it++)
	// {
	// 	this->manager.addServer(it->addr);
	// }

}

Webserv::~Webserv()
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  methods                                   //
////////////////////////////////////////////////////////////////////////////////

void	Webserv::run()
{
	for (;;)
	{
		int n = epoll_wait(this->manager.epfd, this->manager.epev, MAXEVENTS, -1);
		if (n == -1)
			throw std::runtime_error("Runtime error: epoll_wait failed");
		for (int i = 0; i < n; i++)
		{
			int fd = this->manager.epev[i].data.fd;
			uint32_t event = this->manager.epev[i].events;
			if ((event & EPOLLERR) || (event & EPOLLHUP) || (!(event & EPOLLIN)))
				this->manager.close(fd);
			
			if (this->manager.isServer(fd) == true)
			{
				Socket		sock;
				socklen_t	len;
				sock.fd = accept(fd,
				reinterpret_cast<sockaddr *>(&sock.addr), &len);
				if (sock.fd != -1)
					this->manager.addClient(fd, sock);
			}
			else
			{
				char buff[MAXBUFF + 1];
				ssize_t bytes = recv(fd, buff, MAXBUFF, 0);
				if (bytes > 0)
				{
					buff[bytes] = '\0';
					this->manager.getData(fd, buff);
				}
				else
				{
					this->manager.close(fd);
					std::cout << "close connection" << '\n';
				}
			}
		}
	}
}


int Webserv::server_start()
{

//   int server_socket = socket(AF_INET, SOCK_STREAM, 0);

//     sockaddr_in server_address;
//     std::memset(&server_address, 0, sizeof(server_address));
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(PORT);
//     server_address.sin_addr.s_addr = INADDR_ANY;

//     bind(server_socket, (sockaddr*)&server_address, sizeof(server_address));
//     listen(server_socket, SOMAXCONN);

//     int epoll_fd = epoll_create1(0);
//     epoll_event event;
//     event.events = EPOLLIN;
//     event.data.fd = server_socket;
//     epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event);

//     std::vector<epoll_event> events(MAX_EVENTS);
//     std::cout << "Server is listening on port " << PORT << "..." << std::endl;

//     while (true) {
// 		Request myRequest(this->servers);
//         int events_count = epoll_wait(epoll_fd, &events[0], MAX_EVENTS, -1);
//         for (int i = 0; i < events_count; ++i) {
//             if (events[i].data.fd == server_socket) {
//                 int client_socket = accept(server_socket, NULL, NULL);
//                 set_nonblocking(client_socket);
//                 event.events = EPOLLIN | EPOLLET;
//                 event.data.fd = client_socket;
//                 epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event);
//                 std::cout << "Client connected. Client socket: " << client_socket << std::endl;
//             } else {
//                 int client_socket = events[i].data.fd;
//                 char buffer[2000];
//                 std::string request;
//                 int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
//                 while (bytes_received > 0) {
//                     request.append(buffer, bytes_received);
//                     bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
//                 }
// 				std::ofstream ofs("request");

// 				ofs.write((char *)buffer, sizeof(buffer));
// 				ofs.close();
// 			    std::string hello;

// 				hello = myRequest.requestStarter(bytes_received, buffer);
//                 std::cout << "Received request from client: " << request << std::endl;
//                 std::string response = "Hello, client!";
//                 send(client_socket, hello.c_str(), 2000, 0);
//                 epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_socket, &event);
//                 close(client_socket);
//                 std::cout << "Client disconnected. Client socket: " << client_socket << std::endl;
//             }
//         }
//     }

//     close(server_socket);
//     return 0;


    int server_fd, new_socket; long valread = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    std::string hello;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    int on = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
		Request myRequest(this->servers.at(0));

        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        bzero(buffer, 30000);
        valread = read( new_socket , buffer, 30000);
		std::cout << "REQUEST \n\n" << buffer << std::endl;
        std::ofstream ofs("request");

        ofs.write((char *)buffer, sizeof(buffer));
        ofs.close();
        hello = myRequest.requestStarter(valread, buffer);
        std::ofstream ofs2("response");
        ofs2 << hello;
        write(new_socket , const_cast<char *>(hello.c_str()), hello.size());
        close(new_socket);
    }
    return 0;
}
 }