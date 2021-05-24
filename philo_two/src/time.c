#include "philosopher1.h"

t_time_useconds	epoch_useconds(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void	usleep_accurate(t_useconds time)
{
	const t_useconds	entry = epoch_useconds();

	while ((epoch_useconds() - entry) < time)
		usleep(200);
}
