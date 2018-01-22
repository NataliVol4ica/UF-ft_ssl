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

void	base64(void *param)
{
	t_params	*p;
	size_t		i;

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

	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
