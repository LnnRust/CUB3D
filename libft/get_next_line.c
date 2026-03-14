/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:46:42 by aandreo           #+#    #+#             */
/*   Updated: 2025/10/29 19:58:17 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// Conserve dans tmp le contenu après le premier '\n' et free l'ancienne chaîne
static char	*keep_nextline(char *tmp)
{
	char	*new_tmp;
	char	*newline;
	size_t	index;

	newline = ft_strchr(tmp, '\n');
	if (!newline)
		return (free(tmp), NULL);
	index = (newline - tmp) + 1;
	new_tmp = ft_substr(tmp, index, ft_strlen(tmp) - index);
	free(tmp);
	return (new_tmp);
}

// Extrait la ligne jusqu'au premier '\n' ou la fin de la chaîne
static char	*extract_line(char *tmp)
{
	char	*line;
	char	*newline;
	size_t	len;

	if (!tmp || !*tmp)
		return (NULL);
	newline = ft_strchr(tmp, '\n');
	if (newline)
		len = newline - tmp + 1;
	else
		len = ft_strlen(tmp);
	line = ft_substr(tmp, 0, len);
	return (line);
}

// Lit depuis le file descriptor et join le contenu jusqu a arriver sur un '\n'
static char	*read_and_join(int fd, char *tmp)
{
	char	*buf;
	char	*join;
	ssize_t	bytes_read;

	join = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(tmp, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(tmp), NULL);
		buf[bytes_read] = '\0';
		if (tmp != NULL)
			join = ft_strjoin(tmp, buf);
		else
			join = ft_strjoin("", buf);
		free(tmp);
		tmp = join;
	}
	free(buf);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	tmp = read_and_join(fd, tmp);
	if (!tmp)
		return (NULL);
	line = extract_line(tmp);
	tmp = keep_nextline(tmp);
	return (line);
}

//int	main(void)
//{
//	int		fd;
//	char	*line;

//	fd = open("test.txt", O_RDONLY);
//	if (fd < 0)
//		return (1);
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd);
//	return (0);
//}
