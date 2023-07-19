#include "miniRT.h"

void	*thread_routine(void *arg)
{
	t_pixel_task	*p;
	t_var			*m;
	t_vec			tmp;

	p = arg;
	m = p->m;
	while (1)
	{
		pthread_mutex_lock(&p->sleep);
		pthread_mutex_unlock(&p->sleep);
		pthread_mutex_lock(&p->mut);
		if (p->i != -1)
		{
			if (p->i == -2)
			{
				pthread_mutex_unlock(&p->mut);
				return (NULL);
			}
			pthread_mutex_unlock(&p->mut);
			ft_mat_vec(m->vec[p->i * m->win.lenght + p->j], m->mat_rot, &tmp);
			ft_pixel_put(m, p->i, p->j, tmp);
			pthread_mutex_lock(&p->mut);
			p->i = -1;
			pthread_mutex_unlock(&p->mut);
		}
		else
			pthread_mutex_unlock(&p->mut);
	}
}