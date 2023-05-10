/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:54:00 by wismith           #+#    #+#             */
/*   Updated: 2023/05/10 20:02:12 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "cinterface.hpp"
# include "../channels.hpp"

# define RPL_WELCOME std::string("001")

# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_NICKCOLLISION 436

namespace ft
{
	// irssi commands

	class cap : public ft::cinterface
	{
		public :
				cap (std::map<CLIENT_FD, CLIENT> &,
					std::vector<pollfd> &, std::string &);
				~cap ();

			void exec(int, const std::vector<std::string> &);
	};

	/* Usage: QUIT [ <Quit Message> ]
  	Forces the user to be removed from the server.  The <Quit Message>
  	may be up to 510 characters long and contain space characters.  Numeric
  	Replies:
  	None.
  	Examples:
  	QUIT :Gone to have lunch -or- QUIT :Gone to the beach */
	class quit : public ft::cinterface
	{
		public :
				quit (std::map<CLIENT_FD, CLIENT> &,
					std::vector<pollfd> &, std::string &);
				~quit ();

			void exec(int, const std::vector<std::string> &);
	};

	//! class pass : public ft::cinterface
	/* Usage: PASS <password>
  	Sets the connection password.  The password can and must be set before
  	any attempt to register the connection is made.  Currently no connection
  	is allowed to a server which has not registered.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED */

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
	class nick : public ft::cinterface
	{
		public :
					nick (std::map<CLIENT_FD, CLIENT> &,
						std::vector<pollfd> &, std::string &);
					~nick ();

			void	welcome(ft::client &c);
			void	exec(int, const std::vector<std::string> &);
	};

	//! class oper : public ft::cinterface
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

	/* Usage: JOIN <channel>{,<channel>} [<key>{,<key>}]
  	Join the comma separated list of channels, specifying the passwords,
  	if needed.  If a channel is password protected and no password is given,
  	the user is not joined to that channel.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_BANNEDFROMCHAN ERR_INVITEONLYCHAN
  	ERR_BADCHANNELKEY ERR_CHANNELISFULL ERR_BADCHANMASK
  	ERR_NOSUCHCHANNEL ERR_TOOMANYCHANNELS RPL_TOPIC
  	Examples:
  	JOIN #foobar fubar123 -or- JOIN &foo fubar123 */
	class join : public ft::cinterface
	{
		private :
			std::map<std::string, ft::channels>	&chan;
	
		public :
			join (std::map<CLIENT_FD, CLIENT> &,
					std::vector<pollfd> &, std::string &, 
					std::map<std::string, ft::channels>	&);
	
			~join ();

			void exec(int, const std::vector<std::string> &);
	};

	//! class part : public ft::cinterface
	/* Usage: PART <channel>{,<channel>}
  	Part the comma separated list of channels.  If no message is given,
  	part message is used.  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_NOSUCHCHANNEL ERR_NOTONCHANNEL
  	Examples:
  	PART #twilight_zone -or- PART #oz-ops,&group5 */

	//! class names : public ft::cinterface
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

	//! class kick : public ft::cinterface
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

	//! class invite : public ft::cinterface
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

	//! class topic : public ft::cinterface
	/* Usage: TOPIC <channel> [ <topic> ]
  	Allows the client to set the topic for a channel.  If <topic>
  	is an empty string, the topic for that channel is removed.  Numeric
  	Replies:
  	ERR_NEEDMOREPARAMS ERR_NOTONCHANNEL RPL_NOTOPIC
  	RPL_TOPIC
  	Examples:
  	TOPIC #test :New topic -or- TOPIC #test : */

	//! class mode : public ft::cinterface
	/* Usage: MODE <nickname> <modes>
  	Mode command is provided so that users may query and change the
  	characteristics of a user.  For more details on available modes
  	and their uses, see "Internet Relay Chat: Channel Management"
  	[RFC 2811].  Numeric Replies:
  	ERR_NEEDMOREPARAMS ERR_USERSDONTMATCH ERR_UMODEUNKNOWNFLAG
  	ERR_USERSDONTMATCH
  	Examples:
  	MODE WiZ -w -or- MODE Angel +i */
};

#endif