/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:56:47 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/18 15:12:46 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*initialize(int argc, char **argv)
{
	int		i;
	int		*vars;

	i = 1;
	if (!(argc == 5 || argc == 6 ))
		return (0);
	vars = malloc(6 * sizeof(int));
	while (i < argc)
	{
		if (!ft_string_is_num(argv[i]))
		{
			ft_printf("Error\n");
			exit(0);
		}
		vars[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	if (i == 4)
		vars[5] = 0;
	return (vars);
}

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
	return (1);
}

t_state	init_state_vars(t_philo *philos, int *vars)
{
	t_state	state;

	state.philo_arr = philos;
	state.death = 0;
	state.start_time = current_time();
	ft_printf("state.start_time: %d\n", state.start_time);
	state.vars = vars;
	if (pthread_mutex_init(&state.writing, NULL))
		handle_error(vars);
	return (state);
}
void	init_philo_vars(int i, t_philo *philos, t_state state, int *vars)
{
	philos[i].right_id = ((i + vars[NUM_PHILOS]) + 1) % vars[NUM_PHILOS];
	philos[i].left_id = ((i + vars[NUM_PHILOS]) - 1) % vars[NUM_PHILOS];
	philos[i].times_eaten = 0;
	philos[i].error = 0;
	philos[i].time_to_death = vars[TIME_TO_DIE];
	philos[i].time_last_ate = state.start_time;
}

t_state	create_state(int *vars)
{
	t_state	state;
	t_philo	*philos;
	int		i;
	int		fork_count;

	i = 0;
	philos = malloc(sizeof(t_philo) * vars[NUM_PHILOS]);
	state = init_state_vars(philos, vars);
	while (i < vars[NUM_PHILOS])
	{
		state.thread_id = i;
		init_philo_vars(i, philos, state, vars);
		if (pthread_mutex_init(&philos[i].fork, NULL))
			handle_error(vars);
		if (pthread_create(&philos[i].philo_thread, NULL,
				philo_main, &state))
			handle_error(vars);
		usleep(100000);
		i++;
	}
	return (state);
}
