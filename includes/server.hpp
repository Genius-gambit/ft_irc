/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:30:56 by wismith           #+#    #+#             */
/*   Updated: 2023/04/22 14:48:25 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef SERVER_HPP
# define SERVER_HPP

# include <map>
# include <sys/poll.h>
# include <string>
# include "signals.hpp"
# include "client.hpp"
# include "../ftServerUtils/includes/Listener.hpp"

# define CLIENT ft::client
# define CLIENT_FD int
# define RUNNING 1
# define SHUTDOWN 0

namespace ft
{
	class server
	{
		private :
			int							state;
			int							opt;
			int							port;
			std::string					password;
			ft::Listener				lstn;
			struct pollfd 				server_pfd;
			std::map<CLIENT_FD, CLIENT>	clients;
			std::vector<pollfd>			pfds;
			
		public :
			server (int nport, std::string pw);
			~server ();

			void	run();
	};
};

#endif