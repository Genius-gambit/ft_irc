/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:33:29 by wismith           #+#    #+#             */
/*   Updated: 2023/05/11 14:29:32 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sys/socket.h>
# include <string>
# include <list>
# include "../ftServerUtils/includes/ServerUtility.hpp"

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
			int						fd;			//! Client fd to read / write to
			int						status;		//! Illegal / Verified
			bool					markForDel; //! Mark the client to be deleted
			bool					passCheck;
			bool					markForKick;
			std::string				buffer;
			std::string				nick;		//! Client nickname
			std::string				username;	//! Client username
			std::string				realname;	//! Client realname
			std::string				hostname;	//! Client hostname
			std::string				servername;	//! Client servername
			std::string				mode;		//! Client mode
			std::list<std::string>	backlog;	//! reply to Client backlog


		public :
									client ();
									client (const client &c);
									client (int nfd);
									~client();

			client					&operator=(const client &c);

			std::string				Read();
			void					Write(std::string str);

			void					addBacklog(const std::string);	//! Adds a reply to client
			size_t					getBacklogSize() const; 		//! gets backlog size
			std::string				retrBacklog(); 					//! retrieves backlog
			void					markClientForDel();

			void					setFd(int nfd);
			void					setStatus(int stat);
			void					setPassCheck(bool);
			void					setNick(const std::string &Nick);
			void					setRealname(const std::string &Realname);
			void					setHostname(const std::string &Hostname);
			void					setMode(const std::string &Mode);

			int						getFd() const;
			int						getStatus() const;
			bool					getIsMarkForDel() const;
			bool					getPassCheck() const;
			std::string				getNick() const;
			std::string				getRealname() const;
			std::string				getHostname() const;
			std::string				getMode() const;

	};
};

/** @brief operator writes to a client */
void			operator>>(const std::string &str, ft::client &c);

/** @brief operator recieves command from client*/
std::string		&operator<<(std::string &str, ft::client &c);

#endif