# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/20 13:43:14 by vjovanov          #+#    #+#              #
#    Updated: 2019/04/12 13:21:14 by vjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

LIBFT_NAME= libft
LIBFT_LIB= libft/libft.a
LIBFT_LIB_CMD= -L libft/ -lft

SRCS= minishell.c generic.c execute.c exec_bin_build.c errors.c
SRCS+= expansions/tilde.c expansions/dollar.c
SRCS+= builtins/cd.c builtins/echo.c builtins/setenv.c builtins/env.c \
		builtins/unsetenv.c
SRCS_DIR=srcs/

OBJ= $(SRCS:.c=.o)
OBJ_DIR=obj/
OBJS_DIR=$(addprefix $(OBJ_DIR),$(OBJ))

INCLUDES= -Iincludes -Ilibft/includes

CC= gcc
CFLAGS= -Wall -Werror -Wextra

GCCRESET=\033[0m
GCCBLUE=\033[1;36m
GCCBRED=\033[1;91m
GCCYELLOW=\033[1;33m
GCCGREEN=\033[1;32m
GCCRED=\033[1;31m
GCCMAGENTA=\033[1;35m

all:
	@mkdir -p $(OBJ_DIR)
	@make $(NAME)

$(NAME): $(OBJS_DIR)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS_DIR) $(LIBFT_LIB_CMD) $(INCLUDES) -o $(NAME)
	@echo "$(GCCYELLOW)$(basename $(NAME)): $(GCCRESET)$(GCCGREEN)SUCCESS$(GCCRESET)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GCCYELLOW)$(basename $(NAME)): $(GCCRESET)Compilation $(GCCGREEN)-- $(basename $(notdir $<))$(GCCRESET)"

clean: 
	@make -C libft/ clean
	@rm -Rf $(OBJ_DIR)
	@echo "$(GCCYELLOW)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(OBJ_DIR)$(GCCRESET)"

fclean:
	@make -C libft/ fclean
	@echo "$(GCCYELLOW)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(NAME)$(GCCRESET)"
	@rm -Rf $(NAME)
	@echo "$(GCCYELLOW)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(OBJ_DIR)$(GCCRESET)"
	@rm -Rf $(OBJ_DIR)

re: fclean all
