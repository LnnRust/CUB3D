/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:59:06 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/18 12:54:29 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void ft_ft_toupper(unsigned int z, char *c)
// {
// 	z = 0;
// 	if (*c >= 'a' && *c <= 'z')
// 		*c -= 32;
// }

// int main(void)
// {
// 	char *str = "SdsfasdDSDSAfsa";
// 	ft_striteri(str, ft_ft_toupper);
// 	printf("%s\n", str);
// 	return (0);
// }