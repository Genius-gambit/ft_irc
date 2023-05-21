/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:02:51 by wismith           #+#    #+#             */
/*   Updated: 2023/05/12 15:31:20 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

using namespace ft;

join::join(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels *>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

join::~join() {}

void	join::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::map<std::string, ft::channels *>::iterator	it = this->chan.find(cmds[1]);
	if (it == this->chan.end())
	{
		if (cmds[1][0] != '#')
		{
			M_CLIENT(i_pfds).addBacklog("Channel Name needs to be followed by #!\r\n");
			return ;
		}
		this->chan[cmds[1]] = new ft::channels(this->clients);
		this->chan[cmds[1]]->setChannelName(cmds[1]);
		if (cmds.size() > 2)
			this->chan[cmds[1]]->setChannelPass(cmds[2]);
		this->chan[cmds[1]]->op(M_CLIENT(i_pfds).getFd());
		std::cout << this->chan[cmds[1]]->getOp(M_CLIENT(i_pfds).getFd()) << std::endl;
	}
	if ((this->chan[cmds[1]]->get_pass().empty())
		|| ((cmds.size() > 2)
		&& (cmds[2] == this->chan[cmds[1]]->get_pass())))
		this->chan[cmds[1]]->add_clients(M_CLIENT(i_pfds).getFd());
	else
		std::cout << "Wrong Password!" << std::endl;
}

