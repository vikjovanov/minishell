/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:06:08 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/07 18:06:09 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_env(char *command, char **environ)
{
	char *new_command;

	if ((new_command = ft_strjoin(command, "=")) == NULL)
		exit(EXIT_FAILURE);
	if (find_in_tab(environ, new_command) != -1)
		return (free_tab(new_command, 1));
	return (free_tab(new_command, 0));
}

static void	create_new_environ(char **new_env, char ***environ, char **command)
{
	int		i;
	int		j;
	int		k;
	char	*new_command;

	i = -1;
	j = 0;
	while (environ[0][++i])
	{
		k = -1;
		while (command[++k])
		{
			new_command = ft_strjoin(command[k], "=");
			if (ft_strnstr(environ[0][i], new_command,
				ft_strlen(new_command)) != NULL && free_tab(new_command, 1))
				break ;
			ft_strdel(&new_command);
		}
		if (command[k] != NULL)
			continue ;
		new_env[j] = ft_strdup(environ[0][i]);
		j++;
	}
	free_dtab(*environ, 1);
	*environ = new_env;
}

int			built_unsetenv(char **command, char ***environ)
{
	int		nb_to_delete;
	int		i;
	char	**new_environ;

	i = 1;
	nb_to_delete = 0;
	new_environ = NULL;
	if (command[i] == NULL)
		return (print_error(ERR_TOO_FEW_ARGS, "unsetenv"));
	while (command[i])
	{
		if (is_in_env(command[i], *environ))
			nb_to_delete++;
		i++;
	}
	if (nb_to_delete == 0)
		return (1);
	new_environ = (char**)ft_memalloc((sizeof(char*)
		* (ft_array_length((void**)*environ) - nb_to_delete + 1)));
	new_environ[ft_array_length((void**)*environ) - nb_to_delete] = NULL;
	create_new_environ(new_environ, environ, &(command[1]));
	return (1);
}
