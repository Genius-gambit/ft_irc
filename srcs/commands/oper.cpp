#include "../../includes/commands.hpp"

using namespace ft;

oper::oper(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) :
	ft::cinterface(c, p, pw) {}

oper::~oper() {}

void	oper::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	ft::client	&client = M_CLIENT(i_pfds);

	if (cmds.size() >= 3)
	{
		std::string oper_name = cmds[1];
		std::string password = cmds[2];
		if (oper_name == "admin" && password == "admin")
		{
			client.setOper(1);
			client.addBacklog("381 " + client.getNick() + " :You are now an IRC operator\r\n");
		}
		else
			client.addBacklog("464 " + client.getNick() + " :Password incorrect\r\n");
	}
	else
		reply(client, ERR_NEEDMOREPARAMS, " OPER :Not enough parameters");
}

