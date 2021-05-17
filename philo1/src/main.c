#include "not_libft/include/not_libft.h"
#include "philosopher1.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
	if (argc == 6 && !ft_strtol_safe(&input->must_eat_n, argv[5]))
		return (exit_error("Invalid must eat n\n"));
	else
		input->must_eat_n = -1;
	input->time_to_die *= 1000;
	input->time_to_eat *= 1000;
	input->time_to_sleep *= 1000;
	return (true);
}

bool	init_globals(t_globals *g, t_input input)
{
	size_t	i;

	g->forks = malloc(input.n * sizeof(t_fork));
	i = 0;
	while (i < input.n)
	{
		g->forks[i] = AVAILABLE;
		i++;
	}
	if (pthread_mutex_init(&g->lock, NULL))
		return (exit_error("Create mutex lock failed"));
	g->n = input.n;
	g->casualty = false;
	return (true);
}


int	main(int argc, const char **argv)
{
	t_globals	g;
	t_ph		*phs;
	t_input		input;

	if (!parse_input(&input, argc, argv))
		return (1);
	if (!init_globals(&g, input))
		return (1);
	phs = phs_create(input, &g);
	if (!phs)
		return (1);
	g.phs = phs;
	phs_start(phs, g.n);
	phs_await(phs, input.n);
	free(phs);
	return (0);
}
