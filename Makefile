#---------------------------------------------------------#
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
GFLAGS			=	-g3
LNK				=	$(shell ld -v 2>&1 | grep --quiet GNU && which lld >/dev/null && echo lld)
ifeq ($(LNK), lld)
	LNKFLAGS	=	-fuse-ld=lld
endif

COMPILER		=	$(CC) $(CFLAGS) $(GFLAGS)
LINKER			=	$(CC) $(LNKFLAGS) $(CFLAGS) $(GFLAGS)
#---------------------------------------------------------#
SRC_DIR			=	src
SRC				=	src/main.c src/path_and_cmd_extraction.c src/parsing_cmd.c src/pipex.c src/prepare_context.c src/setup_redirection.c src/utils_check_files.c src/utils_cleanup.c src/utils_redirection.c 

OBJ_DIR			=	obj
OBJ				=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
#---------------------------------------------------------#
INC_DIR			=	include
INC_FLAGS		=	-I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR)

LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a
FT				=	ft
LIB_FLAGS		=	-L$(LIBFT_DIR) -l$(FT)
#---------------------------------------------------------#
NAME			=	pipex
all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJ)
	$(LINKER) $(OBJ) $(LIB_FLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) $(INC_FLAGS) -c $< -o $@ 

lib:			$(LIBFT)
$(LIBFT):
	@echo "LIBFT being created"
	@$(MAKE) -C $(LIBFT_DIR)
#---------------------------------------------------------#
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR_BONUS)

fclean:		clean
	rm -rf $(NAME)
	rm -rf $(BONUS)

libclean:
	rm -rf $(LIBFT_DIR)/$(OBJ_DIR)
	rm -rf $(LIBFT)

ffclean: fclean libclean

re: fclean lib all

libre: libclean lib

.PHONY: all bonus lib libre clean fclean libclean ffclean re
#---------------------------------------------------------#
SRC_DIR_BONUS		=	src_bonus
SRC_BONUS			=	src_bonus/main_bonus.c src_bonus/parsing_cmd_bonus.c src_bonus/path_and_cmd_extraction_bonus.c src_bonus/pipex_bonus.c src_bonus/prepare_context_bonus.c src_bonus/setup_redirection_bonus.c src_bonus/utils_check_files_bonus.c src_bonus/utils_cleanup_bonus.c src_bonus/utils_redirection_bonus.c 

OBJ_DIR_BONUS		=	obj_bonus
OBJ_BONUS			=	$(patsubst $(SRC_DIR_BONUS)/%.c, $(OBJ_DIR_BONUS)/%.o, $(SRC_BONUS))
#---------------------------------------------------------#
BONUS				=	pipex_bonus
bonus:				$(BONUS)

$(BONUS):			$(LIBFT) $(OBJ_BONUS)
	$(LINKER) $(OBJ_BONUS) $(LIB_FLAGS) -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
	@mkdir -p $(@D)
	$(COMPILER) $(INC_FLAGS) -c $< -o $@ 
#---------------------------------------------------------#
