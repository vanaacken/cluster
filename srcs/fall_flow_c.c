#include "cluster.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//create a falling flow using insert and delete, NOT work if the position is 
//in the middle of the map
void fall_flow (t_hex hex_pos)
{
	int original_r = hex_pos.axial.r;
	int hash_index = hash(hex_pos.axial);
	while (hash_array[hash_index] == NULL)
	{
		insert(hex_pos.axial, hex_pos.color);
		if (hex_pos.axial.q - hex_pos.axial.r == original_r)
		{
			hash_array[hash_index] = 1;
			return ; 
		}
		hex_pos.axial.r++;
		hash_index = hash(hex_pos.axial);
		if (hash_array[hash_index] == NULL)
			delete(hex_pos.axial);
	}
	hex_pos.axial.r--;
	hash_array[hash(hex_pos.axial)] = 1;
}

// void column_fall_flow (grid)
// {
// 	for (int i = SIZE * -1; i <= SIZE; i++)
// 	{

// 	}
	
// }

//I don't know if this function already exist 
int	hex_size (void)
{
	int hex_size = 1;
	
	for (int i = 1; i < SIZE; i++)
	{
		hex_size += 6 * i;
		i++;
	}
	return hex_size;
}

//this function calculates number of tiles based on the SIZE and N_COLOR
int	numb_hex_per_color (void)
{
	int tiles = hex_size() / (N_COLORS * 2);
	
	return tiles;
}


int init_player_bucket (t_player* player)
{
	int tiles =	numb_hex_per_color();
	
	for (int i = 0; i < N_COLORS; i++)
		player->bucket[i] = tiles;
	
	return SUCCES;
}

// replace back the unused tile
int put_back_hex(t_player* player, char tile)
{
	int color = tile  - '0';
	player->bucket[color]++;
	return SUCCES;
}


//this function randomly selects a color from a bucket (randomnsess is NOT based on number of tiles in a specific color)
//it automatically removes the tiles from the bucket
int	random_color(t_player *player)
{
	int count = 0;
	for (int i = 0; i < N_COLORS; i++)
		if (player->bucket[i] > 0)
			count++;
	if (count == 0)
		return (-30);
	int color = rand() % (count + 1);
	count = 0;
	for (int i = 0; count != color; i++)
		if (player->bucket[i] > 0)
			count++;
	player->bucket[i]--;
	return i;
}

//return random tiles
char	*random_hex(t_player* player)
{
	char *color= malloc(sizeof(char) *2);
	
	color[0] = '0' + random_color(player);
	color[1] = '0' + random_color(player);
	return color;
}

//this function checks if the tile can be place and than place it or trouw an error
int tile_place(int column, int color)
{
	if (column < 0 || column > SIZE * 2 - 1)
		return ERROR;

	t_hex hex_pos;
	hex_pos.axial.q = column - SIZE;
	hex_pos.color = color;
	if (column < SIZE)
		hex_pos.axial.r = column - 1;
	else
		hex_pos.axial.r = SIZE - 1;

	if (hash_array[hash(hex_pos.axial)] == NULL)
	{	
		fall_flow (hex_pos);
		return 1;
	}
	return ERROR;
}

//take the tile that is a char and return the int value of it
int translate_color(char tile, int player_id)
{
	int color;

	if (player_id)
		color = RED;
	else
		color = BLUE;
	if (tile != '0')
		color += ((int) tile - '0') * 2;
	return color;
}

//wait for the bot input, max time NOT implemented yet
//right input starts the process of inserting the tile in the map and in the hash table
int choose_column_and_place_tile(t_player *player, char tiles)
{
	int column = -1;
	printf("In which column do you want to place the tiles %d? 1 - %d\n", tiles, SIZE * 2 - 1);
	scanf("%d", column);
	if (tile_place(column, translate_color(tiles, player->player_id)))
		return SUCCES;
	return 0;

}

int error_free(char *tiles)
{
	printf ("Invalid imput, you lost yourtiles/n");
	free (tiles);
	return 1;
}

//this function process the input of a player,showing them the which tiles they draw
//and the available move. Wrong move case a inmput error and burn the drawn tiles of the player

int player_input_processing(t_player *player)
{
	char *tiles = random_hex(player);
	int choise;
	int color_one = translate_color(tiles[0], player->player_id);
	if (!tiles[1])
	{	
		printf("You draw your last tiles, the color is %c", color_one);
		if (!choose_column_and_place_tile(player, tiles[0]))
			return (error_free(tiles));
	}
	int color_two = translate_color(tiles[1], player->player_id);
	printf("You draw the colors %d and %d, do you want? r for rotate, to place choose posizion of the color 1 or 2\n", color_one, color_two);
	scanf ("%c", &choise);
	if (choise == 'r')
		todo;
	else if (choise ==  '1' || choise == '2')
	{	
		if(!choose_column_and_place_tile(player, choise))
			return (error_free(tiles));
		if (choise == tiles [0])
			put_back_hex(player, tiles[1]);
		else
			put_back_hex(player, tiles[1]);
	}
	else
		return (error_free(tiles));
	free (tiles);
	return 0;
}
