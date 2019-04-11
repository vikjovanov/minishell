/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:05:57 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/07 18:05:58 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_params(char **command, char *parameter)
{
	int i;
	int j;

	i = 1;
	while (command[i] && command[i][0] == '-')
	{
		j = 1;
		while (command[i][j] == 'n')
			j++;
		if (command[i][j] == '\0')
			*parameter |= 1;
		else
			break ;
		i++;
	}
	return (i);
}

int				built_echo(char **command)
{
	int		i;
	char	parameter;

	parameter = 0;
	i = check_params(command, &parameter);
	while (command[i])
	{
		ft_printf("%s", command[i]);
		if (command[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (parameter & 1)
		ft_printf("{bgwhite}{bold}{black}%%{eoc}{eocbold}{bgeoc}");
	ft_printf("\n");
	return (1);
}
