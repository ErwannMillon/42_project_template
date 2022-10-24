/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:45:41 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/24 18:57:28 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_state *state, t_philo *self)
{
	int	wait;
	pthread_mutex_lock(&state->writing);
	// printf("%d sleep\n", self->id + 1);
	pthread_mutex_unlock(&state->writing);
	check_and_print(self, SLEEP_MSG, state);
	// usleep(state->vars[TIME_TO_SLEEP] * 1000);
	wait = 0;
	while (!state->death && wait < state->vars[TIME_TO_EAT] * 100) 
	{
		usleep(10);
		wait++;
	}
	return (1);
}

int	philo_eat(t_state *state, t_philo *self)
{
	const int		times_must_eat = state->vars[TIMES_MUST_EAT];
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				wait;

	left_fork = &state->forks[self->id];
	right_fork = &state->forks[self->right_id];
	if (state->death || (times_must_eat && self->times_eaten >= times_must_eat) \
			|| pthread_mutex_lock(left_fork))
		return (0);
	check_and_print(self, FORK_MSG, state);
	if (state->death || (times_must_eat && self->times_eaten >= times_must_eat) \
			|| pthread_mutex_lock(right_fork))
	{
		pthread_mutex_unlock(left_fork);
		return (0);
	}
	if (state->death || !check_and_print(self, FORK_MSG, state) \
		|| !check_and_print(self, EAT_MSG, state))
	{

		pthread_mutex_unlock(right_fork);
		pthread_mutex_unlock(left_fork);
		return (0);
	}
	self->time_last_ate = current_time();
	wait = 0;
	while (!state->death && wait < state->vars[TIME_TO_EAT] * 100) 
	{
		usleep(10);
		wait++;
	}
	// usleep(state->vars[TIME_TO_EAT] * 1000);
	self->times_eaten++;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return (1);
}

int	philo_routine(t_state *state, t_philo *self)
{
	const int	times_must_eat = state->vars[TIMES_MUST_EAT];

	if (state->vars[NUM_PHILOS] == 1)
	{
		check_and_print(self, FORK_MSG, state);
		return (0);
	}
	if (state->death || \
		(times_must_eat && self->times_eaten >= times_must_eat) \
			|| !philo_eat(state, self))
		return (0);
	if (state->death || \
		(times_must_eat && self->times_eaten >= times_must_eat) \
			|| !philo_sleep(state, self))
		return (0);
	check_and_print(self, THINK_MSG, state);
	return (1);
}

void	*philo_main(void *arg)
{
	t_philo			*self;
	int				id;
	int				i;
	t_state			*state;

	state = (t_state *)arg;
	id = state->thread_id;
	i = 0;
	self = &state->philo_arr[id];
	self->id = id;
	while (!state->death && !self->error)
	{
		if (!state->death && \
			(!state->vars[TIMES_MUST_EAT] || \
			(i < state->vars[TIMES_MUST_EAT])))
		{
			if (!philo_routine(state, self))
				break ;
			i++;
		}
		else
			break ;
	}
	return (NULL);
}
