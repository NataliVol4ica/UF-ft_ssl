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
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

static void	parse_flags(t_params *p)
{
	size_t	i;

	i = -1;
	while (++i < p->ac)
		if (p->av[i][0] == '-')
		{
			if (p->av[i][1] == 'd' && p->av[i][2] == '\0')
				p->to_encrypt = 0;
			else if (p->av[i][1] == 'e' && p->av[i][2] == '\0')
				p->to_encrypt = 1;
			else if (p->av[i][1] == 'i' && p->av[i][2] == '\0' &&
					p->av[i + 1] && p->av[i + 1][0] != '-')
				p->input = p->av[i + 1];
			else if (p->av[i][1] == 'o' && p->av[i][2] == '\0' &&
					p->av[i + 1] && p->av[i + 1][0] != '-')
				p->output = p->av[i + 1];
			else
				invalid_flag(p->av[i]);
		}
}

static void	open_files(t_params *p)
{
	if (p->input)
		p->input_fd = open(p->input, O_RDONLY);
	if (p->input_fd < 0)
		open_error(p->input);
	if (p->output)
		p->output_fd = open(p->output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (p->output_fd < 0)
		open_error(p->output);
}

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
	parse_flags(p);
	open_files(p);
	if (p->to_encrypt)
		base64_encrypt(p);
	else
		base64_decrypt(p);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
