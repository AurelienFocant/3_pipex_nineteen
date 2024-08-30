#---------------------------------------------------------#
CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

GFLAGS	=	-g

DFLAGS	=	-fsanitize=address -fsanitize=undefined
#---------------------------------------------------------#
SRC_DIR		=	src

SRC_SUBDIRS	=	$(shell find $(SRC_DIR)/* -type d)

SRC			=	$(shell find $(SRC_DIR) -type f -name "*.c")

OBJ_DIR		=	obj

OBJ_SUBDIRS	=	$(SRC_SUBDIRS:$(SRC_DIR)%=$(OBJ_DIR)%)

OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#---------------------------------------------------------#
INC_DIR		=	includes

LIBFT_DIR	=	libft

CPU		=	$(shell uname -p)
ifeq ($(CPU),arm)
	LIBFT	=	libft_arm.a
	FT		=	ft_arm
else
	LIBFT	=	libft_x86.a
	FT		=	ft_x86
endif


.PHONY: all lib clean fclean libclean re
#---------------------------------------------------------#
NAME	=	pipex

all:		$(NAME)

lib:		$(LIBFT_DIR)/$(LIBFT)

$(NAME):	$(OBJ) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIBFT_DIR) -l$(FT)

$(LIBFT_DIR)/$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_SUBDIRS) $(OBJ_DIR)
	@echo $(OBJ_SUBDIRS)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -c $< -o $@ 

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_SUBDIRS):
	mkdir -p $@
#---------------------------------------------------------#
clean:
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -rf $(NAME) *dSYM 

libclean:
	rm -rf $(LIBFT_DIR)/$(OBJ_DIR)
	rm -rf $(LIBFT_DIR)/$(LIBFT)

re: fclean libclean all

libre: libclean lib
#---------------------------------------------------------#
