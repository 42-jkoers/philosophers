#include "philosopher1.h"

static bool	can_pickup_forks(t_ph *ph)
{
	const long	left = ph->g->forks[ph->left_fork];
	const long	right = ph->g->forks[ph->right_fork];

	if (left < 0 && right < 0
		&& !(left == -(ph->id + 1) && right == -(ph->id + 1)))
	{
		ph->g->forks[ph->left_fork] = ph->id + 1;
		ph->g->forks[ph->right_fork] = ph->id + 1;
		return (true);
	}
	return (false);
}

static t_status	start_eating(t_ph *ph)
{
	if (!can_pickup_forks(ph))
		return (FAILURE);
	ph_print_status("is eating", ph);
	ph->last_meal = epoch_useconds();
	return (SUCCESS);
}

static void	stop_eating(t_ph *ph)
{
	ph->g->forks[ph->left_fork] = -(ph->id + 1);
	ph->g->forks[ph->right_fork] = -(ph->id + 1);
}

// This is very very bad
static t_status	attempt_eat(t_ph *ph)
{
	t_status	status;

	pthread_mutex_lock(&ph->g->lock);
	pthread_mutex_lock(&ph->g->locks[ph->left_fork]);
	pthread_mutex_lock(&ph->g->locks[ph->right_fork]);
	status = start_eating(ph);
	pthread_mutex_unlock(&ph->g->locks[ph->left_fork]);
	pthread_mutex_unlock(&ph->g->locks[ph->right_fork]);
	pthread_mutex_unlock(&ph->g->lock);
	if (status != SUCCESS)
		return (status);
	if (ph->g->casualty)
		return (CASUALTY);
	ph_delay(ph, ph->time_to_eat);
	pthread_mutex_lock(&ph->g->lock);
	pthread_mutex_lock(&ph->g->locks[ph->left_fork]);
	pthread_mutex_lock(&ph->g->locks[ph->right_fork]);
	stop_eating(ph);
	pthread_mutex_unlock(&ph->g->locks[ph->left_fork]);
	pthread_mutex_unlock(&ph->g->locks[ph->right_fork]);
	pthread_mutex_unlock(&ph->g->lock);
	return (SUCCESS);
}

t_status	ph_consume_meal(t_ph *ph)
{
	t_status	status;
	double		search_delay;

	search_delay = 200;
	usleep(300);
	while (true)
	{
		status = attempt_eat(ph);
		if (status != FAILURE)
			return (status);
		if (!time_until_ded(ph))
		{
			ph_die(ph);
			return (CASUALTY);
		}
		usleep((t_useconds)search_delay);
		search_delay *= 0.99;
	}
	return (status);
}
