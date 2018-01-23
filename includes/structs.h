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
	char	*hex_key;
}				t_params;

typedef struct	s_read
{
	unsigned char	x8[3];
	unsigned char	x6[4];
}				t_read;

typedef struct	s_des
{
	char	str[8];
	_Bool	block[64];
	_Bool	x64key[64];
}				t_des;

typedef struct	s_bits
{
	_Bool	bits[64];
}				t_bits;

static char		*g_alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz0123456789+/=";

#endif
