/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:31:39 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/16 15:31:39 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static void		do_free(t_list **readlist, char **left, t_list *fd_elem)
{
	ft_lstdel(readlist, NULL);
	ft_memdel((void**)left);
	ft_memdel(&fd_elem->content);
}

static t_list	*get_list_elem(t_list **l, const int fd)
{
	t_list	*t;

	t = *l;
	while (t)
	{
		if (t->content_size == (size_t)fd)
			return (t);
		t = t->next;
	}
	if ((t = ft_lstnew(NULL, 0)))
	{
		t->content_size = (size_t)fd;
		ft_lstpushback(l, t);
		return (t);
	}
	return (NULL);
}

static int		read_the_line(int fd, char **left, char **line, t_list *fd_elem)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	int				new_str_size;
	t_list			*readlist;

	new_str_size = 0;
	if (read(fd, buf, 0) < 0)
		return (-1);
	readlist = ft_lstnew(*left, ft_strlen(*left) + 1);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		new_str_size = ret - ft_strlen((char*)ft_memchr(buf, '\n', BUFF_SIZE));
		buf[new_str_size] = '\0';
		ft_lstpushback(&readlist, ft_lstnew(&buf, new_str_size + 1));
		if (ret != new_str_size)
			break ;
	}
	*line = ft_list_to_string(readlist);
	do_free(&readlist, left, fd_elem);
	if (ret == 0 && (*line)[0] == '\0')
		return (0);
	fd_elem->content = (new_str_size == ret || ret == 0) ? NULL :
		(void*)ft_strdup(&buf[new_str_size + 1]);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*fd_list = NULL;
	t_list			*fd_elem;
	char			*left;
	char			*temp;
	char			*cont;

	if (BUFF_SIZE <= 0 || BUFF_SIZE > 8387512 || fd < 0 || line == NULL)
		return (-1);
	fd_elem = get_list_elem(&fd_list, fd);
	left = ft_strdup((char*)fd_elem->content);
	if (left && (cont = ft_memchr(left, '\n', ft_strlen(left))))
	{
		temp = ft_strdupab(left, ft_strlen(left) - ft_strlen(cont) + 1,
			ft_strlen(left) - 1);
		*line = ft_strdupab(left, 0,
			ft_strlen(left) - ft_strlen(cont) - 1);
		free(left);
		ft_memdel(&fd_elem->content);
		fd_elem->content = temp[0] == '\0' ? NULL : (void*)ft_strdup(temp);
		free(temp);
		return (1);
	}
	return (read_the_line(fd, &left, line, fd_elem));
}
