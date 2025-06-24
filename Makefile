# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymaia-do <ymaia-do@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/06 16:43:06 by yasmin            #+#    #+#              #
#    Updated: 2025/06/24 22:39:27 by ymaia-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR) -I$(LIBFT_DIR)/get_next_line
FT_PRINTF_DIR = $(LIBFT_DIR)/ft_printf
GNL_DIR = $(LIBFT_DIR)/get_next_line

FT_PRINTF_OBJ = $(FT_PRINTF_DIR)/ft_printf.o $(FT_PRINTF_DIR)/ft_printf_utils.o
GNL_OBJ = $(GNL_DIR)/get_next_line.o $(GNL_DIR)/get_next_line_utils.o

INCLUDES = -I. $(LIBFT_INC)
LIBS = $(LIBFT_A)

LIBFT_REPO = git@github.com:Yasmin-Maia/libft.git

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(LIBFT_A) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT_A):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Libft não encontrada, clonando..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@echo "Compilando libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJS_SERVER) $(FT_PRINTF_OBJ) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_SERVER) $(LIBS) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(FT_PRINTF_OBJ) $(GNL_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_CLIENT) $(LIBS) -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf libft
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
