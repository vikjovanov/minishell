/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:32:51 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/06 13:32:53 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_slash(char **tilde)
{
	char *usr;
	char *path;

	usr = ft_strdup(*tilde + 1);
	path = ft_strjoin("/Users/", usr);
	if (usr == NULL || path == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&usr);
	ft_strdel(tilde);
	*tilde = path;
}

static void	with_slash(char **tilde, char *home)
{
	char *tmp;

	tmp = *tilde;
	if ((*tilde = ft_streplace_first(*tilde, "~", home)) == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
}

int		expansion_tilde(char **command, char **environ)
{
	char *home;
	int index;

	index = find_in_tab(command, "~");
	if (command[index][0] != '~')
		return (index);
	if (command[index][1] == '~')
		return (index);
	home = (find_in_tab(environ, "HOME=")) == -1 ? ft_strdup("") :
		ft_strdup(&(environ[find_in_tab(environ, "HOME=")][5]));
	if (home == NULL)
		exit(EXIT_FAILURE);
	if (command[index][1] != '/' && command[index][1] != '\0')
		no_slash(&(command[index]));
	else
		with_slash(&(command[index]), home);
	return (index);
}
