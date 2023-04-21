/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Listener.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:57:26 by wismith           #+#    #+#             */
/*   Updated: 2023/04/20 14:43:50 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LISTENER_HPP
# define LISTENER_HPP

# include "SetSocket.hpp"

namespace ft
{
	class Listener : public ft::SetSocket
	{
		private :
			int			backlog;

			Listener(const Listener &l);
			Listener	&operator=(const Listener &l);
			int			connect_net(int sock, struct sockaddr_in addr);

		public :
			Listener();
			~Listener();

			void	setInfo(int domain, int service, int protocol,
					int port, unsigned long interface);

			void	setSockProto(int level, int option_name, int &opt);
			void	nonBlocking();
			void	BindConnect();
			void	ListenConnect();
	};
};

#endif