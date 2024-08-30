#---------------------------------------------------------#
CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

aGFLAGS	=	-g
#---------------------------------------------------------#
SRC_DIR		=	src

SRC			=	src/main.c src/path_and_cmd_extraction.c src/pipex.c src/prepare_context.c src/setup_redirection.c src/utils_check_files.c src/utils_cleanup.c src/utils_redirection.c 

OBJ_DIR		=	obj

OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#---------------------------------------------------------#
INC_DIR		=	includes

LIBFT_DIR	=	libft

LIBFT	=	libft.a
FT		=	ft

.PHONY: all lib clean fclean libclean re
#---------------------------------------------------------#
NAME	=	pipex

all:		$(NAME)

lib:		$(LIBFT_DIR)/$(LIBFT)

$(NAME):	$(OBJ) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIBFT_DIR) -l$(FT)

$(LIBFT_DIR)/$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -c $< -o $@ 

$(OBJ_DIR):
	mkdir -p $@

#---------------------------------------------------------#
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

fclean:		clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

libclean:
	rm -rf $(LIBFT_DIR)/$(OBJ_DIR)
	rm -rf $(LIBFT_DIR)/$(LIBFT)

re: fclean lib all

libre: libclean lib
#---------------------------------------------------------#
SRC_DIR_BONUS		=	src_bonus

SRC_BONUS			=	src_bonus/main.c src_bonus/path_and_cmd_extraction.c src_bonus/pipex.c src_bonus/prepare_context.c src_bonus/setup_redirection.c src_bonus/utils_check_files.c src_bonus/utils_cleanup.c src_bonus/utils_redirection.c 

OBJ_DIR_BONUS		=	obj_bonus

OBJ_BONUS			=	$(SRC_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)
#---------------------------------------------------------#
BONUS	=	pipex_bonus

bonus:		$(BONUS)

$(BONUS):	$(OBJ_BONUS) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ_BONUS) -o $@ -L$(LIBFT_DIR) -l$(FT)

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -c $< -o $@ 

$(OBJ_DIR_BONUS):
	mkdir -p $@
