/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:38 by wismith           #+#    #+#             */
/*   Updated: 2023/04/25 00:00:14 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

ft::server::server(int nport, std::string pw) : state(SHUTDOWN), opt(1),
				port(nport), password(pw), lstn(), clients(), pfds()
{
	try
	{
		this->opt = 1;
		this->lstn.setInfo(AF_INET, SOCK_STREAM, IPPROTO_TCP, this->port, INADDR_ANY);
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
	while (g_server_run && this->state)
	{
		poll(this->pfds.data(), this->pfds.size(), -1);
		for (size_t i = 0; i < this->pfds.size(); i++)
		{
			if ( this->pfds[i].revents & POLLIN && !i)
        	{
            	int fd = -1;
            	int addressLen = 0;
            	struct sockaddr_in address;
            	memset(&address, 0, sizeof(address));

            	if ( ( fd = accept( this->lstn.getSock(), (sockaddr *)&address, (socklen_t *)&addressLen ) ) < 0 )
					break ;
				this->clients[fd] = ft::client(fd);
				this->pfds.push_back((pollfd){ .fd = fd, .events = POLLIN | POLLOUT, .revents = 0 });
        	}

			// if (this->pfds[i].revents & POLLOUT && i)
			// {
				// this->clients[this->pfds[i].fd].Write("hello from server!\n");
			// }

			if (this->pfds[i].revents & POLLIN)
			{
				std::string str = this->clients[this->pfds[i].fd].Read();
				std::cout << "fd '" << this->pfds[i].fd << "' : " << str; 
				if (this->pfds[i].revents & POLLOUT && i)
					this->clients[this->pfds[i].fd].Write("Server: Acknowledged Command\n");
			}

		}
	}

	for (size_t i = 0; i < this->pfds.size(); i++)
		(i ? close (this->pfds[i].fd) : (int) i);
}


