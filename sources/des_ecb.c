/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:12:48 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 16:12:48 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <unistd.h>
#include "libft.h"

void	des_encode(t_des *des)
{
	size_t	i;
	t_bits	temp;

	des_initial_permutation(des);
	des_data_halv(des);
	des->dround = 0;
	while (des->dround < 16)
	{
		i = -1;
		while (++i < 32)
			temp.bits[i] = des->x32data_r.bits[i];
		des_expand_permut(des);
		des_xor(&des->x48data_r, &des->x48key[des->dround], 48);
		i = -1;
		while (++i < 8)
			des_sbox_perm(des, i);
		des_pbox_permutation(des);
		des_xor(&des->x32data_r, &des->x32data_l, 32);
		i = -1;
		while (++i < 32)
			des->x32data_l.bits[i] = temp.bits[i];
		des->dround++;
	}
	i = -1;
	while (++i < 32)
		des->block.bits[i] = des->x32data_r.bits[i];
	i = -1;
	while (++i < 32)
		des->block.bits[32 + i] = des->x32data_l.bits[i];
	des_final_permutation(des);
}

void	key_processing(t_params *p, t_des *des)
{
	des_key_to_bits(des, p->hex_key);
	des_key_permutation(des);
	des->dround = 0;
	while (des->dround < 16)
	{
		des_key_shift_enc(des);
		des_compression_permutation(des);
		des->dround++;
	}
}

void	des_reading(t_params *p) //without base64 flag
{
	t_des	des;
	int		ret;
	char	buf[9];
	size_t	i;

	key_processing(p, &des);
	des.is_last = 0;
	while ((ret = read(p->input_fd, buf, 8)) > 0 || des.is_last == 0)
	{
		if (ret == 0)
		{
			des.is_last = 1;
			i = -1;
			while (++i < 8)
				buf[i] = 8;
		}
		buf[ret] = '\0';
		des_str_to_bits(&des, &buf[0]);
		des_encode(&des);
		des_bits_to_str(&des, &buf[0]);
		ft_printf_fd(p->output_fd, "%8s", buf);
	}
}

void	des_base64_reading(t_params *p)
{
	//do the same stuff as in des_reading
	//if flag is encode then encode with base64 in the end of encryption
	//if flag is decode then read with 3 character blocks
	//and convert them into x8 blocks, marking if is this block last
	(void)p;
}

void	des_ecb(void *param)
{
	t_params	*p;

	p = (t_params*)param;
	des_parse_flags(p);

	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	des_reading(p);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
