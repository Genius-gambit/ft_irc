/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connecter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:46:27 by wismith           #+#    #+#             */
/*   Updated: 2023/04/14 17:48:14 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CONNECTER_HPP
# define CONNECTER_HPP

# include "SetSocket.hpp"

namespace ft
{
	class Connecter : public SetSocket
	{
		private :
			Connecter();
			Connecter(const Connecter &b);
			Connecter	&operator=(const Connecter &b);
			
		public :
			Connecter(int domain, int service, int protocol, int port, unsigned long interface);
			
			int connect_net(int sock, struct sockaddr_in address);
			
	};
};

#endif