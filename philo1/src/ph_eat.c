#include "philosopher1.h"

static bool	can_pickup_forks(t_ph *ph)
{
	return (ph->g->forks[ph->left_fork] == AVAILABLE
		&& ph->g->forks[ph->right_fork] == AVAILABLE);
}

static t_status	attempt_eat(t_ph *ph)
{
	t_status	status;

	pthread_mutex_lock(&ph->g->lock);
	if (!can_pickup_forks(ph))
	{
		pthread_mutex_unlock(&ph->g->lock);
		return (FAILURE);
	}
	ph->g->forks[ph->left_fork] = IN_USE;
	ph->g->forks[ph->right_fork] = IN_USE;
	ph->last_meal = epoch_useconds();
	pthread_mutex_unlock(&ph->g->lock);
	ph_print_status("is eating", ph);
	ph_delay(ph, ph->time_to_eat);
	pthread_mutex_lock(&ph->g->lock);
	ph->g->forks[ph->left_fork] = AVAILABLE;
	ph->g->forks[ph->right_fork] = AVAILABLE;
	if (ph->g->casualty)
		status = CASUALTY;
	pthread_mutex_unlock(&ph->g->lock);
	return (status);
}

void	ph_consume_meal(t_ph *ph)
{
	while (attempt_eat(ph) == FAILURE)
	{
	}
}
