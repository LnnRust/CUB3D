/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 13:38:18 by aandreo           #+#    #+#             */
/*   Updated: 2026/03/30 14:16:13 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static void	remove_backslash(char *line)
{
	if(!line)
		return ;
	if(line[0] == '\0')
		return ;
	if(line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
}

static char **add_line(char **final, char *line)
{
	int count;
	char **new;
	int i;

	count = 0;
	while(final && final[count])
	count++;
	new = malloc(sizeof(char *) * (count + 2));
	if(!new)
	return (NULL);
	if(final == NULL)
	{
		new[0] = line;
		new[1] = NULL;
		return (new);
	}
	i = 0;
	while(final[i])
	{
		new[i] = final[i];
		i++;
	}
	free(final);
	new[count] = line;
	new[count + 1] = NULL;
	return new;
}

char	**extract_file_content(char *map_filename)
{
	int		fd;
	char	*line;
	char	**final;

	final = NULL;
	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while((line = (get_next_line(fd))))
	{
		remove_backslash(line);
		final = add_line(final, line);
	}
	return (close(fd), final);
}
