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

t_str	*des_str_processing(t_params *p, t_str *str)
{
	t_des	des;
	char	buf[9];
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	num;
	size_t	print_len;
	t_list	*list;
	t_str	*ans;

	ans = (t_str*)malloc(sizeof(t_str));
	list = NULL;
	print_len = 8;
	key_processing(p, &des);
	des.is_last = 0;
	i = 0;
	while (i < str->size || des.is_last == 0)
	{
		j = 0;
		while (i + j < str->size && j < 8)
		{
			buf[j] = str->str[i + j];
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
		if (j == 8 && str->size == i + 8 && !p->to_encrypt)
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
		ft_lstpushback(&list, ft_lstnew((void*)(&buf[0]), print_len));
		i += j;
	}
	ans->str = ft_list_to_string(list, &ans->size);
	ft_lstdel(&list, NULL);
	return (ans);
}
