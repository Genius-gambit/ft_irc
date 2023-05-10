/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:43:42 by wismith           #+#    #+#             */
/*   Updated: 2023/05/10 19:52:55 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef CHANNELS_HPP
# define CHANNELS_HPP

# include <vector>

namespace ft
{
	class channels
	{
		private :
			std::vector<int>	fds;
		public :
			std::vector<int>	&getFds();
	};
};

/*

for (size_t i = 0; i < channels.getFds().size(); i++)
{
	this->clients[channels.getFds()[i]].addBacklog("hi bob");
}

*/

#endif