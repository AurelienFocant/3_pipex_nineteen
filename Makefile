CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror 

GFLAGS	=	-g

DFLAGS	=	-fsanitize=address -fsanitize=undefined

###########################################################

NAME	=	pipex

SRC_DIR	=	./src

SRC	=	$(wildcard $(SRC_DIR)/*.c)

OBJ_DIR	=	./obj

OBJ	=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#OBJ	=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIB_DIR	=	./libft

LIB	=	$(LIB_DIR)/libft.a

.PHONY: all lib clean fclean libclean re

###########################################################

all:		$(NAME)

lib:		$(LIB)

$(NAME):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIB_DIR) -lft


$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) -Iincludes -c $< -o $@

$(OBJ_DIR):
	mkdir -p obj

clean:
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -rf $(NAME) *dSYM 

libclean:
	rm -rf $(LIB_DIR)/*.o
	rm -rf $(LIB)

re: fclean all
