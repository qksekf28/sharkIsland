// prototyping function
#define BOARDSTATUS_OK      1
#define BOARDSTATUS_NOK     0

#define N_BOARD             15
#define N_COINPOS           12
#define MAX_COIN            4

int board_initboard(void);
int board_printBoardStatus(void);

int board_getBoardStatus(int pos);
int board_getBoardCoin(int pos);

int board_getSharkPosition(void); 	
int board_stepShark(void);			// Moving shark
