NAME	=	philo

FILES	=	main.c \
			validate_agrs.c \
			utils.c \
			routine.c \
			init_philo.c \
			errors.c \
			get_time.c \
			write_mutex.c \
			synchro.c \
			getters_setters.c \
			monitor.c \
			thread_functions.c \

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra --debug -I ./include -fsanitize=thread

LINKS	=	-pthread

OBJS	=	$(FILES:.c=.o)

RM		=	/bin/rm

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LINKS) -o $(NAME)

clean:
	$(RM) -f $(OBJS)

fclean:	clean
	$(RM) -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re