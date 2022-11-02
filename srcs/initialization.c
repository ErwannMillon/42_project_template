/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:56:47 by gmillon           #+#    #+#             */
/*   Updated: 2022/11/02 20:43:02 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*initialize(int argc, char **argv)
{
	int		i;
	int		*vars;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("Error, must provide 4 or 5 args\n");
		return (0);
	}
	vars = malloc(6 * sizeof(int));
	while (i < argc)
	{
		vars[i - 1] = ft_atoi(argv[i]);
		if (!handle_input_errors(argv, vars, i))
		{
			free(vars);
			return (0);
		}
		i++;
	}
	if (argc == 5)
		vars[4] = 0;
	return (vars);
}

t_state	*init_state_vars(t_philo *philos, int *vars)
{
	t_state	*state;

	state = malloc(sizeof(t_state));
	state->forks = make_fork_arr(vars);
	state->philo_arr = philos;
	state->death = 0;
	state->finished = 0;
	state->ready = 0;
	state->start_time = current_time();
	state->vars = vars;
	if (pthread_mutex_init(&state->writing, NULL))
		handle_error(vars);
	return (state);
}

void	init_philo_vars(int i, t_philo *philos, \
						t_state *state, int *vars)
{
	philos[i].right_id = ((i + vars[NUM_PHILOS]) + 1) % vars[NUM_PHILOS];
	philos[i].left_id = ((i + vars[NUM_PHILOS]) - 1) % vars[NUM_PHILOS];
	philos[i].times_eaten = 0;
	philos[i].error = 0;
	philos[i].time_to_death = vars[TIME_TO_DIE];
	philos[i].time_last_ate = state->start_time;
}

t_state	*create_state(int *vars)
{
	t_state	*state;
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	state = init_state_vars(philos, vars);
	while (i < vars[NUM_PHILOS])
	{
		state->thread_id = i;
		init_philo_vars(i, philos, state, vars);
		if (pthread_create(&philos[i].philo_thread, NULL,
				philo_main, state))
			handle_error(vars);
		usleep(100);
		i++;
	}
	return (state);
}
