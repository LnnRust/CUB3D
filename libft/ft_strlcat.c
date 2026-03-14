/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:29:50 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/19 15:43:48 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	dstlen = 0;
	srclen = 0;
	while (dst[dstlen] && dstlen < size)
		dstlen++;
	while (src[srclen])
		srclen++;
	if (dstlen == size)
		return (srclen + size);
	while (src[i] && dstlen + i + 1 < size)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < size)
		dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
// int main (void)
// {
// 	char *dst = "Mais nan";
// 	const char *src = "Jure ?";
// 	size_t size = 9;
// 	printf("%zu\n", ft_strlcat(dst, src, size));
// 	printf("%c\n", 'c');
// 	printf("%zu\n", strlcat(dst, src, size));
// 	return(0);
// }