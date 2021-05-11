/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_ft_arr.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoers <jkoers@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 12:18:35 by jkoers        #+#    #+#                 */
/*   Updated: 2020/12/26 12:36:05 by jkoers        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(void)
{
	t_readbuf	buf;
	int			fd;
	char		*result;

	fd = open(".gitignore", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Can't find file\n");
		return (1);
	}
	ft_buf_init(&buf, 4096, fd);
	while (ft_buf_read(&buf))
	{
	}
	result = ft_buf_merge(&buf);
	printf("%s", result);
	free(result);
	return (0);
}
