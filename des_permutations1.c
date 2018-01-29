/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_permutations1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:46:50 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 17:46:51 by nkolosov         ###   ########.fr       */
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

void	des_key_permutation(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 56)
		des->x56key.bits[i] = des->x64key.bits[g_key_permut[i] - 1];
}

void	des_compression_permutation(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 48)
		des->x48key[des->dround].bits[i] = des->x56key.bits[g_compress_permut[i] - 1];
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
