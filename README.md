# FT_IRC

## Work Logs :notebook_with_decorative_cover:(April 7 2023~)
1.	***MAK:***	Created a Makefile.
	1. Channels.
	2. Implementation of all unique clients into the channels.
2. ***WJS*** 
   1. Created main.cpp
   2. Implemented class error object
   3. Handled invalid port as argument
   4. Implemented a signal handler
   5. Implemented SetSocket(Interface) and Binder class for ftServer library
   6. Implemented Listener and Reader class, and merged Binder into Listener for ftServer library
   7. Implemented non-blocking using function fcntl within Listener
   8. Added socket options method to Listener class that incorporated setsockopt

## Objectives

#### MAK
1. Create config and parse such files.
2. Update Authentication for all the clients before joining the channels.

#### WJS
1. Implement server
