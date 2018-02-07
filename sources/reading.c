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
#include <stdlib.h>

#define READ_SIZE 128

t_str	*read_input(t_params *p)
{
	char	buf[READ_SIZE];
	t_str	*read_s;
	t_list	*list;
	int		ret;

	read_s = (t_str*)malloc(sizeof(t_str));
	list = NULL;
	while ((ret = read(p->input_fd, buf, READ_SIZE)) > 0)
		ft_lstpushback(&list, ft_lstnew((void*)(&buf[0]), ret));
	read_s->str = ft_list_to_string(list, &read_s->size);
	ft_lstdel(&list, NULL);
	return (read_s);
}
