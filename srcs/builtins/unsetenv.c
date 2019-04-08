/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:06:08 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/07 18:06:09 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_unsetenv(char **command, char ***environ)
{
	int nb_to_delete;
	int i;

	i = 1;
	nb_to_delete = 0;
	while (command[i])
	{
		if (find_in_tab(*environ, command[i]) != -1)
			nb_to_delete++;
		i++;
	}
	printf("%d\n", nb_to_delete);
	return (1);
}