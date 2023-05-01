/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:17:52 by wismith           #+#    #+#             */
/*   Updated: 2023/05/01 12:22:27 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/network.hpp"

using namespace ft;

network::network(std::string pw) : clients(), pfds(), password(pw) {}

network::~network() {}

void	network::quit(int i_pfds)
{
	if (pfds[i_pfds].revents & POLLOUT)
		M_CLIENT(i_pfds).Write(M_CLIENT(i_pfds).getNick() + " Quiting ircserv\n");
	clients.erase(pfds[i_pfds].fd);
	close (pfds[i_pfds].fd);
	pfds.erase(pfds.begin() + i_pfds);
}

void	network::pass(int i_pfds, const std::vector<std::string> &cmds)
{
	if (cmds[1] == this->password)
		M_CLIENT(i_pfds).setStatus(VERIFIED);
	// if ()
	// std::cout << "Client status verified\n";
}

void	network::nick(int i_pfds, const std::vector<std::string> &cmds)
{
	M_CLIENT(i_pfds).setNick(cmds[1]);
	std::cout << "Set client nickname to: " + cmds[1] << "\n";
}

void	network::selCmd(const std::vector<std::string> &cmds, int i_pfds)
{
	size_t	i = 0;
	std::map<int, std::string>	m_cmds;

	// irssi commands
	m_cmds[0] = "PASS";
	/* Usage: PASS <password>
  	Sets the connection password.  The password can and must be set before
  	any attempt to register the connection is made.  Currently no connection
  	is allowed to a server which has not registered.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED */
	m_cmds[1] = "NICK";
	/* Usage: NICK <nickname> [ <hopcount> ]
  	Allows a client to register a nickname with the server.  Numeric Replies:
  	ERR_NONICKNAMEGIVEN ERR_ERRONEUSNICKNAME ERR_NICKNAMEINUSE
  	ERR_NICKCOLLISION ERR_UNAVAILRESOURCE ERR_RESTRICTED
  	RPL_WELCOME RPL_YOUREOPER RPL_YOURESERVICE
  	Notes:
  	After registration, clients must use the NICK command to
  	change their nickname.  Numeric Replies:
  	ERR_NONICKNAMEGIVEN ERR_ERRONEUSNICKNAME ERR_NICKNAMEINUSE
  	ERR_NICKCOLLISION ERR_UNAVAILRESOURCE ERR_RESTRICTED
  	RPL_WELCOME RPL_YOUREOPER RPL_YOURESERVICE
  	Notes:
  	After registration, clients must use the NICK command to
  	change their nickname. */
	m_cmds[2] = "USER";
	/* Usage: USER <username> <hostname> <servername> <realname>
  	Initial user registration command.  The first parameter is the user's
  	username, the second one is hostname (optionally including the
  	servername), the third one is the name of the server which the client
  	is connecting to and the last parameter is the real name of the user.
  	The hostname for servers is passed as *.
  	<servername> parameter is used to determine the name of the other
  	server to which all data must be sent.  If it is omitted, the
  	current server is assumed as the target.  If any wildcard (*)
  	is present in the <servername> parameter, the client will be
  	disconnected from the server unless it has been started with
  	the allow-wildcard option.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED
  	Notes:
  	After registration, clients must use the NICK command to
  	change their nickname. */
	m_cmds[3] = "OPER";
	/* Usage: OPER <name> <password>
  	Used by a normal user to obtain operator privileges.  The combination
  	of <name> and <password> are compared with a list of oper
  	(password) entries in the configuration file and if a match is found,
  	the client is bootstrapped to operator status.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_NOOPERHOST ERR_PASSWDMISMATCH
  	RPL_YOUREOPER
  	Examples:
  	OPER foo bar - Try to become an operator using password "bar" and
  	username "foo". */
	m_cmds[4] = "QUIT";
	/* Usage: QUIT [ <Quit Message> ]
  	Forces the user to be removed from the server.  The <Quit Message>
  	may be up to 510 characters long and contain space characters.  Numeric
  	Replies:
  	None.
  	Examples:
  	QUIT :Gone to have lunch -or- QUIT :Gone to the beach */
	m_cmds[5] = "JOIN";
	/* Usage: JOIN <channel>{,<channel>} [<key>{,<key>}]
  	Join the comma separated list of channels, specifying the passwords,
  	if needed.  If a channel is password protected and no password is given,
  	the user is not joined to that channel.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_BANNEDFROMCHAN ERR_INVITEONLYCHAN
  	ERR_BADCHANNELKEY ERR_CHANNELISFULL ERR_BADCHANMASK
  	ERR_NOSUCHCHANNEL ERR_TOOMANYCHANNELS RPL_TOPIC
  	Examples:
  	JOIN #foobar fubar123 -or- JOIN &foo fubar123 */
	m_cmds[6] = "PART";
	/* Usage: PART <channel>{,<channel>}
  	Part the comma separated list of channels.  If no message is given,
  	part message is used.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_NOSUCHCHANNEL ERR_NOTONCHANNEL
  	Examples:
  	PART #twilight_zone -or- PART #oz-ops,&group5 */
	m_cmds[7] = "MODE";
	/* Usage: MODE <nickname> <modes>
  	Mode command is provided so that users may query and change the
  	characteristics of a user.  For more details on available modes
  	and their uses, see "Internet Relay Chat: Channel Management"
  	[RFC 2811].  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_USERSDONTMATCH ERR_UMODEUNKNOWNFLAG
  	ERR_USERSDONTMATCH
  	Examples:
  	MODE WiZ -w -or- MODE Angel +i */
	m_cmds[8] = "TOPIC";
	/* Usage: TOPIC <channel> [ <topic> ]
  	Allows the client to set the topic for a channel.  If <topic>
  	is an empty string, the topic for that channel is removed.  Numeric
  	Replies:
  	ERR_NEEDMOREPARAMS ERR_NOTONCHANNEL RPL_NOTOPIC
  	RPL_TOPIC
  	Examples:
  	TOPIC #test :New topic -or- TOPIC #test : */
	m_cmds[9] = "NAMES";
	/* Usage: NAMES [ <channel>{,<channel>} ]
  	By supplying a list of channel names or if no arguments are given,
  	a list of all channels and their occupants is returned.  If the
  	target server is joined to fewer than 5 channels, a list of all
  	channels the client is joined to will be returned.  The <channel>
  	parameter may also be a comma separated list of channels.  Numeric
  	Replies:
  	ERR_TOOMANYMATCHES ERR_NOSUCHSERVER RPL_NAMREPLY
  	RPL_ENDOFNAMES
  	Examples:
  	NAMES #twilight_zone,#42 - list visible users on #twilight_zone
  	and #42 -or- NAMES - list visible users for all channels */
	m_cmds[10] = "LIST";
	/* Usage: LIST [ <channel>{,<channel>} [ <server> ] ]
  	If no parameters are given, all visible channels and contents
  	are listed.  If a server parameter is given, the list will
  	be returned in a format similar to the reply for LINKS.  However,
  	only servers which are visible to the user issuing the command
  	are listed.  If a list of channels is given, then only those
  	channels are listed which are visible to the user issuing the
  	command.  Numeric Replies:
  	ERR_TOOMANYMATCHES ERR_NOSUCHSERVER RPL_LIST RPL_LISTEND
  	Examples:
  	LIST - list all channels -or- LIST #twilight_zone,#42 - list
  	only channels #twilight_zone and #42 -or- LIST #* -or- LIST
  	* - list all channels which the user can see */
	m_cmds[11] = "INVITE";
	/* Usage: INVITE <nickname> <channel>
  	Invites a user to a channel.  <channel> does not have to exist.
  	As with PRIVMSG, for a user to be able to invite other users to
  	a channel, they must have the operator status.  If the channel
  	is +i, the user must be invited by an operator of the channel.
  	Otherwise, any user may issue an INVITE command.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_NOSUCHNICK ERR_NOTONCHANNEL
  	ERR_USERONCHANNEL ERR_CHANOPRIVSNEEDED ERR_INVITEONLYCHAN
  	ERR_USERONCHANNEL ERR_NOCHANMODES ERR_BANNEDFROMCHAN
  	ERR_BADCHANNELKEY ERR_CHANNELISFULL ERR_BADCHANMASK
  	RPL_INVITING
  	Examples:
  	INVITE Wiz #Twilight_Zone -or- INVITE Wiz #Twilight_Zone */
	m_cmds[12] = "KICK";
	/* Usage: KICK <channel> <user> [<comment>]
  	Forcibly removes a user from a channel.  <comment> is an optional
  	message that is sent to the kicked user.  KICK can only be used
  	by a channel operator or the server administrator.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_NOSUCHCHANNEL ERR_BADCHANMASK
  	ERR_CHANOPRIVSNEEDED ERR_USERNOTINCHANNEL ERR_NOTONCHANNEL
  	ERR_USERONCHANNEL ERR_NOCHANMODES ERR_CHANOPRIVSNEEDED
  	ERR_NOTREGISTERED
  	Examples:
  	KICK &Melbourne Matthew -or- KICK #Finnish John :Speaking
  	English */ 
	for (; i < m_cmds.size() && m_cmds[i] != cmds[0]; i++)
		;
	switch (i){
		case 0:
			network::quit(i_pfds);
		break ;
		case 1:
			network::pass(i_pfds, cmds);
		break ;
		case 2:
			network::nick(i_pfds, cmds);
		break ;
		default:
			std::cout << "Command not found" << std::endl;
	};
}
