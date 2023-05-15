#include "../../includes/commands/commands.hpp"

using namespace ft;

user::user(std::map<CLIENT_FD, CLIENT> &c, std::vector<pollfd> &p, std::string &pw) : ft::cinterface(c, p, pw) {}

user::~user() {}

void	user::exec(int i_pfds, const std::vector<std::string> &cmds)
{
	(void)i_pfds;
	if (cmds[0] == "USER")
	{
		if (cmds.size() == 6)
		{
			M_CLIENT(i_pfds).setHostname(cmds[3]);
			M_CLIENT(i_pfds).setRealname(cmds[4] + " " + cmds[5]);
			M_CLIENT(i_pfds).setStatus(VERIFIED);
			M_CLIENT(i_pfds).addBacklog("001 " + M_CLIENT(i_pfds).getNick() + " :Welcome " + M_CLIENT(i_pfds).getRealname() + "!\r\n");
			switch (random() % 7)
			{
			case 0:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- The only way to do great work is to love what you do. - Steve Jobs\r\n");
				break;
			case 1:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- If you can dream it, you can do it. - Walt Disney\r\n");
				break;
			case 2:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- The secret of getting ahead is getting started. - Mark Twain\r\n");
				break;
			case 3:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- If you can dream it, you can do it. - Walt Disney\r\n");
				break;
			case 4:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- Never give up. Today is hard, tomorrow will be worse, but the day after tomorrow will be sunshine. - Jack Ma\r\n");
				break;
			case 5:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- Life is hard. It's even harder when you're stupid. - John Wayne\r\n");
				break;
			case 6:
				M_CLIENT(i_pfds).addBacklog("375 " + M_CLIENT(i_pfds).getNick() + " :- You can't wait until life isn't hard anymore before you decide to be happy. - Nightbird\r\n");
				break;
			default:
				break;
			}
			M_CLIENT(i_pfds).addBacklog("376 " + M_CLIENT(i_pfds).getNick() + " :End of MOTD command\r\n");
		}
		else
			M_CLIENT(i_pfds).addBacklog("461 " + M_CLIENT(i_pfds).getNick() + " USER :Not enough parameters\r\n");
	}
}