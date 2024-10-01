FLAGS = -Wall -Wextra -Werror 

NAME = philo

SRC = philo.c \
	  utils1.c \
	  data_init.c \
	  getters_setters.c\
	  sync.c \
	  utils2.c \
	  philo_routine.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
