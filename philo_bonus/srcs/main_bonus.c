/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:06:37 by nflan             #+#    #+#             */
/*   Updated: 2022/04/20 14:57:06 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_print_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_init_philo(t_all *g)
{
	int	i;

	i = 0;
	while (i < g->nbphilo)
	{
		g->philo[i].id = i;
		g->philo[i].x_ate = 0;
		g->philo[i].left_fork_id = i;
		g->philo[i].right_fork_id = (i + 1) % g->nbphilo;
		g->philo[i].last_meal = 0;
		g->philo[i].g = g;
		i++;
	}
	return (0);
}

int	ft_init_all(t_all *g, char **av)
{
	char	str[6] = "FORKS";

	g->nbphilo = ft_atoi(av[1]);
	g->tdie = ft_atoi(av[2]);
	g->teat = ft_atoi(av[3]);
	g->tsleep = ft_atoi(av[4]);
	g->died = 0;
	g->all_ate = 0;
	if (av[5])
		g->nbeat = ft_atoi(av[5]);
	else
		g->nbeat = -1;
	g->sem = str;
	sem_unlink(g->sem);
	g->forks = sem_open(g->sem, O_CREAT, 0660, ft_atoi(av[1]));
	if (g->forks == SEM_FAILED)
		return (ft_print_error("Sem open failed"));
	ft_init_philo(g);
	return (0);
}

int	main(int ac, char **av)
{
	t_all	g;

	if (ft_parsing(ac, av, 0))
		return (ft_print_error("Parsing error"));
	if (ft_init_all(&g, av))
		return (ft_print_error("Init error"));
	sem_close(g.forks);
	return (0);
}
