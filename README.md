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
   1. Created main.cpp
   2. Implemented class error object
   3. Handled invalid port as argument
   4. Implemented a signal handler
   5. Implemented SetSocket(Interface) and Binder class for ftServer library
   6. Implemented Listener and Reader class, and merged Binder into Listener for ftServer library
   7. Implemented non-blocking using function fcntl within Listener
   8. Added socket options method to Listener class that incorporated setsockopt
   
   ## Authentication Part
   1. ~~Password needs to be matched.~~
   2. ~~Nickname parsing if there are same nicknames.~~

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
1. Implement server
