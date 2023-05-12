/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:17:52 by wismith           #+#    #+#             */
/*   Updated: 2023/05/11 17:44:24 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.hpp"

using namespace ft;

network::network(std::string pw) : ft::parser(), clients(), pfds(), password(pw)
{
	this->cmds["QUIT"] = new ft::quit(this->clients, this->pfds, this->password);
	this->cmds["CAP"] = new ft::cap(this->clients, this->pfds, this->password);
	this->cmds["JOIN"] = new ft::join(this->clients, this->pfds, this->password, this->chans);
	this->cmds["NICK"] = new ft::nick(this->clients, this->pfds, this->password);
	this->cmds["PASS"] = new ft::pass(this->clients, this->pfds, this->password);
}

network::~network()
{
	std::map<std::string, ft::cinterface *>::iterator	it;

	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
		delete it->second;
}

void	network::selCmd(const std::vector<std::string> &v_cmds, int i_pfds)
{
	std::map<std::string, ft::cinterface *>::iterator	it;

	it = this->cmds.find(v_cmds[0]);
	if (it != this->cmds.end())
		it->second->exec(i_pfds, v_cmds);
}
