/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_includes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 18:43:52 by jkoers        #+#    #+#                 */
/*   Updated: 2020/11/04 18:46:43 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

bool	ft_includes(const char *str, char c)
{
	char	*s;

	s = (char *)str;
	while (*s != '\0')
	{
		if (*s == c)
			return (true);
		s++;
	}
	return (false);
}
