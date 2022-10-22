/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:07:08 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/22 03:47:40 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

int	check_and_print(t_philo *philo, char *msg, t_state *state)
{
	long long	timestamp_ms;

	timestamp_ms = current_time() - state->start_time;
	if (state->death || philo->error)
		return (0);
	if (pthread_mutex_lock(&state->writing))
	{
		philo->error = 1;
		return (0);
	}
	printf(TIMESTAMP_MSG, timestamp_ms);
	printf(msg, philo->id + 1);
	pthread_mutex_unlock(&state->writing);
	return (1);
}
