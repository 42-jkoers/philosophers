#include "philosopher1.h"
#include <sys/time.h>

void	print_status(const char *status, const t_ph *ph)
{
	pthread_mutex_lock(&ph->g->print_lock);
	printf("%lu %3lu %s\n", epoch_useconds() / 1000, ph->id + 1, status);
	pthread_mutex_unlock(&ph->g->print_lock);
}


t_status	ph_attempt_eat(t_ph *ph)
{
	bool	can_eat;

	pthread_mutex_lock(&ph->g->forks_lock);
	can_eat = ph->g->forks[ph->left_fork] == AVAILABLE &&ph->g->forks[ph->right_fork] == AVAILABLE;
	if (can_eat)
	{
		ph->g->forks[ph->left_fork] = IN_USE;
		ph->g->forks[ph->right_fork] = IN_USE;
		ph->last_meal = epoch_useconds();
		pthread_mutex_unlock(&ph->g->forks_lock);
		print_status("is eating", ph);
		usleep(ph->time_to_eat);
		pthread_mutex_lock(&ph->g->forks_lock);
		ph->g->forks[ph->left_fork] = AVAILABLE;
		ph->g->forks[ph->right_fork] = AVAILABLE;
	}
	pthread_mutex_unlock(&ph->g->forks_lock);
	return (can_eat);
}

void	ph_sleep(const t_ph *ph)
{
	print_status("is sleeping", ph);
	usleep(ph->time_to_sleep);
}

// void	ph_think(t_ph *ph)
// {
// 	print_status("is thinking", ph);
// 	usleep(ph->time_to_t);
// }

void	*ph_thread(void *philosoper)
{
	const t_ph	*ph = (t_ph *)philosoper;

	// while (true)
	// {
	// 	if (ph_attempt_eat(ph) == SUCCESS)
	// }
	ph_sleep(ph);
	return (NULL);
}
