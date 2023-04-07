NAME = ft_irc

#* @note : no need to include .cpp extension in SRCS 	
#* 	@format : directory/file_name without .cpp
SRCS = main \
	classDef/rawData \

CXX = c++ -std=c++98

CXXFLAGS = -Wall -Wextra -Werror

OBJDIR = object

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

#* @note : to include a new directory within srcs
#* 	please add @mkdir -p $(OBJDIR)/directory_name to below
$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/classDef
	$(CXX) $(CXXFLAGS) -c $< -o $@
	tput setaf 2; printf " . "

all : $(NAME) printProvided

$(NAME): printStart $(OBJS) printnl
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJDIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

#* @brief : rules to print messages
printStart :
	tput setaf 7; printf "\nConstructing new webserv "
printnl :
	tput setaf 7; echo ""
printProvided :
	printf "\nServer 'webserv' provided\n"

.PHONY : all clean fclean re printStart printnl printProvided