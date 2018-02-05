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
#include "libft.h"
#include <stdlib.h>

void	des_cbc(void *param)
{
	t_params	*p;
	char		*str;
	char		*ans;

	p = (t_params*)param;
	p->mode = CBC;
	des_parse_flags(p);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	if (!p->iv)
		p->iv = getpass("enter initial vector: ");
	str = read_input(p);
	if (p->base64_flag && !p->to_encrypt)
	{
		ans = base64_decrypt(p, str);
		free(str);
		str = ans;
	}
	ans = des_str_processing(p, str);
	if (p->base64_flag && p->to_encrypt)
	{
		str = base64_encrypt(p, ans);
		free(ans);
		ans = str;
	}
	ft_printf_fd(p->output_fd, "%s", ans);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
