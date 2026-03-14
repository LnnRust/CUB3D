/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:41:20 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/18 15:16:23 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}
// int main(void)
// {
// 	char s[13] = "mais nan jure";
// 	int c = '5';
// 	size_t n = 3;
// 	printf("%s", (char *)ft_memset(s, c, n));
// 	return (0);
// }