/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 15:44:03 by jkoers        #+#    #+#                 */
/*   Updated: 2020/10/30 13:35:29 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_strrchr(const char *str, char c)
{
	size_t	i;
	char	*s;

	s = (char *)str;
	i = ft_strlen(str) + 1;
	while (i > 0)
	{
		i--;
		if (s[i] == c)
			return (&s[i]);
	}
	return (NULL);
}
