# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 23:57:52 by wismith           #+#    #+#              #
#    Updated: 2023/04/18 22:54:50 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ServerUtils.a

CXX = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = SetSocket \
	error \
	Listener \
	Reader \

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	@printf "\033[A\033[2K\r"
	@printf "\x1B[32m\tGenerating ... \x1B[0m"
	$(CXX) $(CPPFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : printHead $(OBJ)
	@printf "\033[A\033[2K\r"
	@printf "\x1B[32m\tGenerating ... \x1B[0m"
	ar -rc $(NAME) $(OBJ)
	@printf "\033[A\033[2K\r"
	@printf "\x1B[32m\tArchived ServerUtils.a\n \x1B[0m"

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

printHead :
	@printf "\x1B[0m _______________________________________________________\n"
	@printf "\x1B[0m|                                                       |\n"
	@printf "\x1B[0m|     \x1B[32m\"THE MOMENT WE STOP LEARNING IS THE MOMENT WE \x1B[0m    |\n"
	@printf "\x1B[0m|    \x1B[32mSTAGNATE, AND THOUGH LEARNING IN THE REAL WORLD\x1B[0m    |\n"
	@printf "\x1B[0m|     \x1B[32mIS SELDOM UNACCOMPANIED BY HARDSHIP IT'S ALSO\x1B[0m     |\n"
	@printf "\x1B[0m|          \x1B[32mAN EXPERIENCE.\"\x1B[0m - Willem J. Smith            |\n"
	@printf "\x1B[0m|_______________________________________________________|\n"
	@printf "\x1B[0m\n\n"

.PHONY : all clean fclean re printHead