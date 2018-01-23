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
	return (p);
}