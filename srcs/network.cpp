/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:17:52 by wismith           #+#    #+#             */
/*   Updated: 2023/05/08 16:59:00 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.hpp"

using namespace ft;

network::network(std::string pw) : ft::parser(), clients(), pfds(), password(pw)
{
	this->cmds["QUIT"] = new ft::quit(this->clients, this->pfds, this->password);
	this->cmds["CAP"] = new ft::cap(this->clients, this->pfds, this->password);
}

network::~network()
{
	std::map<std::string, ft::cinterface *>::iterator	it;

	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
		delete it->second;
}

void	network::selCmd(const std::vector<std::string> &cmds, int i_pfds)
{
	if (this->cmds.find(cmds[0]) != this->cmds.end())
		this->cmds[cmds[0]]->exec(i_pfds, cmds);
	// size_t	i = 0;
	// std::map<int, std::string>	m_cmds;

	
	// for (; i < m_cmds.size() && m_cmds[i] != cmds[0]; i++)
	// 	;
	// switch (i){
	// 	case 0:
	// 		network::quit(i_pfds);
	// 	break ;
	// 	case 1:
	// 		network::pass(i_pfds, cmds);
	// 	break ;
	// 	case 2:
	// 		network::nick(i_pfds, cmds);
	// 	break ;
	// 	default:
	// 		std::cout << "Command not found" << std::endl;
	// };
}
