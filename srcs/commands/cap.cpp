/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:27:19 by wismith           #+#    #+#             */
/*   Updated: 2023/05/09 16:55:51 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

using namespace ft;

cap::cap(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

cap::~cap() {}

void	cap::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	if (cmds[1] == "LS")
		M_CLIENT(i_pfds).addBacklog("CAP * LS :multi-prefix server-time\r\n");
	else if (cmds[1] == "REQ")
		M_CLIENT(i_pfds).addBacklog("CAP * ACK :multi-prefix server-time\r\n");
	else if (cmds[1] == "END")
	{
		M_CLIENT(i_pfds).setStatus(VERIFIED);
		this->welcome(M_CLIENT(i_pfds));
	}
}