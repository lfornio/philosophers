NAME		= 	philo_bonus
SRCS		= 	philo_bonus.c \
				semaphore_and_waiter.c \
				philosophers_work.c \
				function_0.c \
				function_1.c

CC 			= 	gcc
FLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	philo_bonus.h
OBJS		=	$(SRCS:.c=.o)

.c.o: $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(OBJS) $(INCLUDE)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
