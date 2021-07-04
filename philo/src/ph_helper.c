#include "philosopher1.h"

t_useconds	ph_life_expectancy(const t_ph *ph)
{
	t_useconds	since_last_meal;

	since_last_meal = epoch_useconds() - ph->last_meal;
	if (since_last_meal > ph->time_to_die)
		return (0);
	else
		return (ph->time_to_die - since_last_meal);
}
