#include "../includes/cluster.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>





#define MAX_PLAYER 2



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


int main(int argc, const char* argv[])
{

    if (argc != 3)
    {
        printf("Usage: %s <player1_exe> <player2_exe>\n", argv[0]);
        return 1;
    }
    player_t players[MAX_PLAYER] = {0};
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        init_player(argv[i+1], &players[i]);
    }

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
            const player_t* player = &players[i];
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








