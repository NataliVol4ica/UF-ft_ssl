/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:24:14 by nkolosov          #+#    #+#             */
/*   Updated: 2017/11/08 17:24:15 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_str
{
	char			*str;
	size_t			size;
}					t_str;

#endif
