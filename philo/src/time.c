#include "philosopher1.h"
#include "not_libft/include/not_libft.h"

t_time_useconds	epoch_useconds(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000 + now.tv_usec);
}

void	usleep_accurate(t_useconds time)
{
	const t_useconds	stop_at = epoch_useconds() + time;
	t_useconds			now;

	while (true)
	{
		now = epoch_useconds();
		if (now >= stop_at)
			return ;
		usleep(ft_minu(stop_at - now, 400));
	}
}
