NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread #-fsanitize=address

G = "\033[32m"
Y = "\033[33m"
R = "\033[31m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

SRCS = main.c exit.c init.c threads.c acts.c monitor.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@echo $(Y)Compiling	[$<]$(X)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf $(UP)$(CUT)

$(NAME): $(OBJS)
	@echo $(Y)"Compiling	" [$(SRCS)]$(X)
	@echo $(G)"Created		" [$(SRCS)]$(X)
	@echo $(Y)"Compiling	" [$(NAME)]$(X)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo $(G)"Created		" [$(NAME)]$(X)

clean:
	@rm -f $(OBJS)
	@echo $(R)"Removed		" [$(OBJS)]$(X)

fclean: clean
	@rm -f $(NAME)
	@echo $(R)"Removed		" [$(NAME)]$(X)

re: fclean all

.PHONY: all clean fclean re
