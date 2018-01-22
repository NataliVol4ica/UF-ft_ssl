/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:12:11 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 16:12:11 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

# include "ft_ssl.h"

# define NUM_OF_FUNCS 1

static t_func	g_parse_funcs[] =
{
	{"base64", 6, &base64}
};

#endif
