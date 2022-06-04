/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:48:37 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:48:38 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	my_counter(char *s, char c)
{
	int	i;
	int	k;
	int	word;

	i = 0;
	k = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (word == 0 && s[i] != c)
		{
			word = 1;
			k++;
		}
		else if (s[i] == c)
			word = 0;
		i++;
	}
	return (k);
}

static char	*my_strsepcpy(char *str, int begin, int size)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (size + 1));
	if (ptr != 0)
	{
		i = 0;
		while (i < size)
		{
			ptr[i] = str[begin];
			i++;
			begin++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

static char	*my_separator(char **str, char c)
{
	int		i;
	int		size;
	char	*s;

	s = *str;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	size = 0;
	while (s[i + size] != '\0' && s[i + size] != c)
		size++;
	*str = s + i + size;
	return (my_strsepcpy(s, i, size));
}

static char	**my_free(char **x, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(x[i]);
		i++;
	}
	free(x);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**x;
	char	*str;
	int		size;
	int		i;

	str = (char *)s;
	if (str == 0)
		size = 0;
	else
		size = my_counter(str, c);
	x = malloc(sizeof(char *) * (size + 1));
	if (x != 0)
	{
		i = 0;
		while (i < size)
		{
			x[i] = my_separator(&str, c);
			if (x[i] == 0)
				return (my_free(x, i));
			i++;
		}
		x[i] = 0;
	}
	return (x);
}
