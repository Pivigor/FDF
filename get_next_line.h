/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarlic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:49:42 by jgarlic           #+#    #+#             */
/*   Updated: 2021/09/11 16:49:43 by jgarlic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

int			my_failure(char **saved_buffer);
void		my_free(char **pointer);
long long	str_size(char *str);
int			copy_line(char *strto, char *strfrom, long long size,
				int need_to_malloc);
int			get_next_line(int fd, char **line);
#endif
