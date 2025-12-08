CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -I.

NAME = philo

SRCS = philo.c \
       parse.c \
       init.c \
       dinner.c \
       monitor.c \
       utils.c \
       cleanup.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Philosophers compiled!"

%.o: %.c philo.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "Objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable removed"

re: fclean all

.PHONY: all clean fclean re