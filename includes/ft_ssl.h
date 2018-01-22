/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 14:37:40 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 14:37:40 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include "structs.h"

/*
** CRYPTOGRAPHY FUNCS
*/

void		base64(void *param);

/*
** STRUCT TOOLS
*/

t_params	*new_param(int ac, char **av);

/*
** ERRORS
*/

void		malloc_error(void);
void		invalid_flag(char *str);
void		open_error(char *str);

#endif
