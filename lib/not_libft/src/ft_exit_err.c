#include "libft.h"
#include <stdlib.h>

void	ft_exit_err(const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(1, msg, len);
	if (len != 0 && msg[len - 1] != '\n')
		write(1, "\n", 1);
	exit(1);
}
