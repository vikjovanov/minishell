/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:06:10 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 14:06:11 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_pwd(char **cmd, char **environ, char *path)
{
	char *new_path;
	struct stat info;
	int		pid;

	if ((new_path = create_new_path(path, cmd[0])) == NULL)
		exit(EXIT_FAILURE);
	if (free_tab(path, 1) && lstat(new_path, &info) != -1)
	{
		if (info.st_mode & S_IXUSR)
		{
			if ((pid = fork()) == -1)
				return (print_error(free_tab(new_path, ERR_FORK), "fork"));
			if (pid == 0)
			{
				if ((execve(new_path, cmd, environ)) == -1)
					ft_printf("minishell: execve: Unable to execute script\n");
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

int		exec_exact_pwd(char **command, char **environ)
{
	struct stat info;
	int		pid;

	if (lstat(command[0], &info) != -1)
	{
		if (info.st_mode & S_IXUSR)
		{
			if ((pid = fork()) == -1)
				return (print_error(ERR_FORK, "fork"));
			if (pid == 0)
			{
				if ((execve(command[0], command, environ)) == -1)
					ft_printf("minishell: execve: Unable to execute script\n");
				exit(EXIT_SUCCESS);
			}
			wait(NULL);
			return (1);
		}
		else
			return (print_error(ERR_PERM_DENIED, command[0]));
	}
	return (print_error(ERR_CMD_NOT_FOUND, command[0]));
}

int		execute_cmd(char **command, char ***environ)
{
	int result;

	result = 0;
	if (ft_strchr(command[0], '/') == NULL)
		result = exec_binary_built(command, environ);
	else if (command[0][0] == '/')
		result = exec_exact_pwd(command, *environ);
	else
		result = exec_pwd(command, *environ, getcwd(NULL, 0));
	return (result);
}