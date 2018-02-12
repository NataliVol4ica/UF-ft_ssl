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

static void	proceed_round(t_des *des, t_bits *x48key)
{
	size_t	i;
	t_bits	temp;

	i = -1;
	while (++i < 32)
		temp.bits[i] = des->x32data_r.bits[i];
	des_expand_permut(des);
	des_xor(&des->x48data_r, &x48key[des->dround], 48);
	i = -1;
	while (++i < 8)
		des_sbox_perm(des, i);
	des_pbox_permutation(des);
	des_xor(&des->x32data_r, &des->x32data_l, 32);
	i = -1;
	while (++i < 32)
		des->x32data_l.bits[i] = temp.bits[i];
}

void	des_encode_block(t_des *des, t_bits *x48key)
{
	size_t	i;

	des_initial_permutation(des);
	des_data_halv(des);
	des->dround = 0;
	while (des->dround < 16)
	{
		proceed_round(des, x48key);
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

void	des3_encode_block(t_des *des, t_bits *x48key)
{
	des_encode_block(des, des->x48key1);
	des_encode_block(des, des->x48key2);
	des_encode_block(des, des->x48key3);
	(void)x48key;
}

t_str	*des_str_processing(t_params *p, t_str *str, t_keyf *kf, t_desf *desf)
{
	t_des	des;
	char	buf[9];
	size_t	print_len;
	t_list	*list;
	t_str	*ans;

	ans = (t_str*)malloc(sizeof(t_str));
	list = NULL;
	kf(p, &des, des.x48key);
	des.is_last = 0;
	while (des.is_last == 0)
	{
		get_next_block(str, p, &des);
		proceed_des_mode_pre(p->mode, &des, p->to_encrypt);
		desf(&des, des.x48key);
		proceed_des_mode_final(p->mode, &des, p->to_encrypt);
		des_bits_to_str(&des, &buf[0]);
		print_len = !p->to_encrypt && des.is_last ? 8 - buf[7] : 8;
		buf[print_len] = '\0';
		ft_lstpushback(&list, ft_lstnew((void*)(&buf[0]), print_len));
	}
	ans->str = ft_list_to_string(list, &ans->size);
	ft_lstdel(&list, NULL);
	return (ans);
}
