/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:27:19 by wismith           #+#    #+#             */
/*   Updated: 2023/05/08 16:56:00 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/commands.hpp"

using namespace ft;

cap::cap(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

cap::~cap() {}

void	cap::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void) cmds;
	std::string	cap;
	if (cmds[1] == "LS")
		M_CLIENT(i_pfds).Write("CAP * LS :multi-prefix sasl message-tags server-time\r\n");
	// if (this->pfds[i_pfds].revents & POLLOUT && cmds[1] != "LS")
	// else if (this->pfds[i_pfds].revents & POLLOUT && cmds[1] == "REQ")
	// 	M_CLIENT(i_pfds).Write("CAP * LS :multi-prefix sasl message-tags server-time\r\n");
	std::cout << cap << std::endl;
}