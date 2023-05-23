#include "../../includes/commands.hpp"

using namespace ft;

dcc::dcc( std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw ) :
	ft::cinterface( c, p, pw ) {}

dcc::~dcc() {}

void	dcc::exec( int i_pfds, const std::vector<std::string> &cmds )
{
	std::cout << cmds[1] << std::endl;
	std::cout << cmds[2] << std::endl;
	std::cout << cmds[3] << std::endl;
	if (cmds.size() == 4)
	{
		ft::client	nick;
		std::size_t	it;
		// std::map<int, ft::client>::iterator it;
		for (it = 0; it <= this->clients.size(); it++)
		{
			ft::client	tmp = M_CLIENT(it);
			if (tmp.getNick() == cmds[2])
			{
				nick = tmp;
				break;
			}
		}
		if (it != this->clients.size())
		{
			std::string	filename = "";

			filename += cmds[2];
			FILE	*file = fopen(filename.c_str(), "r");
			if (file)
			{
				fclose(file);
				/**************************************/
				/***************Execution*************/
				std::map<int, int>	tmp;
				tmp[M_CLIENT(i_pfds).getFd()] = nick.getFd();
				if (cmds[1] == "SEND")
				{
					if (this->_sender[tmp] == true)
						M_CLIENT(i_pfds).addBacklog("You have already sent a file request!\r\n");
					this->_sender[tmp] = true;
				}
				else if (cmds[1] == "GET")
				{
					if (this->_sender[tmp] == true)
					{
						M_CLIENT(i_pfds).addBacklog("File received!\r\n");
						nick.addBacklog("File sent successfully!\r\n");
						this->_sender[tmp] = false;
					}
					else
						M_CLIENT(i_pfds).addBacklog("You don't have any file requests!\r\n");
				}
				return ;
			}
			else
				M_CLIENT(i_pfds).addBacklog("File does not exist\r\n");
		}
		else
			M_CLIENT(i_pfds).addBacklog("Client does not exist\r\n");
	}
	else
		M_CLIENT(i_pfds).addBacklog("Expected 4 arguments\r\n");
}