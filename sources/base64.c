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

static void	s1(t_str *str, size_t *i, t_read *reader)
{
	size_t		j;
	size_t		extra_bytes;

	extra_bytes = 0;
	j = 0;
	while (*i + j < str->size && j < 3)
	{
		reader->x8[j] = str->str[*i + j];
		j++;
	}
	*i = *i + j;
	while (j < 3)
	{
		extra_bytes++;
		reader->x8[j++] = 0;
	}
	x8_to_x6(reader);
	j = -1;
	while (++j < 4 - extra_bytes)
		reader->x6[j] = g_alph[reader->x6[j]];
	j = 3 - extra_bytes;
	while (++j < 4)
		reader->x6[j] = '=';
}

t_str		*base64_encrypt(t_str *str)
{
	t_str		*ans;
	size_t		i;
	t_read		reader;
	t_list		*list;

	ans = (t_str*)malloc(sizeof(t_str));
	list = NULL;
	i = 0;
	while (i < str->size)
	{
		s1(str, &i, &reader);
		ft_lstpushback(&list, ft_lstnew((void*)(&reader.x6[0]), 4));
	}
	ans->str = ft_list_to_string_x64(list, &ans->size);
	ft_lstdel(&list, NULL);
	return (ans);
}

static int	s2(t_str *str, size_t *i, t_read *reader)
{
	size_t		j;

	if (str->str[*i] == '\n' && ((*i + 1) % 65 == 0 || *i + 1 == str->size))
	{
		*i = *i + 1;
		return (1);
	}
	j = 0;
	while (*i + j < str->size && j < 4)
	{
		reader->x6[j] = str->str[*i + j];
		j++;
	}
	if (j != 4)
		base64_block_error();
	*i = *i + j;
	return (0);
}

t_str		*base64_decrypt(t_str *str)
{
	t_str		*ans;
	size_t		i;
	t_read		reader;
	t_list		*list;
	size_t		extra;

	ans = (t_str*)malloc(sizeof(t_str));
	list = NULL;
	i = 0;
	while (i < str->size)
	{
		if (s2(str, &i, &reader))
			continue ;
		extra = x6_to_x8(&reader);
		ft_lstpushback(&list, ft_lstnew((void*)(&reader.x8[0]), 3 - extra));
	}
	ans->str = ft_list_to_string(list, &ans->size);
	ft_lstdel(&list, NULL);
	return (ans);
}

void		base64(void *param)
{
	t_params	*p;
	t_str		*str;
	t_str		*ans;

	p = (t_params*)param;
	base64_parse_flags(p);
	str = read_input(p);
	if (p->to_encrypt)
		ans = base64_encrypt(str);
	else
		ans = base64_decrypt(str);
	write(p->output_fd, ans->str, ans->size);
	if (p->input)
		close(p->input_fd);
	if (p->output)
		close(p->output_fd);
	free(str->str);
	free(str);
	free(ans->str);
	free(ans);
}
