/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:50 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/24 18:19:48 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_state *state)
{
	free(state->vars);
	free(state->philo_arr);
	free(state->forks);
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
	usleep(10);
	checker(state);
	usleep(100);
	join_threads(vars, state);
	// destroy_mutexes(state);
	cleanup(state);
	return (0);
}
