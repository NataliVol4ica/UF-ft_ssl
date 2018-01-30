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

char	*ft_list_to_string(t_list *t)
{
	char	*ans;
	char	*str;
	int		i;
	int		j;
	t_list	*l;

	l = t;
	i = 0;
	while (l)
	{
		i += ft_strlen((char*)l->content);
		l = l->next;
	}
	ans = ft_strnew(i);
	i = -1;
	while (t)
	{
		j = -1;
		str = (char*)t->content;
		if (str)
			while (str[++j])
				ans[++i] = str[j];
		t = t->next;
	}
	return (ans);
}
