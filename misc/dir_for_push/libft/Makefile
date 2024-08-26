# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afocant <afocant@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/25 14:26:45 by afocant           #+#    #+#              #
#    Updated: 2024/08/27 00:36:02 by afocant          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------------------------------#
CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

GFLAGS	=	-g
#---------------------------------------------------------#
SRC_DIR		=	src

SRC_SUBDIRS	=	src/get_next_line src/list_fn src/mem_fn src/printf src/str_fn 

SRC			=	src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c src/list_fn/ft_lstadd_back_bonus.c src/list_fn/ft_lstadd_front_bonus.c src/list_fn/ft_lstclear_bonus.c src/list_fn/ft_lstdelone_bonus.c src/list_fn/ft_lstiter_bonus.c src/list_fn/ft_lstlast_bonus.c src/list_fn/ft_lstmap_bonus.c src/list_fn/ft_lstnew_bonus.c src/list_fn/ft_lstsize_bonus.c src/mem_fn/ft_bzero.c src/mem_fn/ft_calloc.c src/mem_fn/ft_memchr.c src/mem_fn/ft_memcmp.c src/mem_fn/ft_memcpy.c src/mem_fn/ft_memmove.c src/mem_fn/ft_memset.c src/printf/ft_printf.c src/printf/ft_printf_utils.c src/str_fn/ft_atoi.c src/str_fn/ft_atol.c src/str_fn/ft_isalnum.c src/str_fn/ft_isalpha.c src/str_fn/ft_isascii.c src/str_fn/ft_isdigit.c src/str_fn/ft_isprint.c src/str_fn/ft_isquote.c src/str_fn/ft_isspace.c src/str_fn/ft_itoa.c src/str_fn/ft_print_nbr.c src/str_fn/ft_print_ptr.c src/str_fn/ft_print_strv.c src/str_fn/ft_putchar_fd.c src/str_fn/ft_putendl_fd.c src/str_fn/ft_putnbr_fd.c src/str_fn/ft_putstr_fd.c src/str_fn/ft_split.c src/str_fn/ft_strchr.c src/str_fn/ft_strcmp.c src/str_fn/ft_strdup.c src/str_fn/ft_striteri.c src/str_fn/ft_strjoin.c src/str_fn/ft_strlcat.c src/str_fn/ft_strlcpy.c src/str_fn/ft_strlen.c src/str_fn/ft_strmapi.c src/str_fn/ft_strncmp.c src/str_fn/ft_strnstr.c src/str_fn/ft_strrchr.c src/str_fn/ft_strtrim.c src/str_fn/ft_substr.c src/str_fn/ft_tolower.c src/str_fn/ft_toupper.c 

OBJ_DIR		=	obj

OBJ_SUBDIRS	=	$(SRC_SUBDIRS:$(SRC_DIR)%=$(OBJ_DIR)%)

OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
#---------------------------------------------------------#
INC_DIR		=	includes

NAME		=	libft.a

.PHONY: all clean fclean re
#---------------------------------------------------------#
all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $@ $^ 
	@echo "libft created"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_SUBDIRS)
	@$(CC) $(CFLAGS) $(GFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_SUBDIRS):
	@mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)

re: fclean all
