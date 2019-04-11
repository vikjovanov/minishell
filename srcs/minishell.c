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

void	free_dtabv(char **tab)
{
	int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		ft_strdel(&(tab[i]));
		i++;
	}
	free(tab);
	tab = NULL;
	return ;
}

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

char	*get_dirpath(void)
{
	char *path;
	char *dir;

	if ((path = getcwd(NULL, 0)) == NULL)
		return (ft_strdup(""));
	if ((dir = ft_strdup(strrchr(path, '/') + 1)) == NULL)
		exit(EXIT_FAILURE);
	if (ft_strequ(dir, ""))
	{
		ft_strdel(&dir);
		if ((dir = ft_strdup("/")) == NULL)
			exit(EXIT_FAILURE);
	}
	ft_strdel(&path);
	return (dir);
}

void	command_line(char ***environ)
{
	char *line;
	char **command;
	char *dirpath;

	command = NULL;
	while (1)
	{
		dirpath = get_dirpath();
		ft_printf("{bold}{brightblue}$ {cyan}%s{brightblue} >{eoc}{eocbold} ",
			dirpath);
		ft_strdel(&dirpath);
		if (get_next_line(0, &line) == 1)
		{
			use_expansion(&line, *environ, 0);
			command = ft_strsplitfunc(line, &ft_isspace);
			ft_strdel(&line);
			if (ft_array_length((void**)command) == 0 && free_dtab(command, 1))
				continue ;
		}
		if (ft_strequ(command[0], "exit"))
			return (free_dtabv(command));
		use_expansion(command, *environ, 1);
		execute_cmd(command, environ);
		free_dtab(command, 1);
	}
}

int		main(int argc, char **argv, char **environ)
{
	argv = NULL;
	argc = 0;
	environ = dup_env(environ);
	command_line(&environ);
	free_dtab(environ, 1);
	return (0);
}
