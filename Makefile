# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 11:39:48 by sminot            #+#    #+#              #
#    Updated: 2025/02/11 15:23:37 by madelvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/

SRC_FILE = main.c\

EXEC_DIR = $(SRC_DIR)exec/

EXEC = child.c\
	command_exec.c \
	exec.c \
	init_child.c \
	utils.c \

UTILS_DIR = $(SRC_DIR)utils/

UTILS = exit.c\
	list_token.c \
	list_file_utils.c \
	list_cmd_utils.c \
	list_env.c \
	array_utils.c \
	cmd_parser_utils.c \
	

PARSING_DIR = $(SRC_DIR)parsing/

EXEC_DIR = $(SRC_DIR)exec/

PARSING = parsing.c \
	tokenize.c \
	pars_env.c \
	replace_var.c \
	cmd_parser.c \
	replace_var_utils.c \

FILE =$(addprefix $(SRC_DIR), $(SRC_FILE))\
	$(addprefix $(UTILS_DIR), $(UTILS))\
	$(addprefix $(PARSING_DIR), $(PARSING))\
	$(addprefix $(EXEC_DIR), $(EXEC))\

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE) -I$(LIBFT_DIR)/include -MMD -g3
READ_FLAG = -lreadline -lhistory
INCLUDE = include

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(FILE:.c=.o))

DEPS =  $(addprefix $(OBJ_DIR)/, $(FILE:.c=.d))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME) force

$(OBJ_DIR)/%.o : %.c $(LIBFT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) : force
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(READ_FLAG) $(OBJ) -o $(NAME) $(LIBFT)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean : clean 
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

force :

re : fclean all

-include $(DEPS)

.PHONY : all, clean, fclean, re, force