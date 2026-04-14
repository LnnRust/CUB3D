#include "cub3d.h"

bool    init_is_finished(t_map *map)
{
    if(map->ceil_color[0] == -1 || map->floor_color[0] == -1)
        return (ft_putstr_fd("RGB code not filled\n", 2), false);
    if(map->height == -1 || map->width == -1 || map->map == NULL)
        return (ft_putstr_fd("map data not filled\n", 2), false);
    if(map->tex_path[0] == -1)
        return (ft_putstr_fd("Textures not found\n", 2), false);
    if(map->doors == NULL)
        return (ft_putstr_fd("\n", 2), false);
    if(map->sprites == NULL || map->sprite_count == -1)
        return (ft_putstr_fd("Sprites not init\n", 2), false);
    return (true);
}       