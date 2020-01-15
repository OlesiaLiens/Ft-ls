#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshyiata <oshyiata@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 17:34:53 by oshyiata          #+#    #+#              #
#    Updated: 2019/04/09 13:34:01 by oshyiata         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CFLAGS		= -Wall -Wextra -Werror
NAME		= ft_ls
SRC_NAME 	= main.c sort_argv.c  error.c valid_argv.c parsing_flags.c \
				sort_files.c write_dir.c free_dir.c create_dir.c add_file.c \
				nbr_len.c cr_t_file.c recursion.c fill_str.c fill.c
LIBFT_DIR	= ./libft/
LIBFT		= ./libft/libft.a
SRC			=$(addprefix ./srcs/, $(SRC_NAME))
OBJ			= $(SRC:%.c=%.o)

.PHONY: norm all re clean fclean

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(CFLAGS) $(OBJ) -I ./includes -I /usr/local/include -I -r $(LIBFT) -L /usr/local/lib -o $(NAME) -lm

%.o:%.c $(LIBFT) ./includes/ft_ls.h
	gcc $(CFLAGS) -c $< -o $@ -I ./includes

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
