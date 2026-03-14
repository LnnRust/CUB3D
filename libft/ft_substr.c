/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 10:31:19 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/07 10:31:32 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*newstring;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		newstring = malloc(sizeof(char));
		if (!newstring)
			return (NULL);
		newstring[0] = '\0';
		return (newstring);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	newstring = malloc((len + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	while (s[start] && i < len)
		newstring[i++] = s[start++];
	newstring[i] = '\0';
	return (newstring);
}
