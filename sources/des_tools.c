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

void	key_processing(t_params *p, t_des *des, t_bits *x48key)
{
	//ft_printf("encrypting? %d\n", p->to_encrypt);
	//ft_printf("key %s\n", p->hex_key);
	des_key_to_bits(p->hex_key, &des->x64key);
	//ft_printf("in bits  "); print_bits(des->x64key, 64);
	des_key_permutation(des);
	//ft_printf("1 permut "); print_bits(des->x56key, 56);
	des->dround = 0;
	while (des->dround < 16)
	{
		if (p->to_encrypt)
			des_key_shift_enc(des);
		else
			des_key_shift_dec(des);
		des_compression_permutation(des, x48key);
		des->dround++;
	}
	if (p->mode == CBC)
		des_key_to_bits(p->iv, &des->iv);
}

void	key3_processing(t_params *p, t_des *des, t_bits *x48key)
{
	size_t	keylen;

	keylen = ft_strlen(p->hex_key);
	if (p->to_encrypt)
		key_processing(p, des, des->x48key1);
	else
		key_processing(p, des, des->x48key3);
	if (keylen > 16)
	{
		p->hex_key = &p->hex_key[16];
		keylen -= 16;
	}
	else
	{
		p->hex_key = &p->hex_key[keylen];
		keylen = 0;
	}
	p->to_encrypt = 1 - p->to_encrypt;
	key_processing(p, des, des->x48key2);
	if (keylen > 16)
	{
		p->hex_key = &p->hex_key[16];
		keylen -= 16;
	}
	else
	{
		p->hex_key = &p->hex_key[keylen];
		keylen = 0;
	}
	p->to_encrypt = 1 - p->to_encrypt;
	if (p->to_encrypt)
		key_processing(p, des, des->x48key3);
	else
		key_processing(p, des, des->x48key1);
	(void)x48key;
}

void	proceed_des_mode_pre(t_des_m mode, t_des *des, _Bool enc)
{
	size_t	i;

	if (mode == CBC && enc)
	{
		//ft_printf("I am here\n");
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
