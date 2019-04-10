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

static int is_in_env(char *command, char **environ)
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
	
}

int		_unsetenv(char **command, char ***environ)
{
	int nb_to_delete;
	int i;
	char **new_environ;

	i = 1;
	nb_to_delete = 0;
	while (command[i])
	{
		if (is_in_env(command[i], *environ))
			nb_to_delete++;
		i++;
	}
	new_environ = (char**)malloc((sizeof(char*)
		* ft_array_length(environ) - nb_to_delete) + 1);
	new_environ[ft_array_length(environ) - nb_to_delete] = NULL;
	create_new_environ(new_environ, environ, command);
	printf("%d\n", nb_to_delete);
	return (1);
}