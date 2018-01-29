/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_permutations2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:46:50 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 17:46:51 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

void	des_key_shift_enc(t_des *des)
{
	size_t	i;
	size_t	j;
	_Bool	temp;

	i = -1;
	while (++i < g_key_shift[des->dround])
	{
		temp = des->x56key.bits[0];
		j = -1;
		while (++j < 27)
			des->x56key.bits[j] = des->x56key.bits[j + 1];
		des->x56key.bits[27] = temp;
		temp = des->x56key.bits[28];
		j = 27;
		while (++j < 55)
			des->x56key.bits[j] = des->x56key.bits[j + 1];
		des->x56key.bits[55] = temp;
	}
}

void	des_data_halv(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 32)
		des->x32data_l.bits[i] = des->block.bits[i];
	i--;
	while (++i < 64)
		des->x32data_r.bits[i - 32] = des->block.bits[i];
}

void	des_expand_permut(t_des *des)
{
	size_t	i;
	
	i = -1;
	while (++i < 48)
		des->x48data_r.bits[i] = des->x32data_r.bits[g_expand_permut[i] - 1];
}

void	des_xor(t_bits *a, t_bits *b, size_t until)
{
	size_t	i;

	i = -1;
	while (++i < until)
		a->bits[i] = a->bits[i] ^ b->bits[i];
}