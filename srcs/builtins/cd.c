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

static int check_access(char *path, char *dirname)
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

static char *absolute_path(char **command)
{
	char *absol_path;

	absol_path = NULL;
	if (check_access(command[1], NULL) == 1)
	{
		if ((chdir(command[1])) == -1)
			print_error(ERR_FAILED, "cd");
		else
			if ((absol_path = ft_strdup(command[1])) == NULL)
				exit(EXIT_FAILURE);
	} 
	return (absol_path);
}

static char *relative_path(char **command)
{
	char *current_path;
	char *rel_path;
	char *tmp;

	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NULL);
	current_path = ft_strjoin(tmp, "/");
	rel_path = ft_strjoin(current_path, command[1]);
	ft_strdel(&current_path);
	ft_strdel(&tmp);
	if (current_path == NULL || rel_path == NULL)
		exit(EXIT_FAILURE);
	if (check_access(rel_path, command[1]) == 1)
	{
		if ((chdir(command[1])) == -1)
		{
			print_error(ERR_FAILED, "cd");
			return (NULL);
		}
	}
	else
		return (NULL);
	return (rel_path);
}

static char *oldpwd_path(char **command, char **environ)
{

}

int		_cd(char **command, char **environ)
{
	static char	*oldpwd = NULL;
	char		*new_old;

	new_old = NULL;
	if (ft_array_length((void**)command) > 2)
		return (print_error(ERR_TOO_MANY_ARGS, "cd"));
	if (ft_strlen(command[1] == 1) && ft_strlen(command[1][0] == '-'))
		oldpwd_path(command, environ);
	if (command[1][0] == '/')
		new_old = absolute_path(command);
	else
		new_old = relative_path(command);
	if (new_old != NULL)
	{
		ft_strdel(&oldpwd);
		oldpwd = ft_strdup(new_old);
		ft_strdel(&new_old);
	}
	return (1);	
}
