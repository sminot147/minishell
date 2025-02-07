# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sminot <simeon.minot@outlook.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 11:39:48 by sminot            #+#    #+#              #
#    Updated: 2025/02/07 16:57:22 by sminot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/

SRC_FILE = main.c\

UTILS_DIR = $(SRC_DIR)utils/

UTILS = exit.c\
	list_token.c\
	list_env.c\

PARSING_DIR = $(SRC_DIR)parsing/

PARSING = parsing.c\
	tokenize.c\
	pars_env.c\

FILE =$(addprefix $(SRC_DIR), $(SRC_FILE))\
	$(addprefix $(UTILS_DIR), $(UTILS))\
	$(addprefix $(PARSING_DIR), $(PARSING))\

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE) -I$(LIBFT_DIR)/include -MMD -g3
READ_FLAG = -lreadline -lhistory
INCLUDE = include

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(FILE:.c=.o))

DEPS =  $(addprefix $(OBJ_DIR)/, $(FILE:.c=.d))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o : %.c $(LIBFT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME) force

$(LIBFT) : force
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) $(LIBFT)
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