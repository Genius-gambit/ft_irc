/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:27:19 by wismith           #+#    #+#             */
/*   Updated: 2023/05/07 18:08:42 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/cap.hpp"


using namespace ft;

cap::cap(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

cap::~cap() {}

void	cap::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void) cmds;
	std::string	cap;
	if (this->pfds[i_pfds].revents & POLLOUT)
		this->clients[this->pfds[i_pfds].fd].Write("CAP * LS :multi-prefix sasl message-tags server-time\r\n");
	std::cout << cap << std::endl;
}