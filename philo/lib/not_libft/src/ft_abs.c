/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_abs.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 15:18:25 by jkoers        #+#    #+#                 */
/*   Updated: 2020/11/26 17:13:19 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "not_libft.h"

long	ft_abs(long num)
{
	if (num < 0)
		return (0 - num);
	else
		return (num);
}
