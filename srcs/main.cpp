/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:07:24 by wismith           #+#    #+#             */
/*   Updated: 2023/04/21 12:58:41 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"
#include <poll.h>

int	main(int argc, char **argv)
{
	/**	@brief : variable contains port number after parsing */
	int			port;

	/**	@brief : Check arguments are valid */
	try{
		error().argc(argc);
		port = error().port(argv[1]);
	}catch(const std::exception &e){
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	try
	{
		int	opt = 1;
		ft::Listener	lstn;
		lstn.setInfo(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY);
		lstn.setSockProto(SOL_SOCKET, SO_REUSEADDR, opt);
		lstn.setSockProto(SOL_SOCKET, SO_REUSEPORT, opt);
		lstn.nonBlocking();
		lstn.BindConnect();
		lstn.ListenConnect();

		/**	@brief : handle signals */
		catch_signals();
	
		int	new_socket;
		int	addrlen = sizeof(lstn.getAddress());

		//! --------- POLL INIT

		struct pollfd	p[3];
		memset(&p, 0, sizeof(p));
		
		new_socket = -1;
		p[0].fd = lstn.getSock();
		p[0].events = POLLIN;
		poll(p, 3, -1);
		if (p[0].revents == POLLIN && (new_socket
        	= accept(lstn.getSock(), (struct sockaddr*)&lstn.getAddress(),
            		(socklen_t*)&addrlen)) >= 0)

		//! -------- End POLL INIT

		/**	@brief : run server */
		while (g_server_run)
		{
			{
				p[1].fd = new_socket;
				p[1].events = POLLIN;
				if (poll(p, 3, -1) >= 0 && p[1].revents == POLLIN)
				{
					std::cout << ft::Reader(new_socket).retrieve().getData();
					p[1].fd = new_socket;
					p[1].events = POLLOUT;
					if (poll(p, 3, -1) >= 0 && p[1].revents == POLLOUT)
						send(new_socket, "Hello from Server\n", strlen("Hello from Server\n"), 0);
				}
        	}
		}
		close (new_socket);

		/**	@brief : free stuff if necessary */
	
	}
	catch (const std::exception &e)
	{ std::cerr << e.what() << std::endl; }
	return (0);
}