NAME = ircserv
BONUS = bot/IrcBot

SERVDIR = ftServerUtils
SERVARCH = $(SERVDIR)/ServerUtils.a

#* @note : no need to include .cpp extension in SRCS
#* 	@format : directory/file_name without .cpp
#*	@example : classDef/rawData

SRCS = main \
	client \
	server \
	network \
	parser \
	channels \
	welcome \
	commands/cinterface \
	commands/dcc \
	commands/quit \
	commands/cap \
	commands/join \
	commands/kick \
	commands/nick \
	commands/pass \
	commands/ping \
	commands/user \
	commands/privmsg \
	commands/mode \
	commands/topic \
	commands/invite \
	commands/part \
	commands/list \

BONUS_SRCS = main \
			bot \
			parser \

OS:= ${shell uname}

ifeq ($(shell uname -s), Darwin)
	def = -D OSX
endif
ifeq ($(shell uname -s), Linux)
	def = -D LINUX
endif

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

OBJDIR = object

B_OBJDIR = b_object

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

B_OBJ = $(addprefix $(B_OBJDIR)/, $(addsuffix .o, $(BONUS_SRCS)))

#* @note : to include a new directory within srcs
#* 	please add @mkdir -p $(OBJDIR)/directory_name to below
#*	@example : @mkdir -p $(OBJDIR)/classDef
$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/commands
	@printf "\033[A\033[2K\r"
	$(CXX) $(CXXFLAGS) $(def) -c $< -o $@

$(B_OBJDIR)/%.o : bot/srcs/%.cpp
	@mkdir -p $(B_OBJDIR)
	@printf "\033[A\033[2K\r"
	$(CXX) $(CXXFLAGS) $(def) -c $< -o $@

all : $(NAME) printProvided
	@clear

	@tput setaf 1
	@printf ".__\n"                                          
	@printf "|__|______   ____   ______ ______________  __\n"
	@printf "|  \_  __ \_/ ___\ /  ___// __ \_  __ \  \/ /\n"
	@printf "|  ||  | \/\  \___ \___  \\  ___/|  | \/\   / \n"
	@printf "|__||__|    \___  >____  >\___  >__|    \_/  \n"
	@printf "                \/     \/     \/             \n\n"
	@tput init

	@printf "Execute server as follows:\n\n"
	@printf "\t./ircserv <"

	@tput setaf 1
	@printf "port"
	@tput init
	
	@printf "> <"

	@tput setaf 1
	@printf "password"
	@tput init

	@printf ">\n\n"

# @printf "<port> <server password>\n\n"

	@printf "Connect client / bot with host's IPv4:\n\n"

	@printf "Your host's IPv4 is: "
	@tput setaf 2
	@ipconfig getifaddr en0
	@tput init
	@printf "\n"

	@printf "If running a bot or client on same host use "
	@printf "localhost : "

	@tput setaf 2
	@printf "127.0.0.1\n"
	@tput init

$(NAME): utils printStart $(OBJS) printnl
	@printf "Generating Executable:\n"
	$(CXX) $(CXXFLAGS) $(OBJS) $(SERVARCH) $(def) -o $(NAME)

bonus : utils $(B_OBJ)
	@printf "Generating Bonus Executable:\n"
	$(CXX) $(CXXFLAGS) $(B_OBJ) $(SERVARCH) -o $(BONUS)

utils :
	@make -C $(SERVDIR)

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(B_OBJDIR)
	@make clean -C $(SERVDIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)
	@make fclean -C $(SERVDIR)
	@rm -rf server.log

re: fclean all

#* @brief vars randomize the clients by date
LOGFILE = $(shell date)
CLIENTTIME = $(addsuffix .$(LOGFILE), client)
CLIENT = $(shell echo $(CLIENTTIME) | tr A-Z a-z | tr -d ' ' | tr -d ':' | tr -d '+' | tr -d '-')
CLIENT_VERSION = irssi:1.2.3

#* @client
#* @brief : make client will build and execute a client
#*	@note : quit client by typing "/quit" on interface
#* ipconfig getifaddr en0
#*
client:
	docker run -it --name $(CLIENT) -e TERM -u $(id -u):$(id -g) \
	--log-driver=none \
	   -v ${HOME}/.irssi:/home/user/.irssi:ro \
	$(CLIENT_VERSION)
	docker rm -f $(CLIENT)

#* @brief : make rm_client will remove the client and delete the image
rm_client:
	docker rmi $(CLIENT_VERSION)

#* @brief : rules to print messages
printStart :
	@printf "\nConstructing new 'ft_irc' server objects:\n\n"

printnl :
	@echo ""

printProvided :
	@printf "\nServer 'ircserv' provided\n"

.PHONY : all clean fclean re printStart printnl printProvided

# run 42 container in interactive mode: docker exec -it 42-valgrind zsh