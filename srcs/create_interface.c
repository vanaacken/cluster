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

int	draw_border(t_img *canvas, int center_x, int center_y)
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
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
				my_mlx_pixel_put(canvas, x, y, BORDER_COLOR);
			x += 1;
		}
		y += 1;
	}
	return (0);
}

int	place_hex(t_img *canvas, int center_x, int center_y, int color)
{
	float corners[6][2];
	float x;
	float y;
	int i = 2;
	draw_border(canvas, center_x, center_y);
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
					my_mlx_pixel_put(canvas, x, y, color);
				else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
					my_mlx_pixel_put(canvas, x, y, color);
				else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
					my_mlx_pixel_put(canvas, x, y, color);
				else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
					my_mlx_pixel_put(canvas, x, y, color);
				else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
					my_mlx_pixel_put(canvas, x, y, color);
				else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
					my_mlx_pixel_put(canvas, x, y, color);
				x++;
			}
			y++;
		}
		i++;
	}
	return (0);
}

void	color_bg(t_img *canvas)
{
	int x;
	int y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			my_mlx_pixel_put(canvas, x, y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}

// int	find_start_x(int total_cols)
// {
// 	int start_x = (total_cols / 2) * g_size; 
// }



int is_hex_center(float q, float r, float x, float y)
{
	float x1 = ((float)3/2 * (float)q);
	float y1 = (((float)sqrt(3)/2) * q) +((float)sqrt(3) * ((float)r));
	x1 *= (g_size + PADDING);
	y1 *= (g_size + PADDING);
	x1 += 500;
	y1 += 500;
	if (x >= x1 - EPSILON && x <= x1 + EPSILON && y >= y1 - EPSILON && y <= y1 + EPSILON)
		return (1);

	return (0);
}





int is_in_grid(float x, float y)
{
	for (int q = -SIZE + 1; q < SIZE; q++)
	{
		int column_len = (2*SIZE -1 - abs(q));
		int r = fmax(-SIZE + 1, -SIZE + 1 - q);
		for (float i = column_len - 1; i >= 0; i-=1)
		{
			// is_hex_center(q, r + i, x, y);
			float x1 = ((float)3/2 * (float)q);
			float y1 = (((float)sqrt(3)/2) * q) +((float)sqrt(3) * ((float)r + i));
			x1 *= (g_size +PADDING);
			y1 *= (g_size +PADDING);
			x1 += 500;
			y1 += 500;
			if (x >= x1 - EPSILON && x <= x1 + EPSILON && y >= y1 - EPSILON && y <= y1 + EPSILON )
				return (1);
		}
	}
	return (0);
}

void draw_hex(t_img *canvas, float q, float r, float x, float y)
{
		float x1 = ((float)3/2 * (float)q);
		float y1 = (((float)sqrt(3)/2) * q) +((float)sqrt(3) * ((float)r));
		x1 *= (g_size +PADDING);
		y1 *= (g_size +PADDING);
		x1 += 500;
		y1 += 500;

		if (x >= x1 - EPSILON && x <= x1 + EPSILON && y >= y1 - EPSILON && y <= y1 + EPSILON )
			place_hex(canvas, x + g_size, y + g_size, 0xbf2000);
		// 	return (1);
}


int g_total_cols = 9;
int g_total_rows = 17;

int	create_grid(t_img *canvas)
{

	// float x = 0;
	// float y = 0;
	// float w = 2 * g_size;
	// float h = sqrt(3) * g_size;
	// int row = 0;
	// int col = 0;

	// float	start_x = 499 - ((g_total_cols / 2) * (w * 3/4) + (w * 3/4) / 2);
	color_bg(canvas);
	// y = 499 - ((g_total_rows / 2) * g_size);
	for (size_t y_index = 0; y_index < 1000; y_index++)
	{
		for (size_t x_index = 0; x_index < 1000; x_index++)
		{
			if(is_in_grid(x_index, y_index))
			{
				place_hex(canvas, x_index + g_size, y_index + g_size, BACKGROUND_COLOR);
				draw_hex(canvas, 0,0,x_index,y_index);
			}
		}
	}
		
	return (0);

	
	// while (row < g_total_rows)
	// {
	// 	x = start_x;
	// 	col = 0;
	// 	if (row % 2 != 0)
	// 	{
	// 		col++;
	// 		x += w * 3/4;
	// 	}
	// 	while (col < g_total_cols)
	// 	{
	// 		if (row >= 0 && row <= 16 && col == 4)
	// 			place_hex(canvas, x + g_size, y + g_size, BACKGROUND_COLOR);
	// 		else if (row >= 1 && row <= 15 && col >= 2 && col <= 6)
	// 			place_hex(canvas, x + g_size, y + g_size, BACKGROUND_COLOR);
	// 		else if (row >= 3 && row <= 13 && col >= 0 && col <= 8)
	// 			place_hex(canvas, x + g_size, y + g_size, BACKGROUND_COLOR);
	// 		if (row == 16 && col == 4)
	// 			place_hex(canvas, x + g_size, y + g_size, 0xbf2000);
	// 		x += g_size * 3;
	// 		col += 2;
	// 	}
	// 	row++;
	// 	y += h / 2;
	// }
	// return (0);
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

