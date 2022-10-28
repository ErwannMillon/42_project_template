/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:01:49 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/28 15:09:46 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	check_int_lim(char *arg)
{
	int			check;
	int			check_copy;
	int			s_len;
	int			i;
	int			minus;

	minus = 0;
	i = 0;
	check = ft_atoi(arg);
	check_copy = check;
	s_len = ft_strlen(arg);
	if (arg[0] == '+' || arg[0] == '-')
		s_len--;
	if (arg[0] == '-')
		minus = -1;
	while (check)
	{
		i++;
		check /= 10;
	}
	if (arg[0] != '0' && (i != s_len || ft_atoi(arg) != check_copy
			|| (minus && check_copy > 0) || (!minus && check_copy < 0)))
		return (0);
	return (1);
}

int	handle_input_errors(char **argv, int *vars, int i)
{
	if (!ft_string_is_num(argv[i]))
	{
		printf("Error, args must be integers\n");
		return (0);
	}
	if (i == 1 && vars[0] < 1)
	{
		printf("Error, no philos\n");
		return (0);
	}
	if (vars[i - 1] < 1)
	{
		printf("Error, args must be greater than 0\n");
		return (0);
	}
	if (!check_int_lim(argv[i]))
	{
		printf("Error, use int arguments");
		return (0);
	}
	return (1);
}
