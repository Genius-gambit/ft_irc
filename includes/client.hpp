/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:33:29 by wismith           #+#    #+#             */
/*   Updated: 2023/04/25 02:09:38 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/poll.h>
# include <sys/socket.h>
# include <strings.h>
# include <string>

# define ILLEGAL 0 	//! Client password not authenticated
# define VERIFIED 1 //! Client password authenticated

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