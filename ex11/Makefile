CC					:= gcc

RM					:= rm -rf

LDFLAGS			+= -Llib

CFLAGS			+= -Iinclude -g

SRCS				:= $(wildcard src/*.c)

OBJS				:= $(SRCS:.c=.o)

NAME				:= myshell_test

all:				$(NAME)

$(NAME):		$(OBJS)
						$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
						$(RM) $(OBJS)

fclean: 		clean
						$(RM) $(NAME)

re: 				fclean all

test:				re
						@(./$(NAME))

debug:			re
						valgrind -v --leak-check=full --track-origins=yes ./$(NAME)
