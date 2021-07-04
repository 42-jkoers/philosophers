#include "philosopher1.h"
#include <sys/time.h>

void	ph_print_status(const char *status, const t_ph *ph)
{
	pthread_mutex_lock(&ph->g->lock);
	if (!ph->g->casualty)
		printf("%lu %3lu %s\n", epoch_useconds() / 1000, ph->id + 1, status);
	pthread_mutex_unlock(&ph->g->lock);
}

// Only print that the current ph has died their the first one
void	ph_die(t_ph *ph)
{
	pthread_mutex_lock(&ph->g->lock);
	if (!ph->g->casualty)
	{
		printf("%lu %3lu has died\n", epoch_useconds() / 1000, ph->id + 1);
		ph->g->casualty = true;
	}
	pthread_mutex_unlock(&ph->g->lock);
}

void	ph_delay(t_ph *ph, t_useconds time)
{
	const t_useconds	life_expectancy = ph_life_expectancy(ph);
	const t_useconds	stop_at = epoch_useconds() + time;
	t_useconds			now;

	if (ph->g->casualty)
		return ;
	if (life_expectancy < time)
	{
		usleep_accurate(life_expectancy);
		ph_die(ph);
		return ;
	}
	while (true)
	{
		now = epoch_useconds();
		if (now >= stop_at)
			return ;
		if (stop_at - now < CHECK_PH_DIED_INTERVAL)
		{
			usleep_accurate(stop_at - now);
			return ;
		}
		else
			usleep(CHECK_PH_DIED_INTERVAL);
	}
}


void	*ph_thread(void *philosoper)
{
	t_ph	*ph;
	long	meals;

	ph = (t_ph *)philosoper;
	meals = 0;
	while (ph->must_eat_n == -1 || meals < ph->must_eat_n)
	{
		if (ph_consume_meal(ph) == CASUALTY)
			return (NULL);
		ph_print_status("is sleeping", ph);
		ph_delay(ph, ph->time_to_sleep);
		ph_print_status("is thinking", ph);
		meals++;
	}
	return (NULL);
}
