#include "../../includes/commands.hpp"

using namespace ft;

privmsg::privmsg(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

privmsg::~privmsg() {}

void	privmsg::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::string	chan_name;
	std::string	nick;
	std::string	msg;

	if (cmds[0] == "PRIVMSG")
	{
		if (cmds.size() >= 3)
		{
			if (cmds[1][0] == '#')
			{
				chan_name = cmds[1];
				nick = M_CLIENT(i_pfds).getNick();
				msg = cmds[2];
				for (size_t i = 3; i < cmds.size(); i++)
				{
					if (i != (size_t)i_pfds)
						msg += " " + cmds[i];
				}
				this->chan[chan_name].sendToAll(":" + nick + " PRIVMSG " + chan_name + " " + msg + "\r\n", this->clients, M_CLIENT(i_pfds).getFd());
			}
			else
			{
				nick = cmds[1];
				msg = cmds[2];
				for (size_t i = 3; i < cmds.size(); i++)
				{
					if (i != (size_t)i_pfds)
						msg += " " + cmds[i];
				}
				for (size_t i = 0; i < this->pfds.size(); i++)
				{
					if (M_CLIENT(i).getNick() == nick)
					{
						M_CLIENT(i).addBacklog(":" + M_CLIENT(i_pfds).getNick() + " PRIVMSG " + nick + " " + msg + "\r\n");
						return ;
					}
				}
				M_CLIENT(i_pfds).addBacklog("401 " + M_CLIENT(i_pfds).getNick() + " " + nick + " :No such nick/channel\r\n");
			}
		}
		else
			M_CLIENT(i_pfds).addBacklog("461 " + M_CLIENT(i_pfds).getNick() + " PRIVMSG :Not enough parameters\r\n");
	}
}

