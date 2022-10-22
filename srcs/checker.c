/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:56:08 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/22 03:20:33 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_times_eaten(t_state *state, int i, long long time_diff)
{
	const int		times_must_eat = state->vars[TIMES_MUST_EAT];
	const t_philo	*philo_arr;

	philo_arr = state->philo_arr;
	if (time_diff > state->vars[TIME_TO_DIE])
	{
		if (times_must_eat && state->philo_arr[i].times_eaten < times_must_eat)
		{
			printf("%lld ms %d has died", \
					current_time() - state->start_time, i + 1);
			state->death = 1;
			return (0);
		}		
		else if (!times_must_eat)
		{
			printf("%lld ms %d has died", \
					current_time() - state->start_time, i + 1);
			state->death = 1;
			return (0);
		}
	}
	return (1);
}

int	all_alive(t_state *state)
{
	int				i;
	const int		times_must_eat = state->vars[TIMES_MUST_EAT];
	long long		time_diff;
	t_philo			*philo_arr;
	int				num_sated;

	philo_arr = state->philo_arr;
	i = 0;
	num_sated = 0;
	while (i < state->vars[NUM_PHILOS])
	{
		time_diff = current_time() - state->philo_arr[i].time_last_ate;
		if (times_must_eat && state->philo_arr[i].times_eaten >= times_must_eat)
			num_sated++;
		if (!check_times_eaten(state, i, time_diff))
			return (0);
		i++;
	}
	if (num_sated && num_sated == state->vars[NUM_PHILOS] - 1)
		return (0);
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
	state->death = 1;
	return ;
}
