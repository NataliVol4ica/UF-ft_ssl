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

static void	do_while(t_des *des)
{
	size_t	i;
	t_bits	temp;

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
}

void		des_encode(t_des *des)
{
	size_t	i;

	des_initial_permutation(des);
	des_data_halv(des);
	des->dround = 0;
	while (des->dround < 16)
	{
		do_while(des);
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

static void	add_block(t_list **list, t_des *des, t_params *p, char *buf)
{
	size_t	print_len;

	print_len = 8;
	des_str_to_bits(des, &buf[0]);
	proceed_des_mode_pre(p->mode, des, p->to_encrypt);
	des_encode(des);
	proceed_des_mode_final(p->mode, des, p->to_encrypt);
	des_bits_to_str(des, &buf[0]);
	if (!p->to_encrypt && des->is_last)
		print_len = 8 - buf[7];
	buf[print_len] = '\0';
	ft_lstpushback(list, ft_lstnew((void*)(&buf[0]), print_len + 1));
}

static void	get_buf(size_t *i, char *buf, t_params *p, t_des *des)
{
	size_t	j;
	size_t	k;
	size_t	num;

	j = 0;
	while (des->str[*i + j] && j < 8)
	{
		buf[j] = des->str[*i + j];
		j++;
	}
	if (j < 8)
	{
		des->is_last = 1;
		if (p->to_encrypt)
		{
			num = 8 - j;
			k = j - 1;
			while (++k < 8)
				buf[k] = num;
		}
	}
	if (j == 8 && !des->str[*i + 8] && !p->to_encrypt)
		des->is_last = 1;
	buf[8] = '\0';
	*i = *i + j;
}

char		*des_str_processing(t_params *p, char *str)
{
	t_des	des;
	size_t	i;
	t_list	*list;
	char	*ans;
	char	buf[9];

	list = NULL;
	key_processing(p, &des);
	des.is_last = 0;
	i = 0;
	des.str = str;
	while (str[i] || des.is_last == 0)
	{
		get_buf(&i, &buf[0], p, &des);
		add_block(&list, &des, p, &buf[0]);
	}
	ans = ft_list_to_string(list);
	ft_lstdel(&list, NULL);
	return (ans);
}
