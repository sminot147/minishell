# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 11:39:48 by sminot            #+#    #+#              #
#    Updated: 2025/03/16 16:42:52 by madelvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/

SRC_FILE = main.c\

EXEC_DIR = $(SRC_DIR)exec/

EXEC = child.c \
	fds_utils.c \
	cmd_utils.c \
	exec_cmd.c \
	file_manager.c \
	path_utils.c \
	start_child.c \

UTILS_DIR = $(SRC_DIR)utils/

UTILS = clean_and_exit.c \
	env_tab.c \
	ft_free_double_array.c \
	get_env_value.c \
	get_random_file_name.c \
	list_cmd.c \
	list_env.c \
	list_file.c \
	list_token.c \
	promp_pwd.c \
	put_env.c \
	safe_close.c \
	signal_handler.c \
	size_of_args.c \
	update_shlev.c \

PARSING_DIR = $(SRC_DIR)parsing/

EXEC_DIR = $(SRC_DIR)exec/

PARSING = parsing.c \
	tokenize.c \
	token_size.c\
	pars_env.c \
	replace_var.c \
	cmd_parser.c \
	cmd_parser_utils.c \
	replace_var_utils.c\
	replace_var_value.c\
	replace_var_check.c\
	here_doc.c \
	here_doc_utils.c \
	parsing_error_message.c \

BUILT_INS_DIR = $(SRC_DIR)builtins/

BUILT_INS = builtins_cd.c \
		builtins_exec.c \
		builtins_exit.c \
		builtins_pwd.c \
		builtins_echo.c \
		builtins_env.c \
		builtins_export.c \
		builtins_unset.c \
		cd_utils.c \
		export_utils.c \

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