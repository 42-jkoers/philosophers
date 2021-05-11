/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_ft_numlen_u.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 16:41:03 by jkoers        #+#    #+#                 */
/*   Updated: 2020/10/31 17:07:48 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "not_libft.h"
#include <stdio.h>

int	main(void)
{
	printf("%lu 3\n", ft_numlenu(123, 10));
	printf("%lu 8\n", ft_numlenu(255, 2));
	printf("%lu 3\n", ft_numlenu(4, 2));
	printf("%lu 1\n", ft_numlenu(0, 2));
	return (0);
}
