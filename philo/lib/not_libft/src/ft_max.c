/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_max.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 16:28:20 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/26 22:13:24 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "not_libft.h"

long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

unsigned long	ft_maxu(unsigned long a, unsigned long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_maxf(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
