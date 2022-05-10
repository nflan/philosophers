/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/10 16:53:59 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_death_checker(t_all *g, t_phil *phil, int i)
{
	usleep(g->tdie * 500);
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&g->meal_check);
		while (++i < g->nbphilo && !g->died)
		{
			usleep(150);
			if (ft_time_check(phil[i].last_meal, ft_get_time()) > g->tdie)
			{
				g->died = 1;
				ft_action_print(g, i, " died\n", 1);
			}
		}
		if (g->died)
		{
			pthread_mutex_unlock(&g->meal_check);
			break ;
		}
		pthread_mutex_unlock(&g->meal_check);
		i = 0;
		pthread_mutex_lock(&g->meal_check);
		while (g->nbeat != -1 && i < g->nbphilo && phil[i].x_ate >= g->nbeat)
			i++;
		if (i == g->nbphilo)
		{
			g->all_ate = 1;
			break ;
		}
		pthread_mutex_unlock(&g->meal_check);
	}
}

void	ft_end_philo(t_all *g, t_phil *phil)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
	{
		if (pthread_mutex_destroy(&g->forks[i]))
		{
			pthread_mutex_unlock(&g->forks[i]);
			pthread_mutex_destroy(&g->forks[i]);
		}
	}
//	pthread_mutex_unlock(&g->lock);
	i = -1;
	while (++i < g->nbphilo)
		pthread_join(phil[i].thread_id, NULL);
	pthread_mutex_destroy(&g->lock);
}
