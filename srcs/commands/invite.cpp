#include "../../includes/commands.hpp"

using namespace ft;

invite::invite(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels *>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

invite::~invite() {}

void	invite::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void) chan;
	std::string chan_name = cmds[2];
	std::string invitee_nick = cmds[1];
	int invitee_fd;
	find_fd(invitee_nick, invitee_fd);
	std::string inviter_nick = M_CLIENT(i_pfds).getNick();
	ft::client	&client = M_CLIENT(i_pfds);
	if (cmds.size() < 3)
    {
        this->reply(M_CLIENT(i_pfds), ERR_NEEDMOREPARAMS, "INVITE");
        return ;
    }
    if (cmds[2][0] == '#')
    {
		if (this->chan.find(cmds[2]) == this->chan.end())
		{
			this->reply(M_CLIENT(i_pfds), ERR_NOSUCHCHANNEL, cmds[2]);
			return ;
		}
		this->clients[invitee_fd].addBacklog(":" + inviter_nick + " INVITE " + invitee_nick + " :" + chan_name + "\r\n");
		this->reply(client, RPL_INVITING, invitee_nick + " " + chan_name);
        return ;
    }
	else
	{
		this->reply(M_CLIENT(i_pfds), ERR_NOSUCHCHANNEL, cmds[2]);
		return ;
	}
}