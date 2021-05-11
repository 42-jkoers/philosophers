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
	input->must_eat_n = -1;
	if (argc == 6 && !ft_strtol_safe(&input->must_eat_n, argv[5]))
		return (exit_error("Invalid must eat n\n"));
	input->time_to_die *= 1000;
	input->time_to_eat *= 1000;
	input->time_to_sleep *= 1000;
	return (true);
}

bool	init_globals(t_globals *g, t_input input)
{
	g->forks = malloc(input.n * sizeof(t_fork));
	pthread_mutex_init(&g->forks_lock, NULL);
	pthread_mutex_init(&g->print_lock, NULL);
	g->n = input.n;
	return (true);
}

void	start_ph(t_ph *ph, size_t id, t_input input, t_globals *g)
{
	ph->id = id;
	ph->last_meal = epoch_useconds();
	if (ph->id == 0)
		ph->left_fork = input.n - 1;
	else
		ph->left_fork = ph->id - 1;
	ph->right_fork = (ph->id + 1) % input.n;
	ph->time_to_die = input.time_to_die;
	ph->time_to_eat = input.time_to_eat;
	ph->time_to_sleep = input.time_to_sleep;
	ph->must_eat_n = input.must_eat_n;
	ph->g = g;
	pthread_create(&ph->threadid, NULL, &ph_thread, (void *)(ph));
}

t_ph	*create_phs(t_input input, t_globals *g)
{
	t_ph		*phs;
	size_t		i;

	phs = malloc(input.n * sizeof(t_ph));
	i = 0;
	while (i < input.n)
	{
		start_ph(&phs[i], i, input, g);
		i++;
	}
	return (phs);
}

void	await_phs(t_ph *phs, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		pthread_join(phs[i].threadid, NULL);
		i++;
	}
}

int	main(int argc, const char **argv)
{
	t_globals	g;
	t_ph 		*phs;
	t_input		input;

	if (!parse_input(&input, argc, argv))
		return (1);
	phs = create_phs(input, &g);
	if (!phs)
		return (1);
	await_phs(phs, input.n);
	free(phs);
	return (0);
}
