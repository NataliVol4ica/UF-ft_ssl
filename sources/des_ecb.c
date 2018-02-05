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
#include <stdlib.h>

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
	des_key_to_bits(des, p->hex_key, &des->x64key);
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
		des_key_to_bits(des, p->iv, &des->iv);
}

void	proceed_des_mode_pre(t_des_m mode, t_des *des, _Bool enc)
{
	if (mode == CBC)
	{
		des_xor(&des->block, &des->iv, 64);
	}
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
}
 echo "zqYWONX68rWNxl7msIdGC67Uh2HfVEBo" | ft_ssl des-cbc -d -a -k 6162636461626364 -v 0011223344556677

char	*des_str_processing(t_params *p, char *str)
{
	t_des	des;
	int		ret;
	char	buf[9];
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	num;
	size_t	print_len;
	t_list	*list;
	char	*ans;

	list = NULL;
	print_len = 8;
	key_processing(p, &des);
	des.is_last = 0;
	i = 0;
	while (str[i] || des.is_last == 0)
	{
		j = 0;
		while (str[i + j] && j < 8)
		{
			buf[j] = str[i + j];
			j++;
		}
		if (j < 8)
		{
			des.is_last = 1;
			if (p->to_encrypt)
			{
				num = 8 - j;
				k = j - 1;
				while (++k < 8)
					buf[k] = num;
			}
		}
		if (j == 8 && !str[i + 8] && !p->to_encrypt)
			des.is_last = 1;
		buf[8] = '\0';
		des_str_to_bits(&des, &buf[0]);
		proceed_des_mode_pre(p->mode, &des, p->to_encrypt);
		des_encode(&des);
		proceed_des_mode_final(p->mode, &des, p->to_encrypt);
		des_bits_to_str(&des, &buf[0]);
		if (!p->to_encrypt && des.is_last)
			print_len = 8 - buf[7];
		buf[print_len] = '\0';
		ft_lstpushback(&list, ft_lstnew((void*)(&buf[0]), print_len + 1));
		i += j;
	}
	ans = ft_list_to_string(list);
	ft_lstdel(&list, NULL);
	return (ans);
}

void	des_ecb(void *param)
{
	t_params	*p;
	char		*str;
	char		*ans;

	p = (t_params*)param;
	p->mode = ECB;
	des_parse_flags(p);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	str = read_input(p);
	if (p->base64_flag && !p->to_encrypt)
	{
		ans = base64_decrypt(p, str);
		free(str);
		str = ans;
	}
	ans = des_str_processing(p, str);
	if (p->base64_flag && p->to_encrypt)
	{
		str = base64_encrypt(p, ans);
		free(ans);
		ans = str;
	}
	ft_printf_fd(p->output_fd, "%s", ans);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
