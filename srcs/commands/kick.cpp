#include "../../includes/commands.hpp"
#include <bits/stdc++.h>

using namespace ft;

kick::kick(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels *>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

kick::~kick() {}

void	kick::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	if (cmds.size() >= 3)
	{
		std::map<std::string, ft::channels *>::iterator	it = this->chan.find(cmds[1]);
		std::vector<int>	getFd = this->chan[cmds[1]]->getFds();
		if (it != this->chan.end() && std::find(getFd.begin(), getFd.end(),
			M_CLIENT(i_pfds).getFd()) != getFd.end())
		{
			if (this->chan[cmds[1]]->getOp(M_CLIENT(i_pfds).getFd()) == true)
			{
				std::string	cpy = cmds[2];
				std::string	msg = cpy + " has been kicked from "
					+ (this->chan[cmds[1]]->getChannelName()) + " by "
					+ M_CLIENT(i_pfds).getNick() + "\r\n";
				this->chan[cmds[1]]->kick_client(cpy, msg);
			}
			else
				M_CLIENT(i_pfds).addBacklog("Not a channel Operator!\r\n");
		}
		else
			M_CLIENT(i_pfds).addBacklog("Not a channel name or member of the channel!\r\n");
	}
}