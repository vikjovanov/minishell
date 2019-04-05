/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:52:43 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 11:52:44 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//////////////////////////
////////////////
#include <stdio.h>
///////////////
// A SUPPRIMER


#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#define ERR_PERM_DENIED 400
#define ERR_FORK 401
#define ERR_CMD_NOT_FOUND 402

char	**dup_env(char **environ);
int		execute_cmd(char **command, char **environ);
int		exec_binary_built(char **command, char **environ);
int		find_in_tab(char **tab, char *to_find);
char	*create_new_path(char *path, char *file_name);
int		free_tab(char *tab, int return_value);
int		free_dtab(char **tab, int return_value);
int		print_error(int error_code, char *error_component);

#endif