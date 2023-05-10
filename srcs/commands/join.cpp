/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:02:51 by wismith           #+#    #+#             */
/*   Updated: 2023/05/10 20:40:18 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands/commands.hpp"

using namespace ft;

join::join(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

join::~join() {}

void	join::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::cout << "Client joining Channel" << std::endl;
	this->chan[cmds[1]] = ft::channels();
	this->chan[cmds[1]].add_clients(M_CLIENT(i_pfds).getFd());
	this->chan[cmds[1]].setChannelName(cmds[1]);
}

