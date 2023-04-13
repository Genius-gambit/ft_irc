/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 23:45:33 by wismith           #+#    #+#             */
/*   Updated: 2023/04/13 23:57:30 by wismith          ###   ########.fr       */
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
			SetSocket();
			SetSocket(const SetSocket &s);
			SetSocket	&operator=(const SetSocket &s);

		public :
			~SetSocket();

	};
};

#endif