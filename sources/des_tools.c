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

void	get_next_block(t_str *str, t_params *p, t_des *des)
{
	static size_t	i = 0;
	size_t			j;
	size_t			num;
	char			buf[8];

	j = 0;
	while (i + j < str->size && j < 8)
	{
		buf[j] = str->str[i + j];
		j++;
	}
	if (j < 8 || (str->size == i + 8 && !p->to_encrypt))
		des->is_last = 1;
	if (j < 8 && p->to_encrypt)
	{
		num = 8 - j;
		j--;
		while (++j < 8)
			buf[j] = num;
	}
	i += 8;
	des_str_to_bits(des, &buf[0]);
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

void	des_xor(t_bits *a, t_bits *b, size_t until)
{
	size_t	i;

	i = -1;
	while (++i < until)
		a->bits[i] = a->bits[i] ^ b->bits[i];
}

void	proceed_des_mode_pre(t_des_m mode, t_des *des, _Bool enc)
{
	size_t	i;

	if (mode == CBC && enc)
	{
		des_xor(&des->block, &des->iv, 64);
	}
	else if (mode == CBC && !enc)
	{
		i = -1;
		while (++i < 64)
			des->iv_temp.bits[i] = des->block.bits[i];
	}
}

void	proceed_des_mode_final(t_des_m mode, t_des *des, _Bool enc)
{
	size_t	i;

	if (mode == CBC && enc)
	{
		i = -1;
		while (++i < 64)
			des->iv.bits[i] = des->block.bits[i];
	}
	else if (mode == CBC && !enc)
	{
		des_xor(&des->block, &des->iv, 64);
		i = -1;
		while (++i < 64)
			des->iv.bits[i] = des->iv_temp.bits[i];
	}
}
