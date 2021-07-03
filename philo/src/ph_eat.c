#include "philosopher1.h"

static bool	can_pickup_forks(t_ph *ph)
{
	return (ph->g->forks_in_use[ph->left_fork] == AVAILABLE
		&& ph->g->forks_in_use[ph->right_fork] == AVAILABLE);
}

static t_status	start_eating(t_ph *ph)
{
	if (!can_pickup_forks(ph))
		return (FAILURE);
	ph->g->forks_in_use[ph->left_fork] = IN_USE;
	ph->g->forks_in_use[ph->right_fork] = IN_USE;
	ph->last_meal = epoch_useconds();
	pthread_mutex_lock(&ph->g->forks[ph->left_fork]);
	pthread_mutex_lock(&ph->g->forks[ph->right_fork]);
	return (SUCCESS);
}

static t_status	stop_eating(t_ph *ph)
{
	t_status	status;

	ph->g->forks_in_use[ph->left_fork] = AVAILABLE;
	ph->g->forks_in_use[ph->right_fork] = AVAILABLE;
	if (ph->g->casualty)
		status = CASUALTY;
	pthread_mutex_unlock(&ph->g->forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->g->forks[ph->right_fork]);
	return (status);
}

// This is very very bad
static t_status	attempt_eat(t_ph *ph)
{
	t_status	status;

	pthread_mutex_lock(&ph->g->lock);
	status = start_eating(ph);
	pthread_mutex_unlock(&ph->g->lock);
	if (status != SUCCESS)
		return (status);
	ph_print_status("is eating", ph);
	ph_delay(ph, ph->time_to_eat);
	pthread_mutex_lock(&ph->g->lock);
	status = stop_eating(ph);
	pthread_mutex_unlock(&ph->g->lock);
	return (status);
}

t_status	ph_consume_meal(t_ph *ph)
{
	t_status	status;

	status = FAILURE;
	while (status == FAILURE)
		status = attempt_eat(ph);
	return (status);
}
