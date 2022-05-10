/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_finish_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:31:57 by nflan             #+#    #+#             */
/*   Updated: 2022/05/10 15:21:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*ft_death_checker(void *arg)
{
	t_phil	*philo;

	philo = (t_phil *)arg;
	usleep(philo->g->tdie * 900);
	while (1)
	{
		sem_wait(philo->g->die);
		if (ft_get_time() > philo->next_meal)
		{
			ft_action_print(philo, 0);
			sem_post(philo->g->death);
			break ;
		}
		sem_post(philo->g->die);
		sem_wait(philo->g->die);
		if (philo->g->nbeat != -1 && philo->g->eat_count > philo->g->nbeat)
		{
			sem_post(philo->g->death);
			break ;
		}
		sem_post(philo->g->die);
		usleep(100);
	}
	return (NULL);
}

void	ft_end_philo(t_all *g, t_phil *philo)
{
	int	i;

	i = -1;
	while (++i < g->nbphilo)
		if (philo[i].pid != -1)
			kill(philo[i].pid, SIGKILL);
	sem_close(g->forks);
	sem_close(g->death);
	sem_close(g->print);
	sem_close(g->take);
	sem_close(g->die);
	free(philo);
}
