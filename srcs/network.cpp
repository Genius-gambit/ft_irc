/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:17:52 by wismith           #+#    #+#             */
/*   Updated: 2023/04/26 19:50:09 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.hpp"

using namespace ft;

network::network(std::string pw) : clients(), pfds(), password(pw) {}

network::~network() {}

void	network::quit(int i_pfds)
{
	if (pfds[i_pfds].revents & POLLOUT)
		M_CLIENT(i_pfds).Write(M_CLIENT(i_pfds).getNick() + " Quiting ircserv\n");
	clients.erase(pfds[i_pfds].fd);
	close (pfds[i_pfds].fd);
	pfds.erase(pfds.begin() + i_pfds);
}

void	network::pass(int i_pfds, const std::vector<std::string> &cmds)
{
	if (cmds[1] == this->password)
		M_CLIENT(i_pfds).setStatus(VERIFIED);
	// if ()
	// std::cout << "Client status verified\n";
}

void	network::nick(int i_pfds, const std::vector<std::string> &cmds)
{
	M_CLIENT(i_pfds).setNick(cmds[1]);
	std::cout << "Set client nickname to: " + cmds[1] << "\n";
}

void	network::selCmd(const std::vector<std::string> &cmds, int i_pfds)
{
	size_t	i = 0;
	std::map<int, std::string>	m_cmds;

	m_cmds[0] = "QUIT";
	m_cmds[1] = "PASS";
	m_cmds[2] = "NICK";
	for (; i < m_cmds.size() && m_cmds[i] != cmds[0]; i++)
		;
	switch (i){
		case 0:
			network::quit(i_pfds);
		break ;
		case 1:
			network::pass(i_pfds, cmds);
		break ;
		case 2:
			network::nick(i_pfds, cmds);
		break ;
	};
}
