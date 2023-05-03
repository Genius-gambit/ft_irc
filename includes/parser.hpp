/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:14:03 by wismith           #+#    #+#             */
/*   Updated: 2023/05/03 18:45:16 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <vector>
# include <sstream>
# include <iostream>
# include "../ftServerUtils/includes/log.hpp"

namespace ft
{
	class parser
	{
		private :
		std::vector<std::string>	cmds;

		protected :
		ft::log						log;

		public :
			parser();
			~parser();

			void	pRecv(const std::string &str);
			void	printCmds();
			void	clear();

			std::vector<std::string>	&getCmds();
	};
};

#endif