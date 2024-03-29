# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 18:53:41 by lsouquie          #+#    #+#              #
#    Updated: 2023/09/01 18:54:07 by lsouquie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/main.c $(SRCDIR)/init_philo.c $(SRCDIR)/utils.c $(SRCDIR)/only_1.c \
	$(SRCDIR)/manage_death.c $(SRCDIR)/routine.c\

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 
NAME = philo

all: $(NAME)


$(NAME): $(OBJS)
		@echo "			-> Compiling $(NAME)..."
		@$(CC) $(OBJS) -o $@ -pthread $(CFLAGS)
		@echo "			-> Finished $(NAME)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

	
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)


fclean: clean
		@rm -f $(NAME)

norme:
		norminette $(SRCS)

re: fclean all

.PHONY: all lib clean fclean re norme
