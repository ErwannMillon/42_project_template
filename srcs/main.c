/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:50 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/28 14:51:43 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_state *state)
{
	free(state->vars);
	free(state->philo_arr);
	free(state->forks);
	free(state);
}

void	handle_error(int *vars)
{
	free(vars);
	printf("Error\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	int		*vars;
	t_state	*state;

	vars = initialize(argc, argv);
	if (!vars)
		return (0);
	state = create_state(vars);
	while (all_alive(state))
		continue ;
	// printf("return");
	// while (!state->death)
	usleep(100);
	join_threads(vars, state);
	pthread_mutex_unlock(&state->writing);
	// destroy_mutexes(state);
	cleanup(state);
	return (0);
}
