#include "../hdr/GameLogic.h"


int main()
{
	gameLogic game;

	while (1)
	{
		game.gameLoop();
	}
}

//#include "xil_printf.h"
//#include "stdio.h"
//#include "stdlib.h"
//
//int main()
//{
//	int random;
//
//	while(1)
//	{
//		random=rand()%1000 + 1;
//		xil_printf ("random: %d", random);
//		xil_printf("\n\r");
//	}
//}

