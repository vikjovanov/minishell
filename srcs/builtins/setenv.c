/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:06:11 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/07 18:06:12 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_environ(char ***environ, char **cmd)
{
	int size;
	int i;
	char **new_env;
	char *tmp;

	size = ft_array_length((void**)*environ);
	if ((new_env = (char**)malloc(sizeof(char*) * (size + 2))) == NULL)
		exit(EXIT_FAILURE);
	new_env[size + 1] = NULL;
	i = -1;
	while ((*environ)[++i])
		if ((new_env[i] = ft_strdup(environ[0][i])) == NULL)
			exit(EXIT_FAILURE);
	if ((tmp = ft_strjoin(cmd[1], "=")) == NULL)
		exit(EXIT_FAILURE);
	new_env[i] = (cmd[2] == NULL) ? ft_strdup(tmp) : ft_strjoin(tmp, cmd[2]);
	if (new_env[i] == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
	ft_2dtabdel((void**)*environ, size);
	*environ = new_env;
}

int		check_params(char **param1, char **param2)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	if (!ft_isalpha(param1[0][0]))
		return (print_error(ERR_BAD_BEGIN_VARNAME, "setenv"));
	while (param1[0][i])
	{
		if (!ft_isalnum(param1[0][i]))
			return (print_error(ERR_VARNAME_ALNUM, "setenv"));
		i++;
	}
	if (param2 != NULL && *param2 != NULL)
	{
		tmp = *param2;
		*param2 = ft_strdupwc(*param2, '\\');
		ft_strdel(&tmp);
	}
	return (1);
}

int		_setenv(char **command, char ***environ)
{
	char **unset;

	unset = NULL;
	if (ft_array_length((void**)command) > 3)
		return (print_error(ERR_TOO_MANY_ARGS, "setenv"));
	if (ft_array_length((void**)command) == 1)
		return (_env(*environ));
	if (check_params(&(command[1]), &(command[2])) == 1)
	{		
		unset = (char**)malloc(sizeof(char*) * 3);
		unset[0] = ft_strdup("unsetenv");
		unset[1] = ft_strdup(command[1]);
		unset[2] = NULL;
		_unsetenv(unset, environ);
		new_environ(environ, command);
	}
	return (free_dtab(unset, 1));
}