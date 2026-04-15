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
	MAP_ENDED,
	ERROR,
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
int		skip_whitespaces(char *line, int i);
int		count_doors(char **map);
char	**copy_map(char **map);
bool	is_map_char(char line);
char	**extract_file_content(char *map_filename);
size_t	find_len(char *path, size_t j);
int		get_texture_index(char *line, int i);
char	*get_texture_path(char **map, char *texture);
bool	is_xpm_file(char *line);
bool	parse_texture_line(char *line, t_map *map);
bool	parse_color_line(char *line, t_map *map);
bool	extract_rgb_code(t_map *map, char *line, int i, char code);
bool	is_config_line(char *line);
bool	init_is_finished(t_map *map);
e_status	get_state(char *content, e_status state);
char		**extract_map(char **content);
bool		parse_map(t_game *game, char **av);
