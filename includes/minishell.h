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
#define ERR_TOO_MANY_ARGS 403
#define ERR_VARNAME_ALNUM 404
#define ERR_BAD_BEGIN_VARNAME 405
#define ERR_TOO_FEW_ARGS 406
#define ERR_NO_SUCH_FILE_DIR 407
#define ERR_NOT_A_DIRECTORY 408
#define ERR_FAILED 409

char	**dup_env(char **environ);
int		execute_cmd(char **command, char ***environ);
int		exec_binary_built(char **command, char ***environ);
int		find_in_tab(char **tab, char *to_find);
char	*create_new_path(char *path, char *file_name);
int		free_tab(char *tab, int return_value);
int		free_dtab(char **tab, int return_value);
int		print_error(int error_code, char *error_component);
int		expansion_tilde(char **command, char **environ);
int		expansion_dollar(char **command, int i, char **environ);

int		_env(char **environ);
int		_echo(char **command);
int		_setenv(char **command, char ***environ);
int		_unsetenv(char **command, char ***environ);
int		_cd(char **command, char **environ);

#endif