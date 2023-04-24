/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:38 by wismith           #+#    #+#             */
/*   Updated: 2023/04/25 01:16:50 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

struct pollfd	newPollfd(int fd)
{
	return (
		(struct pollfd){
			.fd = fd,
			.events = POLLIN | POLLOUT,
			.revents = 0
		}
	);
}

ft::server::server(int nport, std::string pw) : state(SHUTDOWN), opt(1),
				port(nport), password(pw), lstn(), clients(), pfds() {}

ft::server::~server()
{
	for (size_t i = 0; i < this->pfds.size(); i++)
		(i ? close (this->pfds[i].fd) : (int) i);
}

void	ft::server::init()
{
	this->lstnInit();
	this->pfds.push_back(newPollfd(this->lstn.getSock()));
	this->state = RUNNING;
}

void	ft::server::lstnInit()
{
	this->opt = 1;
	this->lstn.setInfo(AF_INET, SOCK_STREAM, IPPROTO_TCP, this->port, INADDR_ANY);
	this->lstn.setSockProto(SOL_SOCKET, SO_REUSEADDR, this->opt);
	this->lstn.setSockProto(SOL_SOCKET, SO_REUSEPORT, this->opt);
	this->lstn.nonBlocking();
	this->lstn.BindConnect();
	this->lstn.ListenConnect();
}

void	ft::server::regNewClient()
{
    int fd = -1;
    int addrlen = 0;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

    if ((fd = accept(this->lstn.getSock(), (sockaddr *)&address, (socklen_t *)&addrlen)) < 0 )
		return ; // throw an Error!
	this->clients[fd] = ft::client(fd);
	this->pfds.push_back(newPollfd(fd));
}

void	ft::server::run()
{
	while (g_server_run && this->state)
	{
		poll(this->pfds.data(), this->pfds.size(), -1);
		for (size_t i = 0; i < this->pfds.size(); i++)
		{
			if (this->pfds[i].revents & POLLIN && !i)
				this->regNewClient();

			// if (this->pfds[i].revents & POLLOUT && i)
			// {
				// this->clients[this->pfds[i].fd].Write("hello from server!\n");
			// }

			if (this->pfds[i].revents & POLLIN)
			{
				std::string str = this->clients[this->pfds[i].fd].Read();
				std::cout << str;
				if (this->pfds[i].revents & POLLOUT && i)
					this->clients[this->pfds[i].fd].Write("Server: Acknowledged Command\n");
			}
		}
	}
}


