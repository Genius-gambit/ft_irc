/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:04 by wismith           #+#    #+#             */
/*   Updated: 2023/05/12 02:00:51 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

using namespace ft;

pass::pass(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

pass::~pass() {}

void	pass::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	if (this->password != cmds[1])
	{
		if (this->pfds[i_pfds].revents & POLLOUT)
			"localhost 464 johnsmith :Incorrect Password!\r\n" >> M_CLIENT(i_pfds);
		M_CLIENT(i_pfds).setStatus(ILLEGAL);
	}
}
