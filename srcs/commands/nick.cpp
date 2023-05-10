/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:38:01 by wismith           #+#    #+#             */
/*   Updated: 2023/05/10 20:07:04 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/commands.hpp"

using namespace ft;

nick::nick(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

nick::~nick() {}

void	nick::welcome(ft::client &c)
{
	c.addBacklog(": localhost "
		+ RPL_WELCOME + " " + c.getNick()
		+ " :\n\nWelcome to ircserv " + c.getNick() + "!\r\n");
}

void	nick::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::string	nick;

	nick = cmds[1];
	for (size_t i = 1; i < this->pfds.size(); i++)
	{
		if (i != (size_t)i_pfds && M_CLIENT(i).getNick() == nick)
		{
			M_CLIENT(i_pfds).addBacklog("NICK : localhost "
				+ (std::string() << ERR_NICKNAMEINUSE) + " * " + nick
				+ " :Nickname already in use\r\n");
			return ;
		}
	}
	M_CLIENT(i_pfds).setNick(nick);
	this->welcome(M_CLIENT(i_pfds));
}