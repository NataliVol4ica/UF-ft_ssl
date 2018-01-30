/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 16:08:22 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/01 16:08:22 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_num_of_words(char *str)
{
	int		ans;
	int		i;

	i = 0;
	ans = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (str[i])
		{
			ans++;
			while (str[i] && !(ft_iswhitespace(str[i])))
				i++;
		}
	}
	return (ans);
}

static char	*get_next_word(char *str, int *pos)
{
	int		len;
	char	*ans;

	len = 0;
	while (str[*pos + len] && !(ft_iswhitespace(str[*pos + len])))
		len++;
	ans = (char*)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (str[*pos + len] && !(ft_iswhitespace(str[*pos + len])))
	{
		ans[len] = str[*pos + len];
		len++;
	}
	*pos += len;
	ans[len] = '\0';
	return (ans);
}

char		**ft_split_whitespaces(char *str)
{
	char	**ans;
	int		num_of_words;
	int		i;
	int		pos;

	num_of_words = count_num_of_words(str);
	ans = (char**)malloc(sizeof(char*) * (num_of_words + 1));
	ans[num_of_words] = NULL;
	i = -1;
	pos = 0;
	while (++i < num_of_words)
		ans[i] = get_next_word(str, &pos);
	return (ans);
}
