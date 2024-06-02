CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

GFLAGS	=	-g

DFLAGS	=	-fsanitize=address -fsanitize=undefined

###########################################################

NAME	=	pipex

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

LIB_DIR	=	./libft

LIB	=	$(LIB_DIR)/libft.a

###########################################################

all:		$(NAME)

lib:		$(LIB)

$(NAME):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIB_DIR) -lft
	

$(LIB):
	$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) -Iincludes -c $< -o $@

clean:
	rm -rf *.o

fclean:		clean
	rm -rf $(NAME) *dSYM 

libclean:
	rm -rf $(LIB_DIR)/*.o
	rm -rf $(LIB)

re: fclean all

PHONY: all lib clean fclean libclean re
