/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 13:05:05 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 13:05:05 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	long	ans;
	int		multiplier;
	int		i;

	i = 0;
	ans = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' ||
			str[i] == ' ' || str[i] == '\f' || str[i] == '\r')
		i++;
	multiplier = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - '0';
		i++;
		if (ans < 0)
			return (multiplier < 0 ? 0 : -1);
	}
	return ((int)(ans * multiplier));
}
