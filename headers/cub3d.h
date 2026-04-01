#pragma once

#include "../libft/libft.h"
#include "../libft/get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>

# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3
# define TEX_DOOR	4
# define TEX_SPRITE	5
# define TEX_COUNT	6

typedef struct s_door
{
	int		x;
	int		y;
	bool	open;
}	t_door;

/* Single sprite on the map (bonus) */
typedef struct s_sprite
{
	int		x;
	int		y;
}	t_sprite;

// enum to track .cub file parsing status
typedef enum e_status
{
	BEFORE_CONTENT,
	IN_CONFIG,
	IN_MAP,
}	e_status;

/* Everything about the parsed map */
typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
	char		*tex_path[TEX_COUNT];
	int			floor_color[3];
	int			ceil_color[3];
	int			door_count;
	t_door		*doors;
	int			sprite_count;
	t_sprite	*sprites;
}	t_map;

/* Player start info — filled during parsing */
typedef struct s_player
{
	int		x;
	int		y;
	char	direction;	/* N / S / E / W */
}	t_player;

/* Master struct — only what parsing needs for now */
typedef struct s_game
{
	t_map		*map;
	t_player	*player;
}	t_game;


void	flood_fill(char **map, int x, int y);
bool	check_floodfill(char **map);
void	set_playerpos(char **map, t_game *game);
void	set_doorpos(char **map, t_game *game);
void 	free_game(t_game *game);
void	free_map(char **map);
char	**extract_file_content(char *map_filename);
char	*get_texture_path(char **map, char *texture);
