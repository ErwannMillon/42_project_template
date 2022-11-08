/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:45:41 by gmillon           #+#    #+#             */
/*   Updated: 2022/11/08 02:51:45 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_state *state, t_philo *self)
{
	check_and_print(self, SLEEP_MSG, state);
	while (current_time() - self->time_finished_meal \
			< state->vars[TIME_TO_SLEEP])
		usleep(5);
	return (1);
}

int	get_forks(t_state *state, t_philo *self)
{
	const int		times_must_eat = state->vars[TIMES_MUST_EAT];
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

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
	return (1);
}

int	philo_eat(t_state *state, t_philo *self)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &state->forks[self->id];
	right_fork = &state->forks[self->right_id];
	if (!get_forks(state, self))
		return (0);
	self->time_last_ate = current_time();
	self->times_eaten++;
	while (current_time() - self->time_last_ate < state->vars[TIME_TO_EAT])
		usleep(10);
	self->time_finished_meal = current_time();
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return (1);
}

int	philo_routine(t_state *state, t_philo *self)
{
	static int	times_must_eat = -1 ;

	if (times_must_eat == -1)
		times_must_eat = state->vars[TIMES_MUST_EAT];
	if (state->vars[NUM_PHILOS] == 1)
	{
		check_and_print(self, FORK_MSG, state);
		return (0);
	}
	if (state->death || \
		(times_must_eat && self->times_eaten >= times_must_eat) \
			|| !philo_eat(state, self))
	{
		pthread_mutex_unlock(&state->forks[self->id]);
		pthread_mutex_unlock(&state->forks[self->right_id]);
		return (0);
	}
	if (state->death || \
		(times_must_eat && self->times_eaten > times_must_eat) \
			|| !philo_sleep(state, self))
		return (0);
	check_and_print(self, THINK_MSG, state);
	return (1);
}

void	*philo_main(void *arg)
{
	t_philo			*self;
	int				id;
	t_state			*state;

	state = (t_state *)arg;
	id = state->thread_id;
	self = &state->philo_arr[id];
	self->id = id;
	if (id == 1)
		state->start_time = current_time();
	while (!state->death && \
		(!state->vars[TIMES_MUST_EAT] || \
		(self->times_eaten < state->vars[TIMES_MUST_EAT])))
	{
		if (!philo_routine(state, self))
			break ;
	}
	return (NULL);
}
