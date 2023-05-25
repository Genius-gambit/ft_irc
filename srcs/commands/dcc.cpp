#include "../../includes/commands.hpp"

using namespace ft;

dcc::dcc( std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw ) :
	ft::cinterface( c, p, pw ) {}

dcc::~dcc() {}

std::string	getClientDir()
{
	char	s[100];
	std::string	cwd;
	std::string	_dir = CLIENTDIR;
	chdir("/");
	_dir = _dir.append("/");
	_dir = _dir.append(getenv("USER"));
	chdir(_dir.c_str());
	cwd = getcwd(s, 100);
	return (cwd);
}

void	dcc::exec( int i_pfds, const std::vector<std::string> &cmds )
{
	if (cmds.size() == 4)
	{
		std::string	receivingFile;
		ft::client	nick;
		std::size_t	it;
		std::cout << cmds[2] << std::endl;
		for (it = 0; it < this->pfds.size(); it++)
		{
			if (M_CLIENT(it).getNick() == cmds[2])
			{
				nick = M_CLIENT(it);
				break;
			}
		}
		if (it != this->pfds.size())
		{
			if (M_CLIENT(i_pfds).getFd() == nick.getFd())
			{
				M_CLIENT(i_pfds).addBacklog("That's Funny!\r\n");
				return ;
			}
			std::string	filename = getClientDir();
			filename += cmds[3];
			std::string	tmp = filename.substr(0, filename.find_last_of('/') + 1);
			chdir("/");
			chdir(tmp.c_str());
			filename = filename.substr(filename.find_last_of('/') + 1, filename.length());
			receivingFile = filename;
			std::ifstream	file(filename.c_str());
			if (file.good())
			{
				std::map<int, int>	tmp;
				tmp[M_CLIENT(i_pfds).getFd()] = nick.getFd();
				std::cout << tmp[M_CLIENT(i_pfds).getFd()] << std::endl;
				if (cmds[1] == "SEND")
				{
					if (this->_sender[tmp] == true)
						M_CLIENT(i_pfds).addBacklog("You have already sent a file request!\r\n");
					else
					{
						this->_fileSending[tmp] = cmds[3];
						for (std::string line; getline(file, line);)
						{
							this->_data[tmp] = this->_data[tmp].append(line);
							// this->_data[tmp] = this->_data[tmp].append("\r\n");
						}
						this->_data[tmp] = this->_data[tmp].substr(0, this->_data[tmp].length() - 1);
					}
					this->_sender[tmp] = true;
					std::cout << tmp[M_CLIENT(i_pfds).getFd()] << std::endl;
				}
				else if (cmds[1] == "GET")
				{
					std::cout << tmp[M_CLIENT(i_pfds).getFd()] << std::endl;
					std::map<int, int>	getPair;
					getPair[nick.getFd()] = M_CLIENT(i_pfds).getFd();
					tmp = getPair;
					if (this->_sender[tmp] == true && _fileSending[tmp] == cmds[3])
					{
						std::string	rootDir = getClientDir();
						std::ofstream	outFile(receivingFile.c_str());
						if (outFile.good())
						{
							outFile << this->_data[tmp];
						}
						outFile.close();
						std::cout << "Successful" << std::endl;
						this->_sender[tmp] = false; 
						_fileSending[tmp] = "";
					}
					else
						M_CLIENT(i_pfds).addBacklog("You don't have any file requests!\r\n");
				}
				file.close();
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