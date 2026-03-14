/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:00:43 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/28 18:31:10 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*sourc;

	dst = (unsigned char *)dest;
	sourc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dst > sourc)
	{
		while (n--)
			dst[n] = sourc[n];
	}
	else
		dst = ft_memcpy(dest, src, n);
	return (dst);
}

// int main(void)
// {{
// 	char dest[13] = "dddddddddddd";
// 	char src[6] = "salut";
// 	printf("%s \n", (char *)ft_memmove(dest, src, 3));
// 	return (0);
// }}
