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

int		echo(char **command)
{
	int i;
	char parameter;

	i = 1;
	parameter = 0;
	while (command[i])
	{
		if (ft_strequ(command[i], "-n"))
			parameter |= 1;
		else
			break ;
		i++;
	}
	while (command[i])
	{
		ft_printf("%s", command[i]);
		if (command[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (parameter & 1)
		ft_printf("{bold}{black}%%{eoc}{eocbold}");
	ft_printf("\n");
	return (1);
}
