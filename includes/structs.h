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
	_Bool	base64_flag;
}				t_params;

typedef struct	s_read
{
	unsigned char	x8[3];
	unsigned char	x6[4];
}				t_read;

typedef struct	s_bits
{
	_Bool	bits[64];
}				t_bits;

typedef struct	s_des
{
	_Bool	is_last;
	t_bits	block;
	t_bits	x64key;
	t_bits	x56key_initial;
	t_bits	x56key;
	t_bits	x48key[16];
	t_bits	x32data_l;
	t_bits	x32data_r;
	t_bits	x48data_r;
	size_t	dround;
}				t_des;

static char		*g_alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz0123456789+/=";

#endif
