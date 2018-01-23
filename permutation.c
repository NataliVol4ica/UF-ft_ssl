/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:46:50 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 17:46:51 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

t_bits	str_to_bits(char *str)
{
	t_bits	ans;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] && i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			ans.bits[i * 8 + 7 - j] = str[i] % 2;
			str[i] /= 2;
		}
		i++;
	}
	return (ans);
}

void	initial_permutation(t_des *des)
{
	static t_bits	temp;
	size_t			i;

	i = -1;
	while (++i < 64)
		temp.bits[i] = des->block[i];
	i = -1;
	while (++i < 64)
		des->block[i] = temp.bits[g_init_permut[i - 1]];
}
