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

void	des_base64(t_params *p, t_str *str, t_keyf *keyf, t_desf *desf)
{
	t_str	*ans;

	if (p->base64_flag && !p->to_encrypt)
	{
		ans = base64_decrypt(str);
		free(str->str);
		free(str);
		str = ans;
	}
	ans = des_str_processing(p, str, keyf, desf);
	if (p->base64_flag && p->to_encrypt)
	{
		str = base64_encrypt(ans);
		free(ans->str);
		free(ans);
		ans = str;
	}
	write(p->output_fd, ans->str, ans->size); //peredelat na return!
}

void	des_cbc(void *param)
{
	t_params	*p;
	t_str		*str;

	p = (t_params*)param;
	p->mode = CBC;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	if (!p->iv)
		p->iv = getpass("enter initial vector: ");
	str = read_input(p);
	des_base64(p, str, &key_processing, &des_encode_block);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}

void	des_ecb(void *param)
{
	t_params	*p;
	t_str		*str;

	p = (t_params*)param;
	p->mode = ECB;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	str = read_input(p);
	des_base64(p, str, &key_processing, &des_encode_block);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}

void	des3_cbc(void *param)
{
	t_params	*p;
	t_str		*str;

	p = (t_params*)param;
	p->mode = CBC;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	if (!p->iv)
		p->iv = getpass("enter initial vector: ");
	str = read_input(p);
	des_base64(p, str, &key3_processing, &des3_encode_block);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}

void	des3_ecb(void *param)
{
	t_params	*p;
	t_str		*str;

	p = (t_params*)param;
	p->mode = ECB;
	des_parse_flags(p, -1);
	if (!p->hex_key)
		p->hex_key = getpass("enter des key in hex: ");
	str = read_input(p);
	des_base64(p, str, &key3_processing, &des3_encode_block);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
}
