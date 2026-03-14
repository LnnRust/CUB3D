/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:36:45 by aandreo           #+#    #+#             */
/*   Updated: 2025/10/29 11:28:54 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

static	void	ft_strcat(char *dest, const char *src)
{
	size_t		i;
	size_t		j;

	j = 0;
	i = ft_strlen(dest);
	if (!src[0])
		return ;
	while (src[j])
	{
		dest[i++] = src[j++];
		dest[i] = '\0';
	}
}

//sert a joindre buffer et tmp dans buffer rest
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	ft_strcat(result, s1);
	ft_strcat(result, s2);
	return (result);
}

//retourne l index de la premiere occurence
char	*ft_strchr(const char *string, int searchedChar)
{
	if (!string)
		return (NULL);
	while (*string)
	{
		if (*string == (char)searchedChar)
			return ((char *)string);
		string++;
	}
	if (*string == (char)searchedChar)
		return ((char *)string);
	return (NULL);
}
//retourne dans une string malloc seulement la fin
//de la ligne avec le '\n' inclus

char	*ft_substr(char const *s, size_t start, size_t len)
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
