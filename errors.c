/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:37:09 by nkolosov          #+#    #+#             */
/*   Updated: 2018/01/22 16:37:09 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	malloc_error(void)
{
	ft_printf("Malloc error. Exiting the program\n");
	exit(1);
}

void	invalid_flag(char *str)
{
	ft_printf("Invalid flag: %s.\n", str);
	exit(1);
}

void	open_error(char *str)
{
	ft_printf("Error opening %s.\n", str);
	exit(1);
}

void	key_error(void)
{
	ft_printf("Key is not hexademical.\n");
	exit(1);
}
