/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 11:58:08 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 11:58:09 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_env(char **environ)
{
	char	**new_environ;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	new_environ = (char**)malloc(sizeof(char*) * (i + 1));
	new_environ[i] = NULL;
	i = 0;
	while (environ[i])
	{
		new_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	return (new_environ);
}

int		find_in_tab(char **tab, char *to_find)
{
	int index;
	char *is_in;

	index = 0;
	while (tab[index])
	{
		if ((is_in = ft_strstr(tab[index], to_find)) != NULL)
			return (index);
		index++;
	}
	return (-1);
}

char	*create_new_path(char *path, char *file_name)
{
	char *new_path;
	char *tmp;

	if ((tmp = ft_strjoin(path, "/")) == NULL)
		return (NULL);
	if ((new_path = ft_strjoin(tmp, file_name)) == NULL)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	return (new_path);
}

int		free_tab(char *tab, int return_value)
{
	ft_strdel(&tab);
	return (return_value);
}

int		free_dtab(char **tab, int return_value)
{
	int i;

	i = 0;
	if (tab == NULL)
		return (return_value);
	while (tab[i])
	{
		ft_strdel(&(tab[i]));
		i++;
	}
	free(tab);
	tab = NULL;
	return (return_value);
}