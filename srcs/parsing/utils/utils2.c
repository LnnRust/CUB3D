#include "cub3d.h"

bool	init_is_finished(t_map *map)
{
	int i;
	i = 0;
	while(i < 3)
	{
		if(map->ceil_color[i] == -1)
			return (ft_putstr_fd("RGB code not filled\n", 2), false);
		i++;
	}
	i = 0;
	while(i < 3)
	{
		if(map->floor_color[i] == -1)
			return (ft_putstr_fd("RGB code not filled\n", 2), false);
		i++;
	}
	i = 0;
	while(i < 4)
	{
		if(map->tex_path[i] == NULL)
			return (ft_putstr_fd("Textures not found\n", 2), false);
		i++;
	}
	return (true);
}
