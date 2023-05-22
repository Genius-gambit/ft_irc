#include "../../includes/commands.hpp"

using namespace ft;

names::names(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw, std::map<std::string, ft::channels *>	&chans) :
	cinterface(c, p, pw), chan(chans) {}

names::~names() {}

void	names::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	ft::client	&client = M_CLIENT(i_pfds);
	std::map<std::string, ft::channels *>::iterator	chan_it;
	std::map<CLIENT_FD, CLIENT>::iterator	client_it;
	std::string	chan_name;
	std::string	users;

	if (cmds.size() == 1)
	{
		client.addBacklog(ERR_NEEDMOREPARAMS + client.getNick() + " NAMES :Not enough parameters\r\n");
		return ;
	}
	chan_name = cmds[1];
	chan_it = this->chan.find(chan_name);
	if (chan_it == this->chan.end())
	{
		client.addBacklog(ERR_NOSUCHCHANNEL + client.getNick() + " " + chan_name + " :No such channel\r\n");
		return ;
	}
	users = chan_it->second->get_users();
	client.addBacklog(RPL_NAMREPLY + client.getNick() + " = " + chan_name + " :" + users + "\r\n");
	client.addBacklog(RPL_ENDOFNAMES + client.getNick() + " " + chan_name + " :End of NAMES list\r\n");
}
