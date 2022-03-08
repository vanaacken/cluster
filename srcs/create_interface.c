// #include "cluster.h"
#include "../includes/cluster.h"

int	g_size = 50;

t_img	create_img(t_vars *vars, int w, int h)
{
	t_img	img;

	img.img = mlx_new_image(vars->mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

float	determine_hex_corners(float (*corners)[6][2], int center_x, int center_y, int size)
{
	float angle_deg;
	float angle_rad;
	int i = 0;

	while (i < 6)
	{
		angle_deg = 60 * i;
		angle_rad = M_PI / 180 * angle_deg;
		(*corners)[i][0] = center_x + size * cos(angle_rad);
		(*corners)[i][1] = center_y + size * sin(angle_rad);
		// printf("%d = {%f, %f}\n", i, (*corners)[i][0], (*corners)[i][1]);
		// my_mlx_pixel_put(canvas, (*corners)[i][0], (*corners)[i][1], 0x483d8b);
		i++;
	}
	return (0);
}

bool	is_line(float x, float y, float x1, float x2, float y1, float y2)
{
	float delta = (y2 - y1) / (x2 - x1);
	float intercept = y1 - delta * x1;
	return (x <= x2 && x >= x1 && y <= delta * x + intercept + 2 && y >= delta * x + intercept - 2);
}

int	draw_one_hex(t_img *canvas, int center_x, int center_y)
{
	float corners[6][2];
	determine_hex_corners(&corners, center_x, center_y, g_size);
	float y = center_y - g_size;
	float x;
	while (y < center_y + g_size)
	{
		x = center_x - g_size;
		while (x < center_x + g_size)
		{
			if (is_line(x, y, corners[2][0], corners[1][0], corners[2][1], corners[1][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
				my_mlx_pixel_put(canvas, x, y, 0x483d8b);
			x += 1;
		}
		y += 1;
	}
	return (0);
}

int	create_grid(t_img *canvas)
{
	float x;
	float y = 0;
	int row = 0;
	float w = 2 * g_size;
	float h = sqrt(3) * g_size;

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
	y = 0;
	while (y < 1000 - (g_size + (g_size / 5)))
	{
		x = 0;
		if (row % 2 != 0)
			x += w * 3/4;
		while (x < 1000 - g_size)
		{
			if (y >= h/2 * 2 && y <= h/2 * 19 && x == (g_size * 3) * 3)
				draw_one_hex(canvas, x + g_size, y + g_size);
			else if (y >= h/2 * 3 && y <= h/2 * 17 && (x >= (w * 3/4) * 4 && x <= (w * 3/4) * 8))
				draw_one_hex(canvas, x + g_size, y + g_size);
			else if (y >= h/2 * 5 && y <= h/2 * 15 && x >= (g_size * 3) && x <= (g_size * 3) * 5)
				draw_one_hex(canvas, x + g_size, y + g_size);
			x += g_size * 3;
		}
		row++;
		y += h / 2;
	}
	return (0);
}

int	place_hex(t_img *canvas, int center_x, int center_y)
{
	float corners[6][2];
	float x;
	float y;
	int i = 10;
	while (i != g_size)
	{
		y = center_y - g_size - i;
		while (y <= center_y + g_size - i)
		{
			determine_hex_corners(&corners, center_x, center_y, g_size - i);
			x = center_x - g_size - i;
			while (x <= center_x + g_size - i)
			{
				if (is_line(x, y, corners[2][0], corners[1][0], corners[2][1], corners[1][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
					my_mlx_pixel_put(canvas, x, y, 0xbf2000);
				x += 1;
			}
			y += 1;
		}
		i += 1;
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
	place_hex(&canvas, (g_size * 3) * 3, (sqrt(3) * g_size)/2 * 19);
	mlx_put_image_to_window(vars.mlx, vars.win, canvas.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}

int main(void)
{
	create_interface();
}