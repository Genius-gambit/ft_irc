/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:45:33 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 02:46:01 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdlib.h>
# include <unistd.h>

namespace	ft
{
	class SetSocket
	{
		private :
			struct sockaddr_in	address;
			int					sock;
			int					connection;

			SetSocket();
			SetSocket(const SetSocket &s);
			SetSocket	&operator=(const SetSocket &s);

		public :
			SetSocket(int domain, int service, int protocol, int port, unsigned long interface);
			~SetSocket();
			
			virtual	int connect_net(int sock, struct sockaddr_in address) = 0;

			struct sockaddr_in	getAddress() const;
			int					getSock() const;
			int					getConnection() const;

			void				setConnection(int);
	};
};

#endif