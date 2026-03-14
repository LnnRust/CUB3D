/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenech <fbenech@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:46:17 by fbenech           #+#    #+#             */
/*   Updated: 2025/10/23 13:28:03 by fbenech          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *src, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		while (src[i] && src[i] == c)
		{
			i++;
		}
		if (src[i] && src[i] != c)
		{
			count++;
		}
		while (src[i] && src[i] != c)
			i++;
	}
	if (count == 0)
		return (0);
	return (count);
}

static char	*ft_duper(const char *s, char c)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_freesec(char **dest, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free (dest[i]);
		i++;
	}
	free (dest);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	dest = malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!s || !dest)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			dest[j] = ft_duper(&((char *)s)[i], c);
			if (dest[j] == NULL)
				return (ft_freesec(dest, j), NULL);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (dest[j] = NULL, dest);
}

// int main(void)
// {
// 	char **dest;
// 	dest = ft_split("nonempty", '\0');
// 	int i = 0;
// 	while(dest[i])
// 	{
// 		printf("%s\n", dest[i]);
// 		free(dest[i]);
// 		i++;
// 	}
// 	free (dest);
// 	return(0);
// }
