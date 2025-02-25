# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 11:39:48 by sminot            #+#    #+#              #
#    Updated: 2025/02/25 19:35:23 by madelvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/

SRC_FILE = main.c\

EXEC_DIR = $(SRC_DIR)exec/

EXEC = child.c\
	exec_cmd.c \
	start_child.c \

UTILS_DIR = $(SRC_DIR)utils/

UTILS = child_manager.c \
	clean_and_exit.c \
	clean_child.c \
	cmd_parser_function.c \
	debbug_messager.c \
	env_tab_handler.c \
	export_handler.c \
	file_manager.c \
	ft_free_double_array.c \
	get_env_value.c \
	get_random_file_name.c \
	list_cmd.c \
	list_env.c \
	list_file.c \
	list_token.c \
	parsing_message_error.c \
	path_handler.c \
	promp_pwd.c \
	put_env_export.c \
	safe_close.c \
	signal_handler.c \
	size_of_args.c \
	update_shlev.c \
	cmd_handler.c \
	replace_var_check.c \
	cd_function.c \

PARSING_DIR = $(SRC_DIR)parsing/

EXEC_DIR = $(SRC_DIR)exec/

PARSING = parsing.c \
	tokenize.c \
	token_size.c\
	pars_env.c \
	replace_var.c \
	cmd_parser.c \
	replace_var_utils.c\
	replace_var_value.c\
	here_doc.c \

BUILT_INS_DIR = $(SRC_DIR)builtins/

BUILT_INS = builtins_cd.c \
		builtins_checker.c \
		builtins_exit.c \
		builtins_pwd.c \
		builtins_echo.c \
		builtins_env.c \
		builtins_export.c \
		builtins_unset.c \

FILE =$(addprefix $(SRC_DIR), $(SRC_FILE))\
	$(addprefix $(UTILS_DIR), $(UTILS))\
	$(addprefix $(PARSING_DIR), $(PARSING))\
	$(addprefix $(EXEC_DIR), $(EXEC))\
	$(addprefix $(BUILT_INS_DIR), $(BUILT_INS))\

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