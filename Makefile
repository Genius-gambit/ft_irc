NAME = ft_irc

#* @note : no need to include .cpp extension in SRCS 	
#* 	@format : directory/file_name without .cpp
#*	@example : classDef/rawData

SRCS = main \

CXX = c++ -std=c++98

CXXFLAGS = -Wall -Wextra -Werror

OBJDIR = object

OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

#* @note : to include a new directory within srcs
#* 	please add @mkdir -p $(OBJDIR)/directory_name to below
#*	@example : @mkdir -p $(OBJDIR)/classDef
$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME) printProvided

$(NAME): printStart $(OBJS) printnl
	@printf "Generating Executable:\n"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJDIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

#* @brief : rules to print messages
printStart :
	@printf "\nConstructing new 'ft_irc' server objects:\n"
printnl :
	@echo ""
printProvided :
	@printf "\nServer 'ft_irc' provided\n"

.PHONY : all clean fclean re printStart printnl printProvided