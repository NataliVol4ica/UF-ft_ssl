/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:50:43 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/30 15:50:43 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "permutations.h"

void	des_key_permutation(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 56)
		des->x56key.bits[i] = des->x64key.bits[g_key_permut[i] - 1];
}

void	des_compression_permutation(t_des *des, t_bits *x48key)
{
	size_t	i;

	i = -1;
	while (++i < 48)
		x48key[des->dround].bits[i] =
			des->x56key.bits[g_compress_permut[i] - 1];
}

void	key_processing(t_params *p, t_des *des, t_bits *x48key)
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
	p->to_encrypt ? key_processing(p, des, des->x48key1) :
					key_processing(p, des, des->x48key3);
	p->hex_key = keylen > 16 ? &p->hex_key[16] : &p->hex_key[keylen];
	keylen = keylen > 16 ? keylen - 16 : 0;
	p->to_encrypt = 1 - p->to_encrypt;
	key_processing(p, des, des->x48key2);
	p->hex_key = keylen > 16 ? &p->hex_key[16] : &p->hex_key[keylen];
	p->to_encrypt = 1 - p->to_encrypt;
	p->to_encrypt ? key_processing(p, des, des->x48key3) :
					key_processing(p, des, des->x48key1);
	(void)x48key;
}
