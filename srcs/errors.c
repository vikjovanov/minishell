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
		ft_printf("minishell: %s: permission denied.\n", error_component);
	else if (error_code == ERR_FORK)
		ft_printf("minishell: %s: an error has occured.\n", error_component);
	else if (error_code == ERR_CMD_NOT_FOUND)
		ft_printf("minishell: %s: command not found.\n", error_component);
	else if (error_code == ERR_TOO_MANY_ARGS)
		ft_printf("minishell: %s: too many arguments.\n", error_component);
	else if (error_code == ERR_VARNAME_ALNUM)
		ft_printf("minishell: %s: variable name must contain alphanumeric \
characters.\n", error_component);
	else if (error_code == ERR_BAD_BEGIN_VARNAME)
		ft_printf("minishell: %s: variable name must begin with a letter.\n",
			error_component);
	else if (error_code == ERR_TOO_FEW_ARGS)
		ft_printf("minishell: %s: too few arguments.\n", error_component);
	else if (error_code == ERR_NO_SUCH_FILE_DIR)
		ft_printf("minishell: %s: no such file or directory.\n",
			error_component);
	else if (error_code == ERR_NOT_A_DIRECTORY)
		ft_printf("minishell: %s: not a directory.\n", error_component);
	else if (error_code == ERR_FAILED)
		ft_printf("minishell: %s: failed to execute.\n", error_component);
	return (error_code);
}
