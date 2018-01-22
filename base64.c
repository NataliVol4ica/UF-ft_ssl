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

#define ALPH "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

static void	char_to_x64(t_params *p, t_read *reader)
{
	reader->res[0] = (reader->buf[0] >> 2);
	reader->res[1] = reader->buf[0] << 6;
	reader->res[1] = (reader->res[1] >> 2) + (reader->buf[1] >> 4);
	reader->res[2] = reader->buf[1] << 4;
	reader->res[2] = (reader->res[2] >> 2) + (reader->buf[2] >> 6);
	reader->res[3] = reader->buf[2] << 2;
	reader->res[3] = reader->res[3] >> 2;
	/*ft_printf("%1$b|%2$b got into %3$b(%3$d)\n", reader.buf[1], reader.buf[2], reader.res[3]);
	unsigned char c;
	ft_printf("%d\n", reader.buf[2]);
	ft_printf("%b\n", reader.buf[2]);
	c = reader.buf[2] << 2;
	ft_printf("%b\n", c);
	c = c >> 2;
	ft_printf("%b\n", c);
	ft_printf("%d\n", c);*/
	//ft_printf("%08b%08b%08b\n", reader.buf[0], reader.buf[1], reader.buf[2]);
	//ft_printf("%06b%06b%06b%06b\n", reader.res[0], reader.res[1], reader.res[2], reader.res[3]);
}

void		base64(void *param)
{
	t_params	*p;
	size_t		i;
	int			ret;
	t_read		reader;
	size_t		extra_bytes;

	p = (t_params*)param;
	i = -1;
	while(++i < p->ac)
	{
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
	if (p->input)
		p->input_fd = open(p->input, O_RDONLY);
	if (p->input_fd < 0)
		open_error(p->input);
	if (p->output)
		p->output_fd = open(p->output, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (p->output_fd < 0)
		open_error(p->output);

	extra_bytes = 0;
	while ((ret = read(p->input_fd, reader.buf, 3)) > 0 )
	{
		extra_bytes = 3 - ret;
		ret = 3;
		while (ret-- > 3 - extra_bytes)
			reader.buf[ret] = 0;
		char_to_x64(p, &reader);
		i = -1;
		while (++i < 4 - extra_bytes)
			write (p->output_fd, &ALPH[reader.res[i]], 1);
		//write(p->output_fd, &ALPH[reader.res[0]], 1);
		//write(p->output_fd, &ALPH[reader.res[1]], 1);
		//write(p->output_fd, &ALPH[reader.res[2]], 1);
		//write(p->output_fd, &ALPH[reader.res[3]], 1);
	}
	while (extra_bytes-- > 0)
		write(p->output_fd, "=", 1);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
