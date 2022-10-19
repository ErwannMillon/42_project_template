/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:56:08 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/18 12:17:10 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	all_alive(t_state *state)
{
	int				i;
	unsigned long	time_diff;
	const t_philo	*philo_arr;

	philo_arr = state->philo_arr;	
	i = 0;	
	while (i < state->vars[NUM_PHILOS])
	{
		time_diff = current_time() - philo_arr[i].time_last_ate;
		// printf("%d, timediff %lu\n", i, time_diff);
		// printf("%lu, timeLast ate\n", philo_arr[i].time_last_ate);
		// printf("%lu, currenttime\n", current_time());
		if (time_diff > state->vars[TIME_TO_DIE])
		{
			printf("%d has died", i);
			return (0);
		}
		i++;
	}
	return (1);
}

void	checker(t_state *state)
{
	while (all_alive(state))
		continue ;
	state->death = 1;
	// printf("death");
	return ;
}
