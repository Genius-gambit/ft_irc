# FT_IRC

## Work Logs :notebook_with_decorative_cover:(April 7 2023~)
1.	***MAK:***	Created a Makefile.
	1. Channels Initialised.
	2. Unique channels implemented.
	3. Unique clients implemented in particular channels.4
	4. Parsing handled for duplicate nicknames.
	5. Unique nicknames have been implemented from nick.cpp.
	6. Added a public memebr function in nick class.
	7. Added a new variable in client class markForKick boolean value.
	8. Added setChannelName(const std::string &) to set the name of the channel.
	9. Added setChannelPass(const std::string &) to set the password of the channel.
	10. Added getChannelName() to fetch the name of the channel.
	11. Added get_pass() to fetch the password of the channel.
	12. Edited kick_client(int fd) to kick_client(std::string &, bool &);
	13. Boolean value which indicates if the client has quit the server / kicked from the particular channel.
	14. Edited kick.cpp kick_client function.
	15. Implemented kick function to check if the client is the channel operator to kick another client.
	16. Before kicking any client, it checks if the client is the member of the channel or not.
	17. After kicking any client it sends a message to all the clients in the channel that the client has been kicked by an operator.
	18. Implemented parsing of file transfer.
	19. Created a class with name dcc.
	20. Implemented file transfer with nc.
	21. Improved FIle transfer command.
2. ***WJS*** 
   1. Implemented Makefile
   2. Implemented rule 'client' within Makefile to pull irssi client version 1.2.3 from Docker Hub
   3. Made every Makefile call to rule 'client' generate a unique instance of irssi with unique names allowing for multiple containers to run simultaneously
   4. Implemented class error object
   5. Handled invalid port as argument
   6. Implemented a signal handler
   7. Implemented SetSocket(Interface) for ftServer library
   8. Implemented Listener class for ftServer library
   9. Implemented non-blocking using function fcntl within Listener
   10. Added socket options method to Listener class that incorporated setsockopt
   11. Developed the Server Architecture
   12. Added network parent class
   13. Implemented a Select Command method within network
   14. Added a parser grandparent to server class, used to parse incoming commands
   15. Added a command interface class that stores all relevant values' references, and takes their references in constructors
   16. Tested resulting program using valgrind, and fixed memory leaks
   17. Helped format messages according to irssi 
   18. Created a simple Irc bot that is seperate from the main program, and connects like a regular user.
   19. Added a create channel and join feature within IrcBot
   
   ## Authentication Part
   20. ~~Password needs to be matched.~~
   21. ~~Nickname parsing if there are same nicknames.~~

## Objectives

#### MAK
1. ~~Initialise Channels.~~
2. ~~Implement Unique channels in the server.~~
3. ~~Implement Unique clients in particular channels.~~
4. ~~Kick Client with the nickname along with sending a message to all the clients in a particular channel.~~
5. ~~Authentication Part for the clients.~~
6. ~~Parsing for nickname.~~
7. ~~Quit command needs to be implemented which leads to kick clients from their respective channelsand also send a message.~~
8. ~~Implementation of channels along with passwords.~~
9. ~~Implementation of granting access to clients who give correct password to the channels for joining in.~~
10. ~~Implement File transfer.~~

#### WJS
1. ~~Implement server~~
