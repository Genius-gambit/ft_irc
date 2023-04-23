/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:38 by wismith           #+#    #+#             */
/*   Updated: 2023/04/23 00:14:23 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

ft::server::server(int nport, std::string pw) : state(SHUTDOWN), opt(1), port(nport), password(pw), lstn(), clients(), pfds()
{
	try
	{
		this->opt = 1;
		this->lstn.setInfo(AF_INET, SOCK_STREAM, 0, this->port, INADDR_ANY);
		this->lstn.setSockProto(SOL_SOCKET, SO_REUSEADDR, this->opt);
		this->lstn.setSockProto(SOL_SOCKET, SO_REUSEPORT, this->opt);
		this->lstn.nonBlocking();
		this->lstn.BindConnect();
		this->lstn.ListenConnect();
		this->server_pfd.fd = lstn.getSock();
		this->server_pfd.events = POLLIN;
		this->pfds.push_back(this->server_pfd);
		this->state = RUNNING;
	} catch (const std::exception &e)
	{
		std::cerr << "Server Failed to start!\n";
		std::cerr << e.what() << std::endl;
	}
}

ft::server::~server() {}

void	ft::server::run()
{
	int	new_client;
	int	addrlen = sizeof(lstn.getAddress());

	while (g_server_run && this->state)
	{
		poll(&this->pfds[0], this->pfds.size(), 1000);

		if (this->pfds[0].revents == POLLIN
			&& (new_client = accept(lstn.getSock(), (struct sockaddr*)&lstn.getAddress(),
            		(socklen_t*)&addrlen)) >= 0)
		{
			this->pfds.push_back(pollfd());
			this->pfds.back().fd = new_client;
			this->pfds.back().events = POLLIN;
			this->clients[new_client] = ft::client(new_client);
		}

		for (std::vector<struct pollfd>::iterator it = this->pfds.begin()
			; it != this->pfds.end(); it++)
		{
			if (it->revents == POLLIN)
			{
				std::cout << this->clients[it->fd].Read();
				this->clients[it->fd].Write("hello from server!\n");
			}
		}
	}
	for (std::map<CLIENT_FD, CLIENT>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		close (it->second.getFd());
}
