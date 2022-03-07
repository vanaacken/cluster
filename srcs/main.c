#include "../includes/cluster.h"



int initPlayer(t_player *player, bool first)
{
	player->first = first;


	return SUCCES;
}

int initGrid(t_hex ***grid)
{
	*grid = (t_hex **)malloc(sizeof(t_hex *) * ((SIZE * 4 - 3)+ 1));
	for (size_t i = 0; i < (SIZE*4-3); i++)
	{
		*grid[i] = malloc(sizeof(t_hex) * ((SIZE * 4 - 3)));
	}
	

	return SUCCES;
}

int initData(t_data *data)
{
	initPlayer(&(data->player_1), true);
	initPlayer(&(data->player_2), false);
	initGrid(&(data->grid));

	return (SUCCES);
}



int main(void)
{
	
	
	// Init
	t_data data;
	initData(&data);
	// Game loop







	return (0);
}













