#include <stdio.h>
#include <stdlib.h>
#include <time.h> // added
#include "board.h" // just like paste board.h contents

#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1		//
#define PLAYERSTATUS_END	2		//

#define	N_PLAYER		4
#define MAX_DIE			6
#define MAX_CHARNAME 	200



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME]; // ���߹迭 
int player_coin[N_PLAYER];
int player_status[N_PLAYER];					// 0 - live, 1 - die, 2 - end
char player_statusString[3][MAX_CHARNAME] = {"LIVE", "DIE", "END"};


void opening(void)
{
	printf("===========|================/===========\n");	
	printf("=========O   ===============   O========\n");
	printf("========================================\n");
	printf("=====MMMMMMMMMMMMMMMMMMMMMMMMMMMM=======\n");
	printf("============SHARK=====ISLAND============\n");
	printf("=====VVVVVVVVVVVVVVVVVVVVVVVVVVVV=======\n");
	printf("========================================\n");
}

int rolldie(void)
{
	return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if (i == player_position[player])
			printf("%c", player_name[player][0]);
		else
		{
			if (board_getBoardStatus)
				print("X");
			else
				print(" ");
		}
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	printf("player status ===\n");
	for (i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos %i, coin %i, status %s\n",
				player_name[i], player_position[i], player_coin[i],
				player_statusString[player_status[i]]);
			printPlayerPosition(i);
	}
	printf("-----------------\n");
}

void checkDie(void)
{
	int i;
	for (i=0; i<N_PLAYER; i++)
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
			player_status[i] = PLAYERSTATUS_DIE;
}


int main(int argc, char *argv[])
{
	int i;
	int pos=0;
	srand((unsigned)time(NULL));		// for random
	
	// 0. opening design
	opening();	
	
	// 1. RESET & set PLAYER NAME
	// 1-1. INITIALIZE BOARD
	board_initboard();

	// 1-2. INITIALIZE PLAYER
	for (i=0; i<N_PLAYER; i++)
	{
		player_position[i] = 0;
		player_coin[i]	= 0;
		player_status[i] = PLAYERSTATUS_LIVE;
		// player_name
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
	}


	// 2. REPEAT (PLAYER TURN)
	do {
		int turn;		// not sure...
		int step;
		int coinResult;
		char c;

		if (player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn + 1)%N_PLAYER;			// without it, player is not change
			continue;
		}

		
		/*
		board_printBoardStatus(); 			  -> 2-1

		pos += step;						  -> 2-3			
		coinResult = board_getBoardCoin(pos);
		
		printf("press any key to continue:"); -> 2-2
		scanf("%d", &c);
		fflush(stdin);
		*/

		// 2-1. DISPLAY PLAYER STATE
		board_printBoardStatus();
		for (i=0;i<N_PLAYER;i++)
			printPlayerPosition(i);
		printPlayerStatus();


		// 2-2. ROLL a DIE
		printf("%s turn!! ", player_name[turn]);
		printf("press any key to roll a die! \n");
		scanf("%d", &c);
		fflush(stdin);
		step = rolldie();


		// 2-3. MOVE
		player_position[turn] += step;
		if (player_position[turn] >= N_BOARD)
		{
			player_position[turn] = N_BOARD-1;
		}
		if (player_position[turn] == N_BOARD-1)
			player_status[turn] = PLAYERSTATUS_END;
		//printf()

		// 2-4. COIN
		coinResult = board_getBoardCoin(pos);
		player_coin[turn] += coinResult;
		//printf()

		// 2-5. NEXT TURN
		turn = (turn + 1)%N_PLAYER; 	//wrap around

		// 2-6. SHARK ACTION, IF (CONDITION : WHEN EVERYONE DONE) 
		if (turn == 0)
		{
			// SHARK ACTION
			int shark_pos = board_stepShark();
			//printf();
			checkDie();
		}
	}	while(1);

	// 3. ENDING CALCULATION (WINNER, COIN)
	int game_end(void)
	{
		int i;
		int flag_end = 1;

		//if all the players are died?
		for (i=0; i<N_PLAYER; i++)
		{
			if (player_status[i] == PLAYERSTATUS_LIVE)
			{
				flag_end = 0;
				break;
			}
		}
		return flag_end;
	}

	int getAlivePlayer(void)
	{
		int i;
		int cnt = 0;
		for (i=0; i<N_PLAYER; i++)
		{
			if (player_status[i] == PLAYERSTATUS_END)
				cnt++;
		}
		return cnt;
	}

	int getWinner(void)
	{
		int i;
		int winner = 0;
		int max_coin = -1;

		for (i=0; i<N_PLAYER; i++)
		{
			if (player_coin[i] > max_coin)
			{
				max_coin = player_coin[i];
				winner = i;
			}
		}
		return winner;
	}



	system("PAUSE");
	return 0;
}
