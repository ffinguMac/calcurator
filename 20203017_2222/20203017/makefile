CC = gcc
NAME = calculator
SOURCES = main.c calc.c queue.c stack.c
OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)	-lm

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re : fclean all
.PHONY : clean fclean re