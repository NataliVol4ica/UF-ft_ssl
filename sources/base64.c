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
#include "libft.h"
#include <stdlib.h>

char	*base64_encrypt(t_params *p, char *str)
{
	char		*ans;
	size_t		i;
	size_t		j;
	int			ret;
	t_read		reader;
	size_t		extra_bytes;
	t_list		*list;

	list = NULL;
	extra_bytes = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && j < 3)
		{
			reader.x8[j] = str[i + j];
			j++;
		}
		i += j;
		while (j < 3)
		{
			extra_bytes++;
			reader.x8[j++] = 0;
		}
		x8_to_x6(p, &reader);
		j = -1;
		while (++j < 4 - extra_bytes)
			reader.x6[j] = g_alph[reader.x6[j]];
		j = 3 - extra_bytes;
		while (++j < 4)
			reader.x6[j] = '=';
		reader.x6[4] = '\0';
		ft_lstpushback(&list, ft_lstnew((void*)(&reader.x6[0]), 5));
	}
	ans = ft_list_to_string(list);
	ft_lstdel(&list, NULL);
	return (ans);
}

char	*base64_decrypt(t_params *p, char *str)
{
	char		*ans;
	size_t		i;
	size_t		j;
	int			ret;
	t_read		reader;
	size_t		extra_bytes;
	t_list		*list;

	list = NULL;
	extra_bytes = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && (i % 64 == 0 || str[i + 1] == '\0'))
		{
			i++;
			continue ;
		}
		j = 0;
		while (str[i + j] && j < 4)
		{
			reader.x6[j] = str[i + j];
			j++;
		}
		if (j != 4)
			base64_block_error();
		i += j;
		x6_to_x8(p, &reader);
		ft_lstpushback(&list, ft_lstnew((void*)(&reader.x8[0]), 4));
	}
	ans = ft_list_to_string(list);
	ft_lstdel(&list, NULL);
	return (ans);
}

void		base64(void *param)
{
	t_params	*p;
	char		*str;
	char		*ans;
	size_t		i;
	size_t		ret;

	p = (t_params*)param;
	base64_parse_flags(p);
	str = read_input(p);
	if (p->to_encrypt)
		ans = base64_encrypt(p, str);
	else
		ans = base64_decrypt(p, str);
	i = 0;
	while (1)
	{
		ret = ft_printf_fd(p->output_fd, "%.64s", &ans[i]);
		if (p->to_encrypt)
			ft_printf_fd(p->output_fd, "\n");
		if (ret % 64 != 0 || ret == 0)
			break ;
		i = i + ret - 1;
	}
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
	free(str);
	free(ans);
}
