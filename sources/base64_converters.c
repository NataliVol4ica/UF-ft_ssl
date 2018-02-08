/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 14:13:10 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 14:13:11 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	x8_to_x6(t_read *reader)
{
	reader->x6[0] = (reader->x8[0] >> 2);
	reader->x6[1] = reader->x8[0] << 6;
	reader->x6[1] = (reader->x6[1] >> 2) + (reader->x8[1] >> 4);
	reader->x6[2] = reader->x8[1] << 4;
	reader->x6[2] = (reader->x6[2] >> 2) + (reader->x8[2] >> 6);
	reader->x6[3] = reader->x8[2] << 2;
	reader->x6[3] = reader->x6[3] >> 2;
}

size_t	x6_to_x8(t_read *reader)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < 4 && (j = -1))
		while (++j < 65)
			if (g_alph[j] == reader->x6[i])
			{
				reader->x6[i] = j;
				break ;
			}
	i = -1;
	while (++i < 3)
		reader->x8[i] = '\0';
	reader->x8[0] = (reader->x6[0] << 2) + (reader->x6[1] >> 4);
	if (reader->x6[2] == 64)
		return (2);
	reader->x8[1] = reader->x6[1] << 4;
	reader->x8[1] += (reader->x6[2] >> 2);
	if (reader->x6[3] == 64)
		return (1);
	reader->x8[2] = reader->x6[2] << 6;
	reader->x8[2] += reader->x6[3];
		return (0);
}
