/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtone <elehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:54:49 by elehtone          #+#    #+#             */
/*   Updated: 2025/07/04 11:28:04 by elehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief Print error message to standard error.
 * @param [in] *message
 */
void	put_error(char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

/**
 * @brief Error handling function. Frees and informs depending on parameters.
 * @param [in] *ps: Not required. t_parse
 * @param [in] **matrix: Not required.
 * @param [in] *vector: Not required.
 * @param [in] *message: Not required. Error message to stderr.
 * @return Always false. To be used in function return.
 * @details Catch all annoying function. May change later.
 */
bool	free_helper(t_parse *ps, char **matrix, void *vector, char *message)
{
	if (message)
		put_error(message);
	if (ps)
	{
		ft_lstclear(&ps->objects, &free);
		close(ps->fd);
	}
	if (matrix && *matrix && **matrix)
		free_matrix(matrix);
	if (vector)
	{
		free(vector);
		vector = NULL;
	}
	return (false);
}
