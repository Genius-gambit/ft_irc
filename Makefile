NAME = ft_irc

SERVDIR = ftServer

SERVARCH = $(SERVDIR)/ServerUtils.a

#* @note : no need to include .cpp extension in SRCS 	
#* 	@format : directory/file_name without .cpp
#*	@example : classDef/rawData

ClIENT = irssi_client

SRCS = main \
	signals \

CXX = c++ -std=c++98

CXXFLAGS = -Wall -Wextra -Werror

OBJDIR = object

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

#* @note : to include a new directory within srcs
#* 	please add @mkdir -p $(OBJDIR)/directory_name to below
#*	@example : @mkdir -p $(OBJDIR)/classDef
$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/classDef
	@printf "\033[A\033[2K\r"
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME) printProvided

$(NAME): utils printStart $(OBJS) printnl
	@printf "Generating Executable:\n"
	$(CXX) $(CXXFLAGS) $(OBJS) $(SERVARCH) -o $(NAME)

utils :
	@make -C $(SERVDIR)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(SERVDIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(SERVDIR)

re: fclean all

#* @client
#* @brief : make client will build and execute a client
#*	@note : quit client by typing "/quit" on interface
client:
	docker run -it --name $(ClIENT) -e TERM -u $(id -u):$(id -g) \
	--log-driver=none \
    -v ${HOME}/.irssi:/home/user/.irssi:ro \
    irssi

#* @brief : make rm_client will remove the client and delete the image
rm_client:
	docker rm -f $(ClIENT)
	docker rmi irssi

#* @brief : rules to print messages
printStart :
	@printf "\nConstructing new 'ft_irc' server objects:\n\n"
printnl :
	@echo ""
printProvided :
	@printf "\nServer 'ft_irc' provided\n"

.PHONY : all clean fclean re printStart printnl printProvided