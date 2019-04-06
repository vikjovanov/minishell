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

int		use_expansion(char **line, char **environ)
{
	int all_replaced;

	all_replaced = 0;
	while (all_replaced != 1)
	{
		if (ft_strchr(*line, '$'))
			expansion_dollar(line, environ);
		else if (ft_strchr(*line, '~'))
			expansion_tilde(line, eviron);
		else
			all_replaced = 1;
	}
	return (1);
}

void	command_line(char **environ)
{
	char *line;
	char **command;

	command = NULL;
	while (1)
	{
		ft_printf("{bold}{brightblue}$>{eoc}{eocbold} ");
		if (get_next_line(0, &line) == 1)
		{
			use_expansion(&line, environ);
			command = ft_strsplitfunc(line, &ft_isspace);
		}
		if (ft_strequ(command[0], "exit"))
			return ;
		execute_cmd(command, environ);
	}
}

int		main(int argc, char **argv, char **environ)
{
	argv = NULL;
	argc = 0;
	environ = dup_env(environ);

	command_line(environ);

	return (0);
}