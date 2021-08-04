#include "philosopher1.h"
#include "not_libft/include/not_libft.h"

t_useconds	time_until_ded(const t_ph *ph)
{
	const t_useconds	since_last_meal = epoch_useconds() - ph->last_meal;

	return (ph->time_to_die - ft_minu(ph->time_to_die, since_last_meal));
}

bool	stay_alive(const t_ph *ph)
{
	return (ph->time_to_eat + ph->time_to_sleep < ph->time_to_die
		&& ph->time_to_eat * 2 < ph->time_to_die);
}
