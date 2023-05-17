#include "../../includes/commands.hpp"

using namespace ft;

user::user(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) : ft::cinterface(c, p, pw) {}

user::~user() {}

void	user::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	ft::client	&client = M_CLIENT(i_pfds);

	if (client.getStatus() == VERIFIED)
		return (this->reply(client, ERR_ALREADYREGISTRED, ":Client already registered"));
	if (cmds.size() >= 4)
	{
		client.setHostname(cmds[3]);
		client.setRealname(cmds[4] + " " + cmds[5]);
	}
	else
		this->reply(client, ERR_NEEDMOREPARAMS, ":Not enough parameters");
}