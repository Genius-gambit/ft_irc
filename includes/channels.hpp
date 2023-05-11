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
# include <string>

namespace ft
{
	class channels
	{
		private :
			std::vector<int>	fds;
			std::string	_chan;
			int			_len;
		public :
			channels();
			~channels();
			std::vector<int>	&getFds();
			void	setChannelName(const std::string &);
			void	add_clients(int fd);
			void	kick_client(int fd);
			int		get_length(void);
			void	print_clients();
	};
};

/*

for (size_t i = 0; i < channels.getFds().size(); i++)
{
	this->clients[channels.getFds()[i]].addBacklog("hi bob");
}

*/

#endif