/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:15:29 by wismith           #+#    #+#             */
/*   Updated: 2023/05/07 17:36:24 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef NETWORK_HPP
# define NETWORK_HPP

# include "client.hpp"
# include "parser.hpp"
# include "commands/cinterface.hpp"
# include <unistd.h>
# include <map>
# include <vector>
# include <string>
# include <iostream>

namespace ft
{
	class network : public ft::parser
	{
		protected :
			std::map<std::string, ft::cinterface *>	cmds;
			std::map<CLIENT_FD, CLIENT>				clients;
			std::vector<pollfd>						pfds;
			std::string								password;

		public :
			network (std::string pw);
			~network ();

			void	selCmd(const std::vector<std::string> &cmds, int i_pfds);
	};
};

# include "commands/quit.hpp"
# include "commands/cap.hpp"

#endif