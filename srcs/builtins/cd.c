/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:06:17 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/07 18:06:18 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char *path, char *dirname)
{
	struct stat info;

	if (dirname == NULL)
		dirname = path;
	if (lstat(path, &info) != -1)
	{
		if (info.st_mode & S_IXUSR)
		{
			if (info.st_mode & S_IFDIR)
				return (1);
			else
				return (print_error(ERR_NOT_A_DIRECTORY, dirname));
		}
		else
			return (print_error(ERR_PERM_DENIED, dirname));
	}
	return (print_error(ERR_NO_SUCH_FILE_DIR, dirname));
}

static int	absolute_path(char **command)
{
	if (check_access(command[1], NULL) == 1)
		if ((chdir(command[1])) == -1)
			return (print_error(ERR_FAILED, "cd"));
	return (1);
}

static int	relative_path(char **command)
{
	char *current_path;
	char *rel_path;
	char *tmp;

	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (0);
	current_path = ft_strjoin(tmp, "/");
	rel_path = ft_strjoin(current_path, command[1]);
	ft_strdel(&tmp);
	if (current_path == NULL || rel_path == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&current_path);
	if (check_access(rel_path, command[1]) == 1)
	{
		if ((chdir(command[1])) == -1)
			return (free_tab(rel_path, print_error(ERR_FAILED, "cd")));
	}
	else
		return (free_tab(rel_path, 0));
	return (free_tab(rel_path, 1));
}

static int	oldpwd_path(char **environ, char **command)
{
	char	*path;
	int		index;
	char	*home;

	index = find_in_tab(environ, "OLDPWD=");
	home = find_in_tab(environ, "HOME=") == -1 ? ft_strdup("")
		: ft_strdup(&(environ[find_in_tab(environ, "HOME=")][5]));
	if (ft_array_length((void**)command) == 1 || ft_strequ(command[1], "--"))
	{
		if ((chdir(home)) == -1)
			return (free_tab(home, print_error(ERR_FAILED, "cd")));
		return (free_tab(home, 1));
	}
	if ((path = ft_strdup(index == -1 ? "" : &(environ[index][7]))) == NULL)
		exit(EXIT_FAILURE);
	if (check_access(path, NULL) == 1)
	{
		if ((chdir(path)) == -1)
			return (free_tab(path, print_error(ERR_FAILED, "cd")));
	}
	else
		return (free_tab(path, 0));
	return (free_tab(path, 1));
}

int			built_cd(char **command, char ***environ)
{
	char		**oldpwd;

	oldpwd = (char**)ft_memalloc(sizeof(char*) * 4);
	oldpwd[0] = ft_strdup("setenv");
	oldpwd[1] = ft_strdup("OLDPWD");
	oldpwd[2] = getcwd(NULL, 0);
	if (ft_array_length((void**)command) > 2)
		return (free_dtab(oldpwd, print_error(ERR_TOO_MANY_ARGS, "cd")));
	if (ft_array_length((void**)command) == 1
		|| (ft_strlen(command[1]) == 1 && command[1][0] == '-')
		|| (ft_strlen(command[1]) == 2 && ft_strequ(command[1], "--")))
	{
		if ((oldpwd_path(*environ, command)) == 1)
			return (built_setenv(oldpwd, environ) && free_dtab(oldpwd, 1));
		else
			return (free_dtab(oldpwd, 1));
	}
	if (command[1][0] == '/')
	{
		if ((absolute_path(command)) == 1)
			built_setenv(oldpwd, environ);
	}
	else if ((relative_path(command)) == 1)
		built_setenv(oldpwd, environ);
	return (free_dtab(oldpwd, 1));
}
