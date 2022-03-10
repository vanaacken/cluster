#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// # include "../mlx/mlx.h"
# include <math.h>
# include "color.h"
# include "../MLX42/include/MLX42/MLX42.h"

#define SIZE 5
#define N_COLORS 2

#define SUCCES 1
#define ERROR 0

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_cube{
	int q;
	int r;
	int s;
} 			t_cube;

typedef struct s_axial{
	int q;
	int r;
}			t_axial;

typedef struct s_color{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_hex{
	t_axial axial;
	int color;
	bool sentinel;
}		t_hex;

typedef struct s_supply{
	int *colors; // array of colors; dependend of game
} t_supply;

typedef struct s_player
{
    pid_t pid;
    int stdin[2];
    int stdout[2];
    FILE* reader;
} t_player;

typedef struct s_data{
	// t_hex		grid[][];
	t_player	player_1;
	t_player	player_2;
} t_data;




int init_player(const char* path, t_player * player);
// int init_grid(t_hex *grid[][]);
int init_data(t_data *data);

//my_pixel_put
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_interface(void);




#endif