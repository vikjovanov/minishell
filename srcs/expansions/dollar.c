/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:32:55 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/06 13:32:56 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_varname(char *command)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (command[i] != '$')
		i++;
	while (!ft_isspace(command[++i]) && command[i] != '/' && command[i] != '\0')
		size++;
	return (ft_strsub(command, i - size - 1, size + 1));

}

int		is_in_env(char *varname, char **environ)
{
	char	*final_var;
	int		index;

	if ((final_var = ft_strjoin(varname, "=")) == NULL)
		exit(EXIT_FAILURE);
	index = find_in_tab(environ, final_var);
	return (free_tab(final_var, index));
}

int		expansion_dollar(char **command, int i, char **environ)
{
	int 	index;
	char *cmd;
	char *tmp;
	char *replacement;
	int j;

	replacement = NULL;
	index = ft_strclen(&(command[0][i]), '$');
	if ((cmd = get_varname(&(command[0][i + index]))) == NULL)
		exit(EXIT_FAILURE);
	if (ft_strequ(cmd, "$"))
		return (index);
	if ((j = is_in_env(&(cmd[1]), environ)) != -1)
		replacement = ft_strdup(&(environ[j][ft_strclen(environ[j], '=') + 1]));
	else
		replacement = ft_strdup("");
	tmp = *command;
	if (replacement == NULL)
		exit(EXIT_FAILURE);
	if ((*command = ft_streplace_first(*command, cmd, replacement)) == NULL)
		exit(EXIT_FAILURE);
	ft_strdel(&tmp);
	return (index);
}