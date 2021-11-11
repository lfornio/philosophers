NAME		= 	philo
SRCS		= 	philo.c \
				function_0.c \
				function_1.c \
				treads_work.c \
				waiter_work.c
CC 			= 	gcc
FLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	philo.h
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
