# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 23:57:52 by wismith           #+#    #+#              #
#    Updated: 2023/04/14 02:25:10 by wismith          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ServerSide.a

CXX = c++

CPPFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS = SetSocket \
	Binder \

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))

$(OBJDIR)/%.o : srcs/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re