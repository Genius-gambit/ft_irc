/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinterface.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:26:54 by wismith           #+#    #+#             */
/*   Updated: 2023/05/05 22:03:33 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CINTERFACE_HPP
# define CINTERFACE_HPP

# include "../client.hpp"
# include "../parser.hpp"
# include <map>
# include <vector>
# include <string>
# include <poll.h>

namespace ft
{
	class cinterface
	{
		protected :
			std::map<CLIENT_FD, CLIENT>			&clients;
			std::vector<pollfd>					&pfds;
			std::string							&password;
		public :
			cinterface (std::map<CLIENT_FD, CLIENT> &, std::vector<pollfd> &, std::string &);
			virtual ~cinterface ();

			virtual void exec(int, const std::vector<std::string> &) = 0;
	};
};

#endif