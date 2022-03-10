// #include "cluster.h"
#include "../includes/cluster.h"

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

int	draw_border(mlx_image_t *canvas, int center_x, int center_y)
{
	float corners[6][2];
	determine_hex_corners(&corners, center_x, center_y, G_SIZE);
	float y = center_y - G_SIZE;
	float x;
	while (y < center_y + G_SIZE)
	{
		x = center_x - G_SIZE;
		while (x < center_x + G_SIZE)
		{
			if (is_line(x, y, corners[2][0], corners[1][0], corners[2][1], corners[1][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
				mlx_put_pixel(canvas, x, y, BORDER_COLOR);
			x += 1;
		}
		y += 1;
	}
	return (0);
}

int	place_hex(mlx_image_t *canvas, int center_x, int center_y, int color)
{
	float corners[6][2];
	float x;
	float y;
	int i = 2;
	draw_border(canvas, center_x, center_y);
	while (i != G_SIZE)
	{
		y = center_y - G_SIZE - i;
		while (y <= center_y + G_SIZE - i)
		{
			determine_hex_corners(&corners, center_x, center_y, G_SIZE - i);
			x = center_x - G_SIZE - i;
			while (x <= center_x + G_SIZE - i)
			{
				if (is_line(x, y, corners[2][0], corners[1][0], corners[2][1], corners[1][1]))
					mlx_put_pixel(canvas, x, y, color);
				else if (is_line(x, y, corners[4][0], corners[5][0], corners[4][1], corners[5][1]))
					mlx_put_pixel(canvas, x, y, color);
				else if (is_line(x, y, corners[3][0], corners[2][0], corners[3][1], corners[2][1]))
					mlx_put_pixel(canvas, x, y, color);
				else if (is_line(x, y, corners[5][0], corners[0][0], corners[5][1], corners[0][1]))
					mlx_put_pixel(canvas, x, y, color);
				else if (is_line(x, y, corners[3][0], corners[4][0], corners[3][1], corners[4][1]))
					mlx_put_pixel(canvas, x, y, color);
				else if (is_line(x, y, corners[1][0], corners[0][0], corners[1][1], corners[0][1]))
					mlx_put_pixel(canvas, x, y, color);
				x++;
			}
			y++;
		}
		i++;
	}
	return (0);
}

void	color_bg(mlx_image_t *canvas)
{
	int x;
	int y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			mlx_put_pixel(canvas, x, y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}

int is_hex_center(float q, float r, float x, float y)
{
	float x1 = ((float)3/2 * (float)q);
	float y1 = (((float)sqrt(3)/2) * q) +((float)sqrt(3) * ((float)r));
	x1 *= (G_SIZE + PADDING);
	y1 *= (G_SIZE + PADDING);
	x1 += OFFSET_WINDOW;
	y1 += OFFSET_WINDOW;
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
			x1 *= (G_SIZE +PADDING);
			y1 *= (G_SIZE +PADDING);
			x1 += OFFSET_WINDOW;
			y1 += OFFSET_WINDOW;
			if (x >= x1 - EPSILON && x <= x1 + EPSILON && y >= y1 - EPSILON && y <= y1 + EPSILON )
				return (1);
		}
	}
	return (0);
}

void draw_hex(mlx_image_t *canvas, float q, float r, int color)
{
		float x = ((float)3/2 * (float)q);
		float y = (((float)sqrt(3)/2) * q) +((float)sqrt(3) * ((float)r));
		x *= (G_SIZE +PADDING);
		y *= (G_SIZE +PADDING);
		x += OFFSET_WINDOW;
		y += OFFSET_WINDOW;
		place_hex(canvas, x + G_SIZE, y + G_SIZE, color);
}


int g_total_cols = 9;
int g_total_rows = 17;

int	create_grid(mlx_image_t *canvas)
{
	for(int q = -SIZE + 1; q < SIZE; q++)
	{
		int r = fmax(-SIZE + 1, -SIZE + 1 - q);
		int column_len = (2*SIZE -1 - abs(q));
		for (int i = column_len - 1; i >= 0; --i)
		{
			draw_hex(canvas, q, r+ i, BACKGROUND_COLOR);
			t_axial tmp;
			tmp.q = q;
			tmp.r = r + i; 
			t_hex *tmp_hex = search(tmp);
			if (tmp_hex)
				draw_hex(canvas, q, r + i, tmp_hex->color);
		}
	}
	// for (size_t y_index = 0; y_index < 1000; y_index++)
	// {
	// 	for (size_t x_index = 0; x_index < 1000; x_index++)
	// 	{
	// 		if(is_in_grid(x_index, y_index))
	// 		{
	// 			place_hex(canvas, x_index + G_SIZE, y_index + G_SIZE, BACKGROUND_COLOR);
	// 		}
	// 	}
	// }
	return (0);
}

static mlx_t	*mlx;

void	rotate_tiles(mlx_key_data_t keydata, void *param)
{
	mlx_image_t *canvas = param;

	(void) keydata;
	create_grid(canvas);
	mlx_image_to_window(mlx, canvas, 0, 0);
	rotate_cluster(2);
}

int	create_interface(void)
{

	mlx_image_t	*canvas;

	mlx = mlx_init(1000, 1000, "CLUSTER", true);
	canvas = mlx_new_image(mlx, 1000, 1000);
	color_bg(canvas);
	mlx_key_hook(mlx, rotate_tiles, canvas);
	mlx_loop(mlx);
	return (0);
}

// int main(void)
// {
// 	create_interface();
// }
