/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys_permuts.c                                 :+:      :+:    :+:   */
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

void	des_compression_permutation(t_des *des)
{
	size_t	i;

	i = -1;
	while (++i < 48)
		des->x48key[des->dround].bits[i] =
			des->x56key.bits[g_compress_permut[i] - 1];
}
