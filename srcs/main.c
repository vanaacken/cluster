#include "../includes/cluster.h"
#include <math.h>


#define MAX_PLAYER 2
#define HASH_SIZE 130













//WARNING: This is a dirty EXAMPLE.
//       It is not safe and should not be used like this.
//       It is only here to give one idea of how to communicate with bots with something usable by any bot.
//       You can choose to use any other way - even hardcoded function ? 
//       You can use pipes, sockets, shared mem... you name it.
//       You will need to show and explain how bots will communicate with your game implementation.
// This example use pipes to communicate with bots.
// the good thing is with small modifications you can execute any kind of bots that can read stdin and write on stdout will work.
// being python / rust / C++ or whatever (not JS it's not a language you better use brainfuck...)

//+[----->+++<]>+.++++++++++++..----.+++.+[-->+<]>.-----------..++[->++<]>.+++++++.+++++++++++.[++>---<]>.--[-->+++++<]>--.-[--->+<]>.-[----->++<]>-.++++.[--->++++<]>-.--[--->+<]>.>+[--->++<]>++.----------.-[--->+<]>++.>-[--->+<]>.>++++++++++..



t_hash_item* hash_array[HASH_SIZE];
t_hash_item* item;
t_hash_item* dummy_item;
t_hex* hex;
t_hex* dummy_hex;


int hash(t_axial key)
{
	return ((key.q+SIZE) * 13 + (key.r+SIZE) * 23) % HASH_SIZE;
}

bool compare_axial(t_axial lhs, t_axial rhs)
{
	return (lhs.q == rhs.q && lhs.r == rhs.r);
}

t_hex *search(t_axial key)
{

	int hash_index = hash(key);
	while(hash_array[hash_index] != NULL)
	{
		if (compare_axial(hash_array[hash_index]->hex->axial, key))
		{
			return (hash_array[hash_index]->hex);
		}
		++hash_index;
		hash_index %= HASH_SIZE;
	}	
	return NULL;
}

int insert(t_axial key, int color)
{
	t_hex *hex = (t_hex*)malloc(sizeof(t_hex));
	t_hash_item *item = (t_hash_item*)malloc(sizeof(t_hash_item));
	hex->axial = key;
	hex->color = color;
	item->hex = hex;
	item->next = NULL;
	int hash_index = hash(key);
	if (hash_array[hash_index] == NULL)
	{
		hash_array[hash_index] = item;
	}
	else
	{
		t_hash_item *tmp = hash_array[hash_index];
		while(tmp->next != NULL)
		{
			if (compare_axial(tmp->hex->axial, hex->axial))
			{
				free(hex);
				free(item);
				return 0;
			}
			tmp = tmp->next;
		}
		if (compare_axial(tmp->hex->axial, hex->axial))
		{
			free(hex);
			free(item);
			return 0;
		}
		tmp->next = item;
	}
	return 1;
}

int delete(t_axial key)
{
	int hash_index = hash(key);
	t_hash_item *tmp;
	t_hash_item *prev;
	if (hash_array[hash_index] == NULL)
		return 0;
	tmp = hash_array[hash_index];
	if (compare_axial(hash_array[hash_index]->hex->axial, key))
	{
		hash_array[hash_index] = hash_array[hash_index]->next;
		free(tmp->hex);
		free(tmp);
		return (1);
	}
	prev = tmp;
	tmp = tmp->next;
	while(tmp)
	{
		if (compare_axial(tmp->hex->axial, key))
		{
			prev->next = tmp->next;
			free(tmp->hex);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);

}

void display_hash_array()
{
	int n = 0;
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (hash_array[i] != NULL)
		{
			t_hash_item *tmp = hash_array[i];
			while (tmp != NULL)
			{
				printf("[Axial:(%d, %d); Color: %d] ;", tmp->hex->axial.q, tmp->hex->axial.r, tmp->hex->color);
				tmp = tmp->next;
				n++;
			}
		}
		else
		{
			printf(" ~~");
		}
		printf("\n");
	}
	printf("total fille: %d\n", n);

}


void init_hash_array()
{
	dummy_item = (t_hash_item*)malloc(sizeof(t_hash_item));
	dummy_hex = (t_hex*)malloc(sizeof(t_hex));
	dummy_hex->axial.q = -1;
	dummy_item->hex = dummy_hex;
}








int insert_in_column(int column)
{
	t_axial axial;
	axial.q = column;
	axial.r = fmax(-SIZE + 1, -SIZE + 1 - axial.q);
	int column_len = (2*SIZE -1 - abs(column));
	printf("column: %d len: %d;\n", column, column_len);
	for (int i = column_len - 1; i >= 0; --i)
	{
		// coordinates[axial.q + SIZE - 1][2 * axial.r + axial.q + SIZE - 1] = 0;
		printf("[%d, %d] ;", axial.q, axial.r + i);
	}
	printf("\n");

	
	return 1;
}



int main(int argc, const char* argv[])
{
	(void)argc;
    // if (argc != 3)
    // {
    //     printf("Usage: %s <player1_exe> <player2_exe>\n", argv[0]);
    //     return 1;
    // }
    t_player players[MAX_PLAYER] = {0};
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        init_player(argv[i+1], &players[i]);
    }
	init_hash_array();



	t_axial tmp;
	for (int i = -4; i < 4; i++)
	{
		for (int j = -4; j < 4; j++)
		{
			tmp.q = i;
			tmp.r = j;
			insert(tmp, 1);
		}
		
	}
	
	insert_in_column(-4);
	// int n = 0;
	// for (int i = -SIZE + 1; i < SIZE; i++)
	// {
	// 	for (int j = -SIZE + 1; j < SIZE; j++)
	// 	{
	// 		insert_in_column(i,j,1);
	// 		n++;
	// 	}
	// }
	display_hash_array();

	

	create_interface();



    int winner = 0;
    while (!winner)
    {
        //TURN FOR EACH PLAYER
        //TODO : Create the game check if the move is legal / possible
        //TODO Create the commands list/ protocol
        //TODO Send the state of the game to the player
        //TODO win condition
        //TODO timeout for each player
        //TODO everyhing else :D
        //TODO Make the all thing safe enough so that the bot can crash without you crashing with it :D

        for (int i = 0; i < MAX_PLAYER; i++)
        {
            char* line = NULL;
            size_t len = 0;
            const t_player* player = &players[i];
            //send board state to the player
            dprintf(player->stdin[STDOUT_FILENO], "Player %d - game state very interesting\n", i);
            //read player move from the pipes
            getline(&line, &len, player->reader);
            printf("Player %d - move: %s", i, line);
            free(line);
        }
        winner = 1;//Ez game
    }
    printf("Game over\n");
	// comments
    (void)players;
}








