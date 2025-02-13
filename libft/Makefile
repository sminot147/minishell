# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madelvin <madelvin@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 14:53:08 by sminot            #+#    #+#              #
#    Updated: 2025/02/13 20:22:20 by madelvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CHAR_DIR = src/char/

CHAR = ft_isalpha.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_toupper.c\
	ft_tolower.c\

INT_DIR = src/int/

INT = ft_atoi.c\
	ft_itoa.c\

LST_DIR = src/lst/

LST = ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c\
	ft_lstiter.c\
	ft_lstmap.c\

MEM_DIR = src/mem/

MEM = ft_bzero.c\
	ft_calloc.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\

PUT_DIR = src/put/

PUT = putchar_fd.c\
	putstr_fd.c\
	putnbr_fd.c\
	putendl_fd.c\
	ft_printf.c\

STR_DIR = src/str/

STR = ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	str_append.c\

GNL_DIR = src/gnl/

GNL = get_next_line.c\
	get_next_line_utils.c\

FILE = $(addprefix $(CHAR_DIR), $(CHAR))\
	$(addprefix $(INT_DIR), $(INT))\
	$(addprefix $(MEM_DIR), $(MEM))\
	$(addprefix $(PUT_DIR), $(PUT))\
	$(addprefix $(STR_DIR), $(STR))\
	$(addprefix $(GNL_DIR), $(GNL))\
	$(addprefix $(LST_DIR), $(LST))\

OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(FILE:.c=.o))

DEPS= $(addprefix $(OBJ_DIR)/, $(FILE:.c=.d))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE) -MMD
INCLUDE = include

AR = ar -rsc

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all, clean, fclean, re