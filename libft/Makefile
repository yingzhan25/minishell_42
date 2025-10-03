# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 14:50:10 by yingzhan          #+#    #+#              #
#    Updated: 2025/09/13 16:33:58 by jkubaev          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -I includes/
AR          = ar rcs
RM          = rm -f

LIBFT_SRCS = ft_strlen.c ft_memset.c ft_bzero.c ft_isalpha.c ft_atoi.c \
		  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		  ft_strdup.c ft_calloc.c \
		  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		  ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		  ft_putendl_fd.c ft_putnbr_fd.c \
		  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		  ft_lstiter.c ft_lstmap.c ft_realloc.c ft_strcmp.c \

PRINTF_SRCS = ft_printf.c ft_handle_char.c \
			ft_handle_str.c ft_handle_ptr.c \
			ft_handle_int.c ft_handle_uint.c \
			ft_handle_hex.c ft_handle_percent.c \
			utils.c

GNL_SRCS = get_next_line.c get_next_line_bonus.c \
		get_next_line_utils.c get_next_line_utils_bonus.c

SRCS        = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)
OBJS        = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re