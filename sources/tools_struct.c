/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:30:55 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 16:30:56 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdlib.h>
#include "libft.h"

t_params	*new_param(int ac, char **av)
{
	t_params	*p;

	if (!(p = (t_params*)malloc(sizeof(t_params))))
		malloc_error();
	p->ac = ac - 2;
	p->av = &av[2];
	p->input = NULL;
	p->output = NULL;
	p->input_fd = 0;
	p->output_fd = 0;
	p->to_encrypt = 1;
	p->hex_key = NULL;
	p->base64_flag = 0;
	return (p);
}

void		print_bits(t_bits bits, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
	{
		ft_printf("%d", bits.bits[i]);
		if (i > 0 && i < len - 1 && i % 4 == 3)
			ft_printf(" ");
	}
	ft_printf("\n");
}
