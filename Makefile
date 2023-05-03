NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC =	init.c\
		philo.c\
		utils.c\
		
OBJS = $(SRC:.c=.o) 

all : $(NAME)

$(NAME) : $(OBJS)	
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all