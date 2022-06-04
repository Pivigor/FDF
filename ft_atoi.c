/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:48:14 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:48:17 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	my_isspace_checker(char c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

static int	my_integer_maker(char *str, long long int i, long long int minus)
{
	unsigned long long int	number;

	number = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i] - '0');
		if (number > __LONG_LONG_MAX__ && minus % 2 == 0)
			return (-1);
		if (number > __LONG_LONG_MAX__ && minus % 2 == 1)
			return (0);
		i++;
	}
	if (minus % 2 == 1)
		return ((int)number * (-1));
	return (number);
}

int	ft_atoi(char *str)
{
	long long int	i;
	long long int	minus;

	i = 0;
	while (str[i] != '\0' && my_isspace_checker(str[i]) == 1)
		i++;
	minus = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	while (str[i] != '\0' && str[i] == '0')
		i++;
	if (str[i] >= '1' && str[i] <= '9')
		return (my_integer_maker(str, i, minus));
	else
		return (0);
}
