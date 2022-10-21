/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:56:50 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/21 13:33:40 by gmillon          ###   ########.fr       */
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
	usleep(1000);
	checker(&state);
	// // ft_printf("returned");
	// // usleep(2000000);
	// join_threads(vars, &state);
	return (0);

}
