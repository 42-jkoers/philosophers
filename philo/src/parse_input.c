#include "philosopher1.h"
#include <limits.h>
#include "not_libft/include/not_libft.h"

bool	exit_error(const char *str)
{
	printf("%s", str);
	return (false);
}

bool	parse_input(t_input *input, int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
		return (exit_error("Err: args\n"));
	if (!ft_strtoul_clamp(&input->n, argv[1], 0, ULONG_MAX * 0.001))
		return (exit_error("Invalid number of phs\n"));
	if (!ft_strtoul_clamp(&input->time_to_die, argv[2], 0, ULONG_MAX * 0.001))
		return (exit_error("Invalid time to die\n"));
	if (!ft_strtoul_clamp(&input->time_to_eat, argv[3], 0, ULONG_MAX * 0.001))
		return (exit_error("Invalid time to eat\n"));
	if (!ft_strtoul_clamp(&input->time_to_sleep, argv[4], 0, ULONG_MAX * 0.001))
		return (exit_error("Invalid time to sleep\n"));
	if (argc == 6)
	{
		if (!ft_strtol_clamp(&input->must_eat_n, argv[5], 0, LONG_MAX))
			return (exit_error("Invalid must eat n\n"));
	}
	else
		input->must_eat_n = -1;
	input->time_to_die *= 1000;
	input->time_to_eat *= 1000;
	input->time_to_sleep *= 1000;
	return (true);
}
