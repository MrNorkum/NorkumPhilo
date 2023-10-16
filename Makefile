NAME = philo
NAME_2 = philo.a
CC = gcc
FLAG = -Wall -Wextra -Werror #-pthread -fsanitize=thread -g
CMPL = $(CC) $(FLAG)
RM = rm -rf
AR = ar rc
OBJDIR = OBJECTS
SRC =	./main.c			\
		./arg_conf.c		\
		./destroy.c			\
		./general_conf.c	\
		./utils.c			\
		./philo_life.c		\
		./philo.c

MAIN =	./main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(CMPL) -c $(SRC)
	@$(AR) $(NAME_2) $(OBJ)
	@$(CMPL) $(NAME_2) -o $(NAME)

c: clean
clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME_2)
	@$(RM) $(NAME)

re: fclean all

norm:
	norminette

.PHONY: all clean fclean re norm
