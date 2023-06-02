CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/test.c\

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 

NAME = philo

all: $(NAME)


$(NAME): $(OBJS)
		@echo "			-> Compiling $(NAME)..."
		@$(CC) $(OBJS) -o $@
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