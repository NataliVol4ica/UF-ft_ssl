/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 15:28:02 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 15:28:02 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <string.h>

typedef enum	e_encoding_type
{
	UNKNOWN = 0, BASE64 = 2
}				t_encoding_type;

typedef int		(*parser_func)(void*);
typedef struct	s_func
{
	char		*name;
	size_t		len;
	parser_func	func;
}				t_func;

typedef struct	s_params
{
	size_t	ac;
	char	**av;
}				t_params;

#endif
