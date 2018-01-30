/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:39:44 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 16:39:44 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <unistd.h>

static void	base64_encrypt(t_params *p)
{
	size_t		i;
	int			ret;
	t_read		reader;
	size_t		extra_bytes;

	extra_bytes = 0;
	while ((ret = read(p->input_fd, reader.x8, 3)) > 0)
	{
		extra_bytes = 3 - ret;
		ret = 3;
		while (ret-- > 3 - extra_bytes)
			reader.x8[ret] = 0;
		x8_to_x6(p, &reader);
		i = -1;
		while (++i < 4 - extra_bytes)
			write(p->output_fd, &g_alph[reader.x6[i]], 1);
	}
	while (extra_bytes-- > 0)
		write(p->output_fd, "=", 1);
}

static void	base64_decrypt(t_params *p)
{
	int			ret;
	t_read		reader;

	while ((ret = read(p->input_fd, reader.x6, 4)) > 0)
	{
		x6_to_x8(p, &reader);
		write(p->output_fd, reader.x8, 3);
	}
}

void		base64(void *param)
{
	t_params	*p;

	p = (t_params*)param;
	base64_parse_flags(p);
	if (p->to_encrypt)
		base64_encrypt(p);
	else
		base64_decrypt(p);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
