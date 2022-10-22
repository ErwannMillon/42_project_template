/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:54:35 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/22 03:37:06 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_string_is_num(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	num;
	int			i;
	int			minus;

	minus = 1;
	i = 0;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + str[i] - 48;
		i++;
	}
	num *= minus;
	return (num);
}
