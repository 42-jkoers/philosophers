#include "philosopher1.h"
#include <sys/time.h>
#include "../lib/not_libft/include/not_libft.h"

unsigned long	since_start_ms(const t_ph *ph)
{
	const t_useconds	time = epoch_useconds() - ph->g->start_program;

	return ((time + 500) / 1000);
}

void	ph_print_status(const char *status, const t_ph *ph)
{
	if (!ph->g->casualty)
		printf("%5lu %3lu %s\n", since_start_ms(ph), ph->id + 1, status);
}

// Only print that the current ph has died their the first one
void	ph_die(t_ph *ph)
{
	pthread_mutex_lock(&ph->g->lock);
	if (!ph->g->casualty)
	{
		printf("%5lu %3lu has died\n", since_start_ms(ph), ph->id + 1);
		ph->g->casualty = true;
	}
	pthread_mutex_unlock(&ph->g->lock);
}

void	ph_delay(t_ph *ph, t_useconds time)
{
	const t_useconds	life_expectancy = time_until_ded(ph);
	const t_useconds	stop_at =
							epoch_useconds() + ft_minu(time, life_expectancy);
	t_useconds			now;

	while (true)
	{
		if (ph->g->casualty)
			return ;
		now = epoch_useconds();
		if (now >= stop_at)
			return ;
		if (stop_at - now < CHECK_PH_DIED_INTERVAL)
		{
			usleep_accurate(stop_at - now);
			break ;
		}
		else
			usleep(CHECK_PH_DIED_INTERVAL);
	}
	if (time >= life_expectancy)
		ph_die(ph);
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
	printf("%lu done\n", ph->id);
	return (NULL);
}
