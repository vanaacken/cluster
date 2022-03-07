#include "../includes/cluster.h"



#define MAX_PLAYER 2
#define HASH_SIZE 50













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



t_hex* hash_array[HASH_SIZE];
t_hex* hex;
t_hex* dummy_hex;

int hash(t_axial key)
{
	return (abs(key.q) * 10 + abs(key.r)) % HASH_SIZE;
}

bool compare_axial(t_axial lhs, t_axial rhs)
{
	return (lhs.q == rhs.q && lhs.r == rhs.q);
}

t_hex *search(t_axial key)
{
	int hash_index = hash(key);
	while(hash_array[hash_index] != NULL)
	{
		if (compare_axial(hash_array[hash_index]->axial, key))
		{
			return (hash_array[hash_index]);
		}
		++hash_index;
		hash_index %= HASH_SIZE;
	}	
	return NULL;
}

void insert(t_axial key, int color)
{
	t_hex *hex = (t_hex*)malloc(sizeof(t_hex));
	hex->axial = key;
	hex->color = color;
	int hash_index = hash(key);
	while(hash_array[hash_index] != NULL && hash_array[hash_index]->axial.q != -1)
	{
		++hash_index;
		hash_index %= HASH_SIZE;
	}
	hash_array[hash_index] = hex;
}

t_hex * delete(t_hex *hex)
{
	int hash_index = hash(hex->axial);
	while (hash_array[hash_index] != NULL)
	{
		if (compare_axial(hash_array[hash_index]->axial, hex->axial))
		{
			t_hex* tmp = hash_array[hash_index];
			hash_array[hash_index] = dummy_hex;
			return (tmp);
		}
		++hash_index;
		hash_index %= HASH_SIZE;
	}
	return NULL;
}

void display_hash_array()
{
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (hash_array[i] != NULL)
		{
			printf("[Axial:(%d, %d); Color: %d]\n", hash_array[i]->axial.q, hash_array[i]->axial.r, hash_array[i]->color);
		}
		else
		{
			printf(" ~~ \n");
		}
	}
}


void init_hash_array()
{
	dummy_hex = (t_hex*)malloc(sizeof(t_hex));
	dummy_hex->axial.q = -1;
}


void insert_new_hex(int q, int r, int color)
{
	t_axial ret;
	ret.q = q;
	ret.r = r;
	insert(ret, color);
}


int main(int argc, const char* argv[])
{

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
	insert_new_hex(1,3,1);
	insert_new_hex(2,3,1);
	insert_new_hex(3,3,2);
	insert_new_hex(4,3,2);
	insert_new_hex(5,3,2);
	insert_new_hex(5,4,3);
	insert_new_hex(5,5,3);
	insert_new_hex(5,6,1);
	insert_new_hex(5,7,2);
	display_hash_array();
	




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
    (void)players;
}








