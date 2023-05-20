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
# include <map>
# include <string>

#include "client.hpp"

# define IS_OPP bool

namespace ft
{
	class channels
	{
		private :
			std::vector<int>			fds;
			std::string					_chan;
			std::string					_pass;
			int							_len;
			std::string					_topic;
			std::map<CLIENT_FD, CLIENT>	&clients;
			std::map<CLIENT_FD, IS_OPP> opps;

		public :
										channels( std::map<CLIENT_FD, CLIENT> &client );
										channels( const channels &other );
										~channels();

			channels					&operator=(const channels &);

			std::vector<int>			&getFds();
			void						setChannelName( const std::string & );
			void						setChannelPass( const std::string & );
			void						add_clients( int fd );
			void						kick_client( int fd );
			int							get_length( void );
			void						print_clients();
			std::string					get_pass();
			std::string					getChannelName();
			void						sendToAll( const std::string &, std::map<int, CLIENT> &, int );
	};
};

#endif