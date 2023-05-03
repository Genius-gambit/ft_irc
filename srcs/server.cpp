/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:45:38 by wismith           #+#    #+#             */
/*   Updated: 2023/05/03 19:02:40 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

/** @brief Port and Password Constructor
 * 		initializes values to default settings
*/
ft::server::server(int nport, std::string pw) : network(pw), state(SHUTDOWN), opt(1),
				port(nport), lstn() {}

/** @brief Destructor 
 * @note closes any open file descriptors 
*/
ft::server::~server()
{
	this->log << "Closing client fds\n";
	for (size_t i = 0; i < this->pfds.size(); i++)
		(i ? close (this->pfds[i].fd) : (int) i);
	this->log << "Shutting Down Server";
	std::cout << "Shutting Down Server\n";
}

/** @brief server init calls lstnInit to initialize the listener,
 * 			pushes a new struct pollfd with values initialized with the macro NPOLL,
 * 			if an exception hasn't been thrown yet, the state is set to RUNNING
*/
void	ft::server::init()
{
	this->log << "initializing the listener";
	std::cout << "Initializing Listener\n";
	this->lstnInit();
	this->pfds.push_back(NPOLL(this->lstn.getSock()));
	this->state = RUNNING;
}

/** @brief lstnInit initializes the listener with the port
 * 			Taken as param for constructor.
 * 			Inits sockaddr_in.
 * 			Sets the socket to non blocking.
 * 			Binds the socket to fd.
 * 			Listens with the socket.
*/
void	ft::server::lstnInit()
{
	this->opt = 1;
	this->log << this->lstn.setInfo(AF_INET, SOCK_STREAM, IPPROTO_TCP, this->port, INADDR_ANY);
	this->log << this->lstn.setSockProto(SOL_SOCKET, SO_REUSEADDR, this->opt);
	this->log << this->lstn.setSockProto(SOL_SOCKET, SO_REUSEPORT, this->opt);
	this->log << this->lstn.nonBlocking();
	this->log << this->lstn.BindConnect();
	this->log << this->lstn.ListenConnect();
}

/** @brief registers a new  client
 * 	@note new client is stored within a std::map
 * 			with key values being the file descriptor returned
 * 			by accept.
 * 		Each client is associated with a pollfd structure stored
 * 			within a vector.
*/
void	ft::server::regNewClient()
{
    int fd = -1;
    int addrlen = 0;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
	
	this->log << "Client Attempting to Connect";
    if ((fd = accept(this->lstn.getSock(), (sockaddr *)&address, (socklen_t *)&addrlen)) < 0 )
	{
		std::cout << "Client not connecting!\n";
		this->log << "Client unable to connect!\n";
		this->log << "accept returned fd : " + (std::string() << fd);
	}
	else
	{
		this->clients[fd] = ft::client(fd);
		this->pfds.push_back(NPOLL(fd));
		this->log << "Accepting new client, fd : " + (std::string() << fd);
	}
}

void	ft::server::run()
{
	std::cout << "Server Running ...\n";
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

			if (this->pfds[i].revents & POLLIN && i)
			{
				std::string str = M_CLIENT(i).Read();
				this->pRecv(str);

				this->selCmd(this->getCmds(), i);
				
				std::cout << "\n -- parsed -- \n";
				this->printCmds();
				std::cout << "-- finished parse --\n";
			}
			this->clear();
		}
	}
}


