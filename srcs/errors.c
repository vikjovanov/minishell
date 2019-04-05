/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:52:13 by vjovanov          #+#    #+#             */
/*   Updated: 2019/04/05 15:52:13 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_error(int error_code, char *error_component)
{
	if (error_code == ERR_PERM_DENIED)
		ft_printf("minishell: %s: permission denied\n", error_component);
	else if (error_code == ERR_FORK)
		ft_printf("minishell: %s: an error has occured\n", error_component);
	else if (error_code == ERR_CMD_NOT_FOUND)
		ft_printf("minishell: %s: command not found\n", error_component);
	return (error_code);
}