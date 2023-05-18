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
	std::map<std::string, ft::channels>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

join::~join() {}

void	join::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::map<std::string, ft::channels>::iterator	it = this->chan.find(cmds[1]);
	if (it == this->chan.end())
	{
		this->chan[cmds[1]] = ft::channels(&this->clients);
		this->chan[cmds[1]].setChannelName(cmds[1]);
		if (cmds.size() > 2)
			this->chan[cmds[1]].setChannelPass(cmds[2]);
	}
	if ((this->chan[cmds[1]].get_pass().empty())
		|| ((cmds.size() > 2)
		&& (cmds[2] == this->chan[cmds[1]].get_pass())))
		this->chan[cmds[1]].add_clients(M_CLIENT(i_pfds).getFd());
	else
		std::cout << "Wrong Password!" << std::endl;
	// std::cout << std::endl << "****Channel Info****" << std::endl;
	// std::cout << "Channel Name: " << this->chan[cmds[1]].getChannelName() << std::endl;
	// std::cout << "Channel Pass: " << this->chan[cmds[1]].get_pass() << std::endl;
	// std::cout << "Clients: " << this->chan[cmds[1]].get_length() << std::endl;
	// for (std::map<std::string, ft::channels>::iterator it = this->chan.begin(); it != this->chan.end();it++)
	// {
	// 	std::cout << "Start" << std::endl;
	// 	this->chan[it->first].print_clients();
	// 	std::cout << "End" << std::endl;
	// }
}

