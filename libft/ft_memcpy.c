/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:24:20 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/21 22:26:27 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
// int main(void)
// {
// 	size_t n = 4;
// 	char src[13] = "mais nan jure";
// 	char dest[n + 1];
// 	printf("%s\n", (char*)memcpy(dest, src, n));
// 	printf("%s\n", (char*)ft_memcpy(dest, src, n));
// 	return (0);
// }