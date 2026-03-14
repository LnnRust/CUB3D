/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:37:52 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/20 21:41:42 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(const char *nptr)
{
	static int	i;
	static int	count;

	i = 0;
	count = 0;
	while (nptr[i] && !(nptr[i] >= '0' && nptr[i] <= '9'))
		i++;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (count_char(nptr) >= 20)
		return (-1);
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * res);
}

// int main(void)
// {
// 	printf("%d\n", ft_atoi("24300000099999999999"));
// 	printf("%d\n", atoi("24300000099999999999"));
// 	return(0);
// }