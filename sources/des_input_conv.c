/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_input_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:43:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/24 14:43:56 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "libft.h"

static void	hex_to_bits(char c, t_bits *b, size_t from)
{
	size_t	i;
	size_t	num;

	if (c >= '0' && c <= '9')
		num = c - '0';
	else if (c >= 'a' && c <= 'f')
		num = c + 10 - 'a';
	else if (c >= 'A' && c <= 'F')
		num = c + 10 - 'A';
	else
		key_error(c);
	i = -1;
	while (++i < 4)
	{
		b->bits[from + 3 - i] = num % 2;
		num /= 2;
	}
}

static void	fill_remainder(t_des *d, size_t i)
{
	size_t			j;
	unsigned char	c;
	char			num;

	num = 8 - i;
	i--;
	while (++i < 8)
	{
		c = num;
		j = -1;
		while (++j < 8)
		{
			d->block.bits[i * 8 + 7 - j] = c % 2;
			c /= 2;
		}
	}
}

void		des_str_to_bits(t_des *d, char *str)
{
	size_t			i;
	size_t			j;
	unsigned char	c;

	i = 0;
	while (i < 8)
	{
		c = str[i];
		j = -1;
		while (++j < 8)
		{
			d->block.bits[i * 8 + 7 - j] = c % 2;
			c /= 2;
		}
		i++;
	}
	fill_remainder(d, i);
}

void		des_key_to_bits(char *str, t_bits *b)
{
	size_t		i;

	i = -1;
	while (str[++i] && i < 16)
		hex_to_bits(str[i], b, i * 4);
	i--;
	while (++i < 16)
		hex_to_bits('0', b, i * 4);
}

void		des_bits_to_str(t_des *d, char *str)
{
	unsigned char	c;
	size_t			i;
	size_t			j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		c = 0;
		while (++j < 8)
			c = c * 2 + d->block.bits[i * 8 + j];
		str[i] = c;
	}
}
