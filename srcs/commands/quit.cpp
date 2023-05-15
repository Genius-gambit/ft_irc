/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:52:49 by wismith           #+#    #+#             */
/*   Updated: 2023/05/11 17:53:11 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

using namespace ft;

quit::quit(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

quit::~quit() {}

std::string	pars(const std::vector<std::string> &cmds)
{
	std::string	res;

	for (size_t i = 1; i < cmds.size(); i++)
	{
		res += cmds[i];
		if (i != cmds.size() - 1)
			res += ' ';
	}
	return (res);
}

void	quit::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	ft::client	&client = M_CLIENT(i_pfds);

	client.markClientForDel();
	client.addBacklog(":" + client.getNick()
		+ " QUIT :" + pars(cmds) + "\r\n");
}
