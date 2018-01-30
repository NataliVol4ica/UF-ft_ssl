/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_permuts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:50:36 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/30 15:50:36 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

void	des_initial_permutation(t_des *des)
{
	static t_bits	temp;
	size_t			i;

	i = -1;
	while (++i < 64)
		temp.bits[i] = des->block.bits[i];
	i = -1;
	while (++i < 64)
		des->block.bits[i] = temp.bits[g_init_permut[i] - 1];
}

void	des_expand_permut(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 48)
		des->x48data_r.bits[i] = des->x32data_r.bits[g_expand_permut[i] - 1];
}

void	des_sbox_perm(t_des *des, size_t num)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = des->x48data_r.bits[num * 6] * 2 + des->x48data_r.bits[num * 6 + 5];
	j = des->x48data_r.bits[num * 6 + 4] +
		des->x48data_r.bits[num * 6 + 3] * 2 +
		des->x48data_r.bits[num * 6 + 2] * 4 +
		des->x48data_r.bits[num * 6 + 1] * 8;
	n = g_sboxes[num][i][j];
	i = -1;
	while (++i < 4)
	{
		des->x32data_r.bits[num * 4 + 3 - i] = n % 2;
		n /= 2;
	}
}

void	des_pbox_permutation(t_des *des)
{
	static t_bits	temp;
	size_t			i;

	i = -1;
	while (++i < 32)
		temp.bits[i] = des->x32data_r.bits[i];
	i = -1;
	while (++i < 32)
		des->x32data_r.bits[i] = temp.bits[g_pbox_permut[i] - 1];
}

void	des_final_permutation(t_des *des)
{
	static t_bits	temp;
	size_t			i;

	i = -1;
	while (++i < 64)
		temp.bits[i] = des->block.bits[i];
	i = -1;
	while (++i < 64)
		des->block.bits[i] = temp.bits[g_final_permut[i] - 1];
}
