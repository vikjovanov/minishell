/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:52:30 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 11:52:31 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		use_expansion(char **command, char **environ, int type)
{
	int i;

	i = 0;
	if (type == 1)
		while (find_in_tab(&(command[i]), "~") != -1)
		{
			i += expansion_tilde(&(command[i]), environ);
			i++;
		}
	else
		while (ft_strchr(&(command[0][i]), '$') != NULL)
		{
			i += expansion_dollar(command, i, environ);
			i++;
		}
	return (1);
}

void	command_line(char ***environ)
{
	char *line;
	char **command;

	command = NULL;
	while (1)
	{
		ft_printf("{bold}{brightblue}$>{eoc}{eocbold} ");
		if (get_next_line(0, &line) == 1)
		{
			use_expansion(&line, *environ, 0);
			command = ft_strsplitfunc(line, &ft_isspace);
		}
		if (ft_strequ(command[0], "exit"))
			return ;
		use_expansion(command, *environ, 1);
		execute_cmd(command, environ);
	}
}

int		main(int argc, char **argv, char **environ)
{
	argv = NULL;
	argc = 0;
	environ = dup_env(environ);

	command_line(&environ);

	return (0);
}