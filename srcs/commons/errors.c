/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:48:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 12:27:41 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

int		handle_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}

void	*handle_error_null(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (NULL);
}

void	*handle_error_free(void *ptr, char *msg)
{
	free(ptr);
	return (msg ? handle_error_null(msg) : NULL);
}
