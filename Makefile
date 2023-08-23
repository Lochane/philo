CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/main.c $(SRCDIR)/init_philo.c $(SRCDIR)/utils.c \
	$(SRCDIR)/routine.c\

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 

NAME = philo

all: $(NAME)


$(NAME): $(OBJS)
		@echo "			-> Compiling $(NAME)..."
		@$(CC) $(OBJS) -o $@ -pthread -g
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