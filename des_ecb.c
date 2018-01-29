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
	des->dround = 0;
	des_initial_permutation(des);
	des_key_shift(des);
	des_compression_permutation(des);
	des_final_permutation(des);
}

void	des_reading(t_params *p) //without base64 flag
{
	t_des	des;
	int		ret;
	char	buf[9];

	des_key_to_bits(&des, p->hex_key);
	des_key_permutation(&des);
	des.is_last = 0;
	while ((ret = read(p->input_fd, buf, 8)) > 0)
	{
		if ((read(p->input_fd, buf, 0)) == 0)
			des.is_last = 1;
		buf[ret] = '\0';
		des_str_to_bits(&des, &buf[0]);
		des_copy_key(&des);
		des_encode(&des);
	}
	if (des.is_last == 0)
	{
		des.is_last = 1;
		des_str_to_bits(&des, NULL);
		des_copy_key(&des);
		des_encode(&des);
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
