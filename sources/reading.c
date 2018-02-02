/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:11:52 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/02 14:11:52 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"
#include <unistd.h>

#define READ_SIZE 128

char	*read_input(t_params *p)
{
	char	buf[READ_SIZE + 1];
	char	*str;
	t_list	*list;
	int		ret;

	list = NULL;
	while ((ret = read(p->input_fd, buf, READ_SIZE)) > 0)
	{
		buf[ret] = '\0';
		ft_lstpushback(&list, ft_lstnew((void*)(&buf[0]), ret + 1));
	}
	str = ft_list_to_string(list);
	ft_lstdel(&list, NULL);
	return (str);
}
