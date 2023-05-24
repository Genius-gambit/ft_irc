#include "../../includes/commands.hpp"

using namespace ft;

mode::mode(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw,
	std::map<std::string, ft::channels *>	&chans) :
	ft::cinterface(c, p, pw), chan(chans) {}

mode::~mode() {}

void	mode::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	std::string	chan_name;
	std::string	mode;
	std::string	chan_mode;

	if (cmds[1][0] != '#')
		return ;
	if (cmds.size() < 2)
	{
		this->reply(M_CLIENT(i_pfds), ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	chan_name = cmds[1];
	if (this->chan.find(chan_name) == this->chan.end())
	{
		this->reply(M_CLIENT(i_pfds), ERR_NOSUCHCHANNEL, chan_name);
		return ;
	}
	if (this->chan[chan_name]->getOp(M_CLIENT(i_pfds).getFd()) == false)
	{
		this->reply(M_CLIENT(i_pfds), ERR_NOPRIVILEGES, chan_name + " :You're not channel operator");
		return ;
	}
	if (cmds.size() == 2)
	{
		chan_mode = this->chan[chan_name]->get_mode();
		this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + " " + chan_mode);
		return ;
	}
	mode = cmds[2];
	if (mode[0] == '+')
	{
		if (mode.find('o') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +o " + M_CLIENT(i_pfds).getNick() + "\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_UMODEIS, "+o " + M_CLIENT(i_pfds).getNick());
		}
		if (mode.find('i') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +i\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + "+i");
		}
		if (mode.find('t') != mode.npos)
		{
			if (this->chan[chan_name]->get_is_topic() == true)
				return ;
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +t\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + " +t");
		}
		if (cmds.size() > 3)
		{
			if (mode.find('l') != mode.npos)
			{
				M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +l " + mode.substr(mode.find('l') + 1, mode.length()) + "\r\n");
				this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + " +l " + mode.substr(mode.find('l') + 1, mode.length()));
			}
			if (mode.find('k') != mode.npos)
			{
				M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +k " + cmds[3] + "\r\n");
				this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + " +k " + cmds[3]);
			}
			this->chan[chan_name]->set_mode(mode + cmds[3]);
		}
		else
			this->chan[chan_name]->set_mode(mode);
		// this->chan[chan_name]->sendToAll(":" + M_CLIENT(i_pfds).getNick() + " MODE " + chan_name + " " + mode + "\r\n", this->clients, M_CLIENT(i_pfds).getFd());
	}
	else if (mode[0] == '-')
	{
		if (mode.find('o') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -o " + M_CLIENT(i_pfds).getNick() + "\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_UMODEIS, "-o " + M_CLIENT(i_pfds).getNick());
		}
		if (mode.find('i') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -i\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + "-i");
		}
		if (mode.find('t') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -t\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + "-t");
		}
		if (mode.find('l') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -l\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + "-l");
		}
		if (mode.find('k') != mode.npos)
		{
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -k\r\n");
			this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + "-k");
		}
		this->chan[chan_name]->set_mode(mode);
		// this->chan[chan_name]->sendToAll(":" + M_CLIENT(i_pfds).getNick() + " MODE " + chan_name + " " + mode + "\r\n", this->clients, M_CLIENT(i_pfds).getFd());
	}
}