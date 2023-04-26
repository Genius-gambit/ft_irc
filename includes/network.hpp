/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:15:29 by wismith           #+#    #+#             */
/*   Updated: 2023/04/26 18:34:33 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef NETWORK_HPP
# define NETWORK_HPP

# include "client.hpp"
# include <unistd.h>
# include <map>
# include <vector>
# include <string>
# include <iostream>

namespace ft
{
	class network
	{
		protected :
			std::map<CLIENT_FD, CLIENT>			clients;
			std::vector<pollfd>					pfds;
			std::string							password;

		private :

		/** @brief commands */

			/** @brief client requested to quit */
			void	quit(int i_pfds);

		/** @brief General validation */

			/** @brief validate client password */
			void	pass(int i_pfds, const std::vector<std::string> &cmds);
			void	nick(int i_pfds, const std::vector<std::string> &cmds);

		public :
			network (std::string pw);
			~network ();

			void	selCmd(const std::vector<std::string> &cmds, int i_pfds);
	};
};

#endif