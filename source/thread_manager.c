#include "miniRT.h"

void	init_cpu_task(t_pixel_task *pxt, int nb, t_var *m)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pxt[i].m = m;
		pxt[i].i = -1;
		pxt[i].j = -1;
		pthread_mutex_init(&pxt[i].mut, NULL);
		pthread_mutex_init(&pxt[i].sleep, NULL);
		pthread_mutex_lock(&pxt[i].sleep);
		i++;
	}
}

void	thread_launcher(t_var *m, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_create(&m->cpu[i], NULL, thread_routine, &m->cpu_task[i]);
		i++;
	}
}

void	init_shared_data(t_var *m)
{
	m->nb_cpu = sysconf(_SC_NPROCESSORS_ONLN);
	m->cpu = malloc(sizeof(pthread_t) * m->nb_cpu - 1);
	m->cpu_task = malloc(sizeof(t_pixel_task) * m->nb_cpu - 1);
	init_cpu_task(m->cpu_task, m->nb_cpu - 1, m);
	thread_launcher(m, m->nb_cpu - 1);
	dprintf(1, "nb of cpu %d\n", m->nb_cpu);
}

void	found_available_thread(int i, int j, t_var *m)
{
	int	loop;

	loop = 0;
	while (1)
	{
		if (loop == m->nb_cpu - 1)
			loop = 0;
		pthread_mutex_lock(&m->cpu_task[loop].mut);
		if (m->cpu_task[loop].i == -1)
		{
			m->cpu_task[loop].i = i;
			m->cpu_task[loop].j = j;
			pthread_mutex_unlock(&m->cpu_task[loop].mut);
			return ;
		}
		pthread_mutex_unlock(&m->cpu_task[loop].mut);
		loop++;
	}
}

void	thread_manager(t_var *m)
{
	int	i;
	int	j;
	int	k;

	k = -1;
	while (++k < m->nb_cpu -1)
		pthread_mutex_unlock(&m->cpu_task[k].sleep);
	i = -1;
	while (++i < m->win.height)
	{
		j = -1;
		while (++j < m->win.lenght)
			found_available_thread(i, j, m);
	}
	while (--k <= 0)
		pthread_mutex_lock(&m->cpu_task[k].sleep);
}