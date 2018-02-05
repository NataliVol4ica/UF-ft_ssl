/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 20:17:31 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/05 20:17:31 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

void	des_base64(t_params *p, char *str)
{
	char		*ans;

	if (p->base64_flag && !p->to_encrypt)
	{
		ans = base64_decrypt(str);
		free(str);
		str = ans;
	}
	ans = des_str_processing(p, str);
	if (p->base64_flag && p->to_encrypt)
	{
		str = base64_encrypt(ans);
		free(ans);
		ans = str;
	}
	ft_printf_fd(p->output_fd, "%s", ans);
}

void	des_cbc(void *param)
{
	t_params	*p;
	char		*str;

	p = (t_params*)param;
	p->mode = CBC;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	if (!p->iv)
		p->iv = getpass("enter initial vector: ");
	str = read_input(p);
	des_base64(p, str);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}

void	des_ecb(void *param)
{
	t_params	*p;
	char		*str;

	p = (t_params*)param;
	p->mode = ECB;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	str = read_input(p);
	des_base64(p, str);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
