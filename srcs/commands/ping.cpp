#include "../../includes/commands.hpp"

using namespace ft;

ping::ping(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) : ft::cinterface(c, p, pw) {}

ping::~ping() {}

void	ping::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void)i_pfds;
	if (cmds[0] == "PING")
	{
		if (cmds.size() == 2)
			M_CLIENT(i_pfds).addBacklog("PONG " + cmds[1] + "\r\n");
		else
			M_CLIENT(i_pfds).addBacklog("461 " + M_CLIENT(i_pfds).getNick() + " PING :Not enough parameters\r\n");
	}
	// else if (cmds[0] == "PONG")
	// 	M_CLIENT(i_pfds).addBacklog("PING\r\n");
}