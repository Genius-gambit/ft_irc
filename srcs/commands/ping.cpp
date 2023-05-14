#include "../../includes/commands/commands.hpp"

using namespace ft;

ping::ping(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) : ft::cinterface(c, p, pw) {}

ping::~ping() {}

void	ping::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void)i_pfds;
	if (cmds[0] == "PING")
		M_CLIENT(i_pfds).addBacklog("PONG\r\n");
	// else if (cmds[0] == "PONG")
	// 	M_CLIENT(i_pfds).addBacklog("PING\r\n");
}