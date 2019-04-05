/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:16:26 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 14:16:27 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		try_exec(char **cmd, char **environ, char *path)
{
	char *new_path;
	struct stat info;
	int		pid;

	if ((new_path = create_new_path(path, cmd[0])) == NULL)
		exit(EXIT_FAILURE);
	if (lstat(new_path, &info) != -1)
	{
		if (info.st_mode & S_IXUSR)
		{
			if ((pid = fork()) == -1)
				return (print_error(free_tab(new_path, ERR_FORK), "fork"));
			if (pid == 0)
			{
				if ((execve(new_path, cmd, environ)) == -1)
					ft_printf("minishell: execve: Unable to execute script");
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
			return (free_tab(new_path, 1));
		}
		else
			return (print_error(free_tab(new_path, ERR_PERM_DENIED), cmd[0]));
	}
	return (free_tab(new_path, 0));
}

int		exec_binary_built(char **command, char **environ)
{
	char	**path;
	int		i;
	int		result;

	i = find_in_tab(environ, "PATH=");
	path = NULL;
	if (i != -1)
		if ((path = ft_strsplit(&(environ[i][5]), ':')) == NULL)
			exit(EXIT_FAILURE);
	if (i == -1)
		return (print_error(ERR_CMD_NOT_FOUND, command[0]));
	i = 0;
	while (path[i])
	{	
		if ((result = try_exec(command, environ, path[i])) != 0)
			return (free_dtab(path, result));
		i++;
	}
	return (print_error(free_dtab(path, ERR_CMD_NOT_FOUND), command[0]));
}