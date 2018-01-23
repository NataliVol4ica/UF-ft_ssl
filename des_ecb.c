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

void	des_ecb(void *param)
{
	t_params	*p;

	p = (t_params*)param;
	base64_parse_flags(p);

	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");

	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
