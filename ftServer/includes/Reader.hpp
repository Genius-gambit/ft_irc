/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:19:59 by wismith           #+#    #+#             */
/*   Updated: 2023/04/18 17:42:41 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef READER_HPP
# define READER_HPP

# include <iostream>
# include "SetSocket.hpp"

# define BUFFER 510

namespace ft
{
	class Reader
	{
		private :
			std::string	*data;
			int			fd;

		public :
			Reader();
			Reader(int nfd);
			Reader(const Reader &r);
			~Reader();

			Reader	&operator=(const Reader &r);

			Reader	&retrieve();

			void	setFd(int nfd);
			std::string	getData();
	};
};

#endif