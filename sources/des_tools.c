/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:50:48 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/30 15:50:48 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

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

void	des_xor(t_bits *a, t_bits *b, size_t until)
{
	size_t	i;

	i = -1;
	while (++i < until)
		a->bits[i] = a->bits[i] ^ b->bits[i];
}

void	key_processing(t_params *p, t_des *des)
{
	des_key_to_bits(p->hex_key, &des->x64key);
	des_key_permutation(des);
	des->dround = 0;
	while (des->dround < 16)
	{
		if (p->to_encrypt)
			des_key_shift_enc(des);
		else
			des_key_shift_dec(des);
		des_compression_permutation(des);
		des->dround++;
	}
	if (p->mode == CBC)
		des_key_to_bits(p->iv, &des->iv);
}

void	proceed_des_mode_pre(t_des_m mode, t_des *des, _Bool enc)
{
	if (mode == CBC)
	{
		des_xor(&des->block, &des->iv, 64);
	}
	(void)enc;
}

void	proceed_des_mode_final(t_des_m mode, t_des *des, _Bool enc)
{
	size_t	i;

	if (mode == CBC)
	{
		i = -1;
		while (++i < 64)
			des->iv.bits[i] = des->block.bits[i];
	}
	(void)enc;
}
