/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:50 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/13 21:44:00 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_error(int *vars)
{
	free(vars);
	printf("Error\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	int		*vars;
	t_state	state;

	vars = initialize(argc, argv);
	state = create_state(vars);
	if (!pthread_mutex_lock(&state.philo_arr[0].fork))
		printf("AAAAAAAAAAAAAAAAAAAAAa");
	usleep(1000);
	join_threads(vars, &state);
	return (0);

}
