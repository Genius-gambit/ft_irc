/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:52:49 by wismith           #+#    #+#             */
/*   Updated: 2023/05/05 21:57:43 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/quit.hpp"

using namespace ft;

quit::quit(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

quit::~quit() {}

void	quit::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void) cmds;
	if (pfds[i_pfds].revents & POLLOUT)
		M_CLIENT(i_pfds).Write(M_CLIENT(i_pfds).getNick() + " Quiting ircserv\n");
	clients.erase(pfds[i_pfds].fd);
	close (pfds[i_pfds].fd);
	pfds.erase(pfds.begin() + i_pfds);
}
