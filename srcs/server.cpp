/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:38 by wismith           #+#    #+#             */
/*   Updated: 2023/04/21 20:27:17 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

ft::server::server(int nport, std::string pw) : state(SHUTDOWN), opt(1), port(nport), password(pw), lstn(), clients()
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
		poll(&this->server_pfd, 1, 100);
		if (this->server_pfd.revents == POLLIN
			&& (new_client = accept(lstn.getSock(), (struct sockaddr*)&lstn.getAddress(),
            		(socklen_t*)&addrlen)) >= 0)
			this->clients[new_client] = ft::client(new_client);

		for (std::map<CLIENT_FD, CLIENT>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		{
			if (poll(it->second.getPfd(), 3, 100) >= 0 && it->second.getPfd()[IN].revents == POLLIN)
			{
				std::cout << it->second.Read();
				if (poll(it->second.getPfd(), 3, 100) >= 0
					&& it->second.getPfd()[OUT].revents == POLLOUT)
					it->second.Write("Hello from Server!\n");
			}
		}
	}
	for (std::map<CLIENT_FD, CLIENT>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		close (it->second.getFd());
}
