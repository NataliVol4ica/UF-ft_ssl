/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:58:33 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/23 17:58:33 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <fcntl.h>
#include <unistd.h>

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

void	base64_parse_flags(t_params *p)
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
	open_files(p);
}

void	des_parse_flags(t_params *p)
{
	size_t	i;

	i = -1;
	while (++i < p->ac)
		if (p->av[i][0] == '-' && p->av[i][2] == '\0')
		{
			if (p->av[i][1] == 'd')
				p->to_encrypt = 0;
			else if (p->av[i][1] == 'e')
				p->to_encrypt = 1;
			else if (p->av[i][1] == 'i' && p->av[i + 1] &&
					p->av[i + 1][0] != '-')
				p->input = p->av[i + 1];
			else if (p->av[i][1] == 'o' && p->av[i + 1] &&
				p->av[i + 1][0] != '-')
				p->output = p->av[i + 1];
			else if (p->av[i][1] == 'a')
				p->base64_flag = 1;
			else if (p->av[i][1] == 'k' && p->av[i + 1] &&
					p->av[i + 1][0] != '-')
				p->hex_key = p->av[i + 1];
			else
				invalid_flag(p->av[i]);
		}
	open_files(p);
}
