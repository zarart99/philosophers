NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/main.c \
		src/simulation.c \
		src/init.c \
		src/utils.c \
		src/parcer.c \
		src/philosopher_atcions.c

OBJS = $(SRCS:.c=.o)
INCLUDES = -I include 


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
