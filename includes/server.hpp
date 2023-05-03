/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:30:56 by wismith           #+#    #+#             */
/*   Updated: 2023/05/03 18:40:54 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef SERVER_HPP
# define SERVER_HPP


# include <map>
# include <sys/poll.h>
# include <string>
# include <vector>
# include "signals.hpp"
# include "client.hpp"
# include "network.hpp"
# include "../ftServerUtils/includes/Listener.hpp"

/** @brief NPOLL macro is used to define a pollfd struct
 * 	@note takes a new fd as arg
*/
# define NPOLL(nfd) (struct pollfd){ .fd = nfd, .events = POLLIN | POLLOUT, .revents = 0 }

# define RUNNING 1
# define SHUTDOWN 0

/*
*	struct pollfd
*	{
*		int fd;
*		int	events = POLLIN | POLLOUT;
*		int revents = 0;
*	}
*
*	struct pollfd *pfds
*/

namespace ft
{
	class server : public network
	{
		private :
			int							state;
			int							opt;
			int							port;
			ft::Listener				lstn;

			void	lstnInit();
			void	regNewClient();

		public :
			server (int nport, std::string pw);
			~server ();

			void	init();
			void	run();
	};
};

#endif