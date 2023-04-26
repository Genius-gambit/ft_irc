/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:33:29 by wismith           #+#    #+#             */
/*   Updated: 2023/04/26 15:19:24 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/poll.h>
# include <sys/socket.h>
# include <strings.h>
# include <string>
# include <vector>

# define ILLEGAL 0 	//! Client password not authenticated
# define VERIFIED 1 //! Client password authenticated

# define CLIENT ft::client
# define CLIENT_FD int

/** @brief M_CLIENT macro is used in place of accessing a mapped client
 * 			using the [] operator.
*/
# define M_CLIENT(i) this->clients[this->pfds[i].fd]

namespace ft
{
	class client
	{
		private :
			int				fd; 	//! Client fd to read / write to
			int				status; //! Illegal / Verified
			std::string		nick;	//! Client nickname


		public :
			client ();
			client (const client &c);
			client (int nfd);
			~client();

			client	&operator=(const client &c);

			std::string		Read();
			void			Write(std::string str);

			void			setFd(int nfd);
			void			setStatus(int stat);
			void			setNick(const std::string &Nick);

			int				getFd() const;
			int				getStatus() const;
			std::string		getNick() const;
	};
};

#endif