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

typedef void	(*t_pars_func)(void*);
typedef struct	s_func
{
	char		*name;
	size_t		len;
	t_pars_func	func;
}				t_func;

typedef struct	s_params
{
	size_t	ac;
	char	**av;
	char	*input;
	char	*output;
	int		input_fd;
	int		output_fd;
	_Bool	to_encrypt;
}				t_params;

typedef struct	s_read
{
	unsigned char	x8[3];
	unsigned char	x6[4];
}				t_read;

static char		*g_alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz0123456789+/=";

#endif
