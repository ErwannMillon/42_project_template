/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:56:47 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/22 00:59:44 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_sleep(t_state *state, t_philo *self)
{
	check_and_print(self, SLEEP_MSG, state);
	usleep(state->vars[TIME_TO_SLEEP] * 1000);
	return (1);
}

int	philo_eat(t_state *state, t_philo *self)
{
	t_philo	*philo_arr = state->philo_arr;
	pthread_mutex_t *left_fork = &state->forks[self->id];
	pthread_mutex_t *right_fork = &state->forks[self->right_id];

	// if (state->death || pthread_mutex_lock(&left_fork))
	// {
	// 	printf("Errorleft");
	// }
	if (pthread_mutex_lock(left_fork))
	{
		printf("Errorleft");
	}
	if (pthread_mutex_lock(right_fork))
		printf("Errorright");
	check_and_print(self, FORK_MSG, state);
	if (state->death || !check_and_print(self, FORK_MSG, state) \
		|| !check_and_print(self, EAT_MSG, state))
		return (0);
	self->time_last_ate = current_time();
	usleep(state->vars[TIME_TO_SLEEP] * 1000);
	self->times_eaten++;
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return (1);
}

int	philo_routine(t_state *state, t_philo *self)
{
	if (state->death || !philo_eat(state, self))
		return (0);
	if (state->death || !philo_sleep(state, self))
		return (0);
	check_and_print(self, THINK_MSG, state);
	return (1);
}

void	*philo_main(t_state *state)
{
	const int		id = state->thread_id;
	t_philo			self;
	int				i;

	i = 0;
	self = state->philo_arr[state->thread_id];
	self.id = id;
	ft_printf("id: %d\n", id);
	while (!state->death && !self.error)
	{
		if (!state->death &&
			(!state->vars[TIMES_MUST_EAT] \
			|| (i < state->vars[TIMES_MUST_EAT])))
		{
			philo_routine(state, &self);
			i++;
		}
		else
			break ;
	}
	return (NULL);
}
