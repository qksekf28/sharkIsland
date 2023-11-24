#include <stdio.h>
#include <stdlib.h>
#include "board.h"
// EACH POSITION STATE(DESTROYED, COIN etc)
// STATE of SHARK

// MACRO setting

#define MAX_SHARKSTEP       6
#define SHARK_INITPOS      -4

// 1. set VARIABLE
static int board_status[N_BOARD];
static int board_coin[N_BOARD];

static int board_sharkPosition = SHARK_INITPOS; // Initialize shark position;     // need saving one number

int board_initboard(void)
{
    int i;
    for (i=0;i<N_BOARD;i++)         // RESET board_state & board_coin
    {   
        board_status[i] = BOARDSTATUS_OK;
        board_coin[i] = 0;
        // assign coin
    }
    

    for (i=0;i<N_COINPOS;i++)
    {
        int flag = 0;                           // good tip to escape while
        while(flag == 0)
        {
            int allocPos = rand()%N_BOARD;
            if (board_coin[allocPos] == 0)      // not allocate
            {
                board_coin[allocPos] = rand() % (MAX_COIN + 1);      // allocate COIN
                flag = 1;           // --> escape WHILE
            }
        }
    }
    return 0;   // right?
}
int board_printBoardStatus(void)      // different w/ game status
{
    int i;
    printf("---------------------BOARD STATUS----------------------\n");
    for (i=0; i<N_BOARD; i++)
    {
        printf("|");
        if (board_status[i] == BOARDSTATUS_NOK)         // DESTROY
            printf("X");
        else
            printf("O");                                // NOT DESTROY
    }
    printf("|\n");
    printf("------------------------------------------------------\n");

    return 0;
}



int board_getBoardStatus(int pos)       // DESTROY or NOT
{
    return board_status[pos];
}

int board_getBoardCoin(int pos)         // need RESET
{
    int coin = board_coin[pos];     // need LOCAL variable
    board_coin[pos] = 0;
    return coin;
}

int board_getSharkPosition(void)
//int board_sharkPosition(void)
{
    int step = rand()%MAX_SHARKSTEP + 1;
    int i;
    for (i = board_sharkPosition + 1; i <= board_sharkPosition + step; i++)
    {
        if (i>=0 && i<N_BOARD)
        board_status[i] = BOARDSTATUS_NOK;
    }

    board_sharkPosition += step;

    return board_sharkPosition;
}

int board_stepShark(void)         // Moving shark
{
    // Implement shark movement logic
    return 0;
}
