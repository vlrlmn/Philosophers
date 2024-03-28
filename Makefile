NAME	=	philo

FILES	=	main.c \
			validate_agrs.c \
			utils.c \
			routine.c \
			init_philo.c \
			init_forks.c \

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra  -I ./include

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