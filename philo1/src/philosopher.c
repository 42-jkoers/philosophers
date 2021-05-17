#include "philosopher1.h"
#include <sys/time.h>

void	ph_print_status(const char *status, const t_ph *ph)
{
	pthread_mutex_lock(&ph->g->lock);
	if (!ph->g->casualty)
		printf("%lu %3lu %s\n", epoch_useconds() / 1000, ph->id + 1, status);
	pthread_mutex_unlock(&ph->g->lock);
}

void	ph_die(t_ph *ph)
{
	pthread_mutex_lock(&ph->g->lock);
	if (!ph->g->casualty)
	{
		printf("%lu %3lu %s\n", epoch_useconds() / 1000, ph->id + 1, "has died");
		ph->g->casualty = true;
	}
	pthread_mutex_unlock(&ph->g->lock);
}

void	ph_delay(t_ph *ph, t_useconds time)
{
	const t_useconds	interval = 7000;
	const t_useconds	life_expectancy = ph_life_expectancy(ph);
	const bool			will_die = life_expectancy <= time;

	if (life_expectancy < time)
		time = life_expectancy;
	while (time > interval)
	{
		usleep_accurate(interval);
		if (casualty(ph))
			return ;
		time -= interval;
	}
	usleep_accurate(time);
	if (will_die)
		return (ph_die(ph));
}

void	ph_sleep(t_ph *ph)
{
	ph_print_status("is sleeping", ph);
	ph_delay(ph, ph->time_to_sleep);
}

void	*ph_thread(void *philosoper)
{
	t_ph		*ph = (t_ph *)philosoper;
	long		meals;

	meals = 0;
	while (ph->must_eat_n == -1 || meals < ph->must_eat_n)
	{
		ph_consume_meal(ph);
		ph_sleep(ph);
		ph_print_status("is thinking", ph);
		if (casualty(ph))
			return (NULL);
		meals++;
	}
	return (NULL);
}
