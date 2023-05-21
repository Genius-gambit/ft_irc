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

void	join::welcome(ft::client &client, std::string chan)
{
	this->chan[chan]->sendToAll( ":" + this->sender(client)
									+ " JOIN :"
									+ chan
									+ "\r\n", this->clients, -1 );

	std::string	clientList;
	std::vector<int>	&chanFds = this->chan[chan]->getFds();
	for (size_t i = 0; i < chanFds.size(); i++)
		clientList += this->clients[chanFds[i]].getNick() + " ";

	client.addBacklog(": "
						+ RPL_NAMREPLY
						+ " "
						+ client.getNick()
						+ " = "
						+ chan
						+ " :"
						+ clientList
						+ "\r\n");

	client.addBacklog(": "
						+ RPL_ENDOFNAMES
						+ " "
						+ client.getNick()
						+ " "
						+ chan
						+ " :End of /NAMES list.\r\n");
}

void	join::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	ft::client	&client = M_CLIENT(i_pfds);
	std::map<std::string, ft::channels *>::iterator	it = this->chan.find(cmds[1]);

	if (it != this->chan.end())
	{
		bool		empty	= this->chan[cmds[1]]->get_pass().empty();
		std::string	pw		= this->chan[cmds[1]]->get_pass();

		if (!empty && (cmds.size() <= 2 || cmds[2] != pw))
		{
			client.addBacklog(ERR_BADCHANNELKEY
						+ " "
						+ client.getNick()
						+ " "
						+ " :Incorrect Channel Password\r\n");
			return ;
		}
	}
	else
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
	this->chan[cmds[1]]->add_clients(client.getFd());
	this->welcome(client, cmds[1]);
}

