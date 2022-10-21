/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:56:08 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/22 01:08:56 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	all_alive(t_state *state)
{
	int				i;
	long long	time_diff;
	const t_philo	*philo_arr;

	philo_arr = state->philo_arr;	
	i = 0;	
	while (i < state->vars[NUM_PHILOS])
	{
		time_diff = current_time() - state->philo_arr[i].time_last_ate;
		// printf("%d, timediff %lu\n", i, time_diff);
		// printf("%lu, timeLast ate\n", philo_arr[i].time_last_ate);
		// printf("%lu, currenttime\n", current_time());
		if (time_diff > state->vars[TIME_TO_DIE])
		{
			printf("%lld ms %d has died", current_time() - state->start_time, i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_mutexes(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->vars[NUM_PHILOS])
	{
		if (pthread_mutex_destroy(&state->philo_arr[i].fork))
			ft_printf("error");
		i++;
	}
	return ;
}

void	checker(t_state *state)
{
	while (all_alive(state))
		continue ;
	state->death = 1;
	// destroy_mutexes(state);
	// printf("death");
	return ;
}
