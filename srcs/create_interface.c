// #include "cluster.h"
#include "../includes/cluster.h"

t_img	create_img(t_vars *vars, int w, int h)
{
	t_img	img;

	img.img = mlx_new_image(vars->mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

// int	draw_one_hex(t_vars *vars)
// {
// 	int size = 40;
// 	int w = 2 * size;
// 	int h = sqrt(3) * size;


// }

int	create_grid(t_img *canvas)
{
	int x;
	int y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			my_mlx_pixel_put(canvas, x, y, 0xfaebd7);
			x++;
		}
		y++;
	}
	return (0);
}

int	create_interface(void)
{
	t_vars	vars;
	t_img	canvas;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "CLUSTER");
	canvas = create_img(&vars, 1000, 1000);
	create_grid(&canvas);
	mlx_put_image_to_window(vars.mlx, vars.win, canvas.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}

int main(void)
{
	create_interface();
}