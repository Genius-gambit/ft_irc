/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:49:24 by wismith           #+#    #+#             */
/*   Updated: 2023/05/05 21:52:06 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef QUIT_HPP
# define QUIT_HPP

# include "cinterface.hpp"

namespace ft
{
	class quit : public ft::cinterface
	{
		public :
			quit (std::map<CLIENT_FD, CLIENT> &, std::vector<pollfd> &, std::string &);
			~quit ();

			void exec(int, const std::vector<std::string> &);
	};
};

#endif