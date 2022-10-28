/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 03:38:15 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/28 14:07:03 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(int *vars, t_state *state)
{
	const t_philo	*philo_arr = state->philo_arr;
	int				i;

	i = 0;
	while (i < vars[NUM_PHILOS])
	{
		if (pthread_join(philo_arr[i].philo_thread, NULL))
			return (0);
		i++;
	}
	if (!state->death && state->vars[TIMES_MUST_EAT] > 0)
		printf("all philos have eaten %d meals", state->vars[TIMES_MUST_EAT]);
	return (1);
}

pthread_mutex_t	*make_fork_arr(int *vars)
{
	int				i;
	pthread_mutex_t	*fork_arr;

	i = 0;
	fork_arr = malloc(vars[NUM_PHILOS] * sizeof(pthread_mutex_t));
	while (i < vars[NUM_PHILOS])
	{
		if (pthread_mutex_init(&fork_arr[i], NULL))
			handle_error(vars);
		i++;
	}
	return (fork_arr);
}
