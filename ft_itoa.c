/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:48:27 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:48:28 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*my_null_func(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (str != 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	return (0);
}

static void	my_gen_str(char *str, long long size, long long x, long long n)
{
	long long int	i;

	i = 0;
	while (i < (long long)size)
	{
		x = x / 10;
		str[i] = n / x % 10 + '0';
		i++;
	}
	str[i] = '\0';
}

static char	*my_negative_number(long long size, long long n, long long x)
{
	char	*str;

	str = malloc(sizeof(char) * (size + 2));
	if (str == 0)
		return (0);
	str[0] = '-';
	n = n * -1;
	my_gen_str(str + 1, size, x, n);
	return (str);
}

static char	*my_positive_number(long long size, long long n, long long x)
{
	char	*str;

	str = malloc(sizeof(char) * (size + 1));
	if (str == 0)
		return (0);
	my_gen_str(str, size, x, n);
	return (str);
}

char	*ft_itoa(int n)
{
	long long int	x;
	long long int	size;

	size = 0;
	x = 1;
	while (n / x != 0)
	{
		x = x * 10;
		size++;
	}
	if (n == 0)
		return (my_null_func());
	if (n < 0)
		return (my_negative_number(size, n, x));
	else
		return (my_positive_number(size, n, x));
}
