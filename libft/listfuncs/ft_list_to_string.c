/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 13:08:15 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/20 13:08:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include <string.h>

static size_t	len_of_malloc(t_list *l)
{
	size_t	i;

	i = 0;
	while (l)
	{
		i += l->content_size;
		l = l->next;
	}
	return (i);
}

char			*ft_list_to_string(t_list *t, size_t *len)
{
	char	*ans;
	char	*str;
	size_t	i;
	size_t	j;

	ans = ft_strnew(len_of_malloc(t));
	i = -1;
	while (t)
	{
		j = -1;
		str = (char*)t->content;
		if (str)
			while (++j < t->content_size)
				ans[++i] = str[j];
		t = t->next;
	}
	if (len)
		*len = i + 1;
	return (ans);
}

char			*ft_list_to_string_x64(t_list *t, size_t *len)
{
	char	*ans;
	char	*str;
	size_t	i;
	size_t	j;
	size_t	l;

	l = len_of_malloc(t);
	ans = ft_strnew(l + l / 64 + (l % 64 == 0 ? 0 : 1));
	i = -1;
	while (t)
	{
		j = -1;
		str = (char*)t->content;
		if (str)
			while (++j < t->content_size)
			{
				ans[++i] = str[j];
				if (i % 64 == 63)
					ans[++i] = '\n';
			}
		t = t->next;
	}
	if (i % 64 != 0)
		ans[++i] = '\n';
	len ? (*len = i + 1) : 1;
	return (ans);
}
