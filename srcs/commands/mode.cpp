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
	if (cmds.size() == 2)
	{
		chan_mode = this->chan[chan_name]->get_mode();
		this->reply(M_CLIENT(i_pfds), RPL_CHANNELMODEIS, chan_name + " " + chan_mode);
		return ;
	}
	if (cmds[2].length() == 1)
	{
		this->reply(M_CLIENT(i_pfds), ERR_NEEDMOREPARAMS, "MODE");
		return ;
	}
	if (this->chan[chan_name]->getOp(M_CLIENT(i_pfds).getFd()) == false)
	{
		this->reply(M_CLIENT(i_pfds), ERR_CHANOPRIVSNEEDED, chan_name + " :You're not channel operator");
		return ;
	}
	if (cmds[2][0] != '+' && cmds[2][0] != '-')
	{
		this->reply(M_CLIENT(i_pfds), ERR_UNKNOWNMODE, cmds[2] + " :is unknown mode to me");
		return ;
	}
	mode = cmds[2];
	if (mode[0] == '+')
	{
		if (mode.find('o') != mode.npos)
			M_CLIENT(i_pfds).addBacklog("MODE " 
				+ chan_name + " +o " + M_CLIENT(i_pfds).getNick() + "\r\n");
		if (mode.find('i') != mode.npos)
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +i\r\n");
		if (mode.find('t') != mode.npos)
		{
			if (this->chan[chan_name]->get_is_topic() == true)
				return ;
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +t\r\n");
		}
		if (cmds.size() > 3)
		{
			if (mode.find('l') != mode.npos)
				M_CLIENT(i_pfds).addBacklog("MODE " 
					+ chan_name + " +l " + mode.substr(mode.find('l') + 1, mode.length()) + "\r\n");
			if (mode.find('k') != mode.npos)
				M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " +k " + cmds[3] + "\r\n");
			this->chan[chan_name]->set_mode(mode + cmds[3]);
		}
		else
			this->chan[chan_name]->set_mode(mode);
	}
	else if (mode[0] == '-')
	{
		if (mode.find('o') != mode.npos)
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " -o " + M_CLIENT(i_pfds).getNick() + "\r\n");
		if (mode.find('i') != mode.npos || mode.find('t') != mode.npos 
			|| mode.find('l') != mode.npos || mode.find('k') != mode.npos)
			M_CLIENT(i_pfds).addBacklog("MODE " + chan_name + " " + mode + "\r\n");
		this->chan[chan_name]->set_mode(mode);
	}
}