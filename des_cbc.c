/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:12:54 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 16:12:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <unistd.h>

void	des_cbc(void *param)
{
	t_params	*p;

	p = (t_params*)param;
	base64_parse_flags(p);

	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
