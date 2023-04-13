/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Binder.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:22:52 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 02:56:59 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BINDER_HPP
# define BINDER_HPP

#include "SetSocket.hpp"

namespace ft
{
	class Binder : public SetSocket
	{
		private :
			Binder();
			Binder(const Binder &b);
			Binder	&operator=(const Binder &b);
			
		public :
			Binder(int domain, int service, int protocol, int port, unsigned long interface);
			
			int connect_net(int sock, struct sockaddr_in address);
			
	};
};

#endif