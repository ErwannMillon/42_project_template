/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:56:08 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/28 15:08:16 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	times_eaten_checker(t_state *state, int i, long long time_diff)
{
	const int		times_must_eat = state->vars[TIMES_MUST_EAT];

	if (time_diff > state->vars[TIME_TO_DIE])
	{
		if (!times_must_eat)
		{
			state->death = 1;
			pthread_mutex_lock(&state->writing);
			printf("%lld ms %d has died", \
					current_time() - state->start_time, i + 1);
			usleep(10);
		}
		if (times_must_eat && state->philo_arr[i].times_eaten < times_must_eat)
		{
			state->death = 1;
			pthread_mutex_lock(&state->writing);
			printf("%lld ms %d has died", \
					current_time() - state->start_time, i + 1);
			usleep(10);
		}
		return (0);
	}
	return (1);
}

int	all_alive(t_state *state)
{
	int				i;
	long long		time_diff;

	i = 0;
	while (i < state->vars[NUM_PHILOS])
	{
		time_diff = current_time() - state->philo_arr[i].time_last_ate;
		if (!times_eaten_checker(state, i, time_diff))
			return (0);
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
		pthread_mutex_destroy(&state->philo_arr[i].fork);
		i++;
	}
	return ;
}

void	checker(t_state *state)
{
	while (all_alive(state))
		continue ;
	return ;
}
