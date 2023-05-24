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
		std::string password = cmds[2];
		if (password == "admin")
		{
			client.setOper(1);
			client.addBacklog(RPL_YOUREOPER + " " + client.getNick() + " : You are now an IRC operator\r\n");
		}
		else
			client.addBacklog(ERR_PASSWDMISMATCH + client.getNick() + " : Password incorrect\r\n");
	}
	else
		reply(client, ERR_NEEDMOREPARAMS, " OPER : Not enough parameters");
}

