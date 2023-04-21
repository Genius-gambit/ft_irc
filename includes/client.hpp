/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:33:29 by wismith           #+#    #+#             */
/*   Updated: 2023/04/21 20:39:42 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/poll.h>
# include "../ftServer/includes/Reader.hpp"

# define IN 0
# define OUT 1

namespace ft
{
	class client
	{
		private :
			int	fd;
			struct pollfd	pfd[3];
			ft::Reader		reader;

			client (const client &c);

		public :
			client ();
			client (int nfd);
			~client();

			client	&operator=(const client &c);

			std::string		Read();
			void			Write(std::string str);

			struct pollfd	*getPfd();

			void			setFd(int nfd);
			int				getFd() const;
	};
};

#endif