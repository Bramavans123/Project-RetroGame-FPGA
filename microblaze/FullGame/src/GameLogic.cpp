#include "../hdr/GameLogic.h"

#include "xil_printf.h"
#include "stdio.h"
#include "stdlib.h"


gameLogic::gameLogic()
{
	players[0].id = (entityId::player);
	players[0].size = (10);

	players[1].id = (entityId::player);
	players[1].size = (10);

	candy.id = (entityId::sweet);
	candy.size = 10;

	enemies[0].xPos = 226 - 144;
	enemies[1].xPos = 281 - 144;
	enemies[2].xPos = 333 - 144;
	enemies[3].xPos = 435 - 144;
	enemies[4].xPos = 491 - 144;
	enemies[5].xPos = 594 - 144;
	enemies[6].xPos = 647 - 144;
	enemies[7].xPos = 701 - 144;

	enemies[0].size = 16;
	enemies[1].size = 16;
	enemies[2].size = 16;
	enemies[3].size = 16;
	enemies[4].size = 16;
	enemies[5].size = 16;
	enemies[6].size = 16;
	enemies[7].size = 16;

	reset();


	XGpio_Initialize(&gpio, 0);
	XGpio_SetDataDirection(&gpio, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input
	XGpio_SetDataDirection(&gpio, 2, 0x00000000); // set LED GPIO channel tristates to All Output

	XGpio_Initialize(&gpioPlayer, 1);
	XGpio_SetDataDirection(&gpioPlayer, 1, 0x00000000); // set LED GPIO channel tristates to All Output
	XGpio_SetDataDirection(&gpioPlayer, 2, 0x00000000); // set LED GPIO channel tristates to All Output

	XGpio_Initialize(&gpioCar1tm6, 2);
	XGpio_SetDataDirection(&gpioCar1tm6, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input
	XGpio_SetDataDirection(&gpioCar1tm6, 2, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	XGpio_Initialize(&gpioCar7tm12, 3);
	XGpio_SetDataDirection(&gpioCar7tm12, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input
	XGpio_SetDataDirection(&gpioCar7tm12, 2, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	XGpio_Initialize(&gpioCar13tm18, 4);
	XGpio_SetDataDirection(&gpioCar13tm18, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input
	XGpio_SetDataDirection(&gpioCar13tm18, 2, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	XGpio_Initialize(&gpioCandy, 5);
	XGpio_SetDataDirection(&gpioCandy, 1, 0x00000000); // set LED GPIO channel tristates to All Output
	XGpio_SetDataDirection(&gpioCandy, 2, 0x00000000); // set LED GPIO channel tristates to All Output

	XGpio_Initialize(&gpioTime, 6);
	XGpio_SetDataDirection(&gpioTime, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input
	XGpio_SetDataDirection(&gpioTime, 2, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	XGpio_Initialize(&gpioTimeScore, 7);
	XGpio_SetDataDirection(&gpioTimeScore, 1, 0x00000000); // set LED GPIO channel tristates to All Output
	XGpio_SetDataDirection(&gpioTimeScore, 2, 0x00000000); // set LED GPIO channel tristates to All Output

	timerGame = 0;
	gameRunning = false;
	srand(time%5000);
}

gameLogic::~gameLogic()
{

}

void gameLogic::gameLoop()
{
	getTime();


	readInputs();

	if (gameRunning) // check if game is ready
	{
		if(timer5min + gameTime < time) // timer of 5 minutes for the game
		{
			reset(); // 5 minutes are over
		}
		else // run gameloop
		{
			if(timerGame + framerate < time) // update at framerate defined in GameLogic.h
			{
				timerGame = time;

				move();
				checkCollision();
				//sendTimeLeft();
			}

			musicGame();
			drawScreen();
		}

	}
	else
	{
		if (xInput[0] == -1 || xInput[1] == -1)
		{
			timer5min = time;
			gameRunning = true;
		}
		musicMainScreen();
	}
	sendScore();
	sendGameState();

	XGpio_DiscreteWrite(&gpio, 2, XGpio_DiscreteRead(&gpio, 1));
}

void gameLogic::readInputs()
{
	u32 btn;
	btn = XGpio_DiscreteRead(&gpio, 1);
	//xil_printf("\rread inputs %04x", btn);

	/*-------------------------*/
	if ((btn&(0x1<<0)) != 0)
	{
		yInput[0] = -1;
	}
	else if ((btn&(0x1<<1)) != 0)
	{
		yInput[0] = 1;
	}
	else
	{
		yInput[0] = 0;
	}
	/*-------------------------*/
	if ((btn&(0x1<<2)) != 0)
	{
		xInput[0] = 1;
	}
	else if ((btn&(0x1<<3)) != 0)
	{
		xInput[0] = -1;
	}
	else
	{
		xInput[0] = 0;
	}

	/*-------------------------*/
	if ((btn&(0x1<<4)) != 0)
	{
		xInput[1] = 1;
	}
	else if ((btn&(0x1<<5)) != 0)
	{
		xInput[1] = -1;
	}
	else
	{
		xInput[1] = 0;
	}

	/*-------------------------*/
	if ((btn&(0x1<<6)) != 0)
	{
		yInput[1] = -1;
	}
	else if ((btn&(0x1<<7)) != 0)
	{
		yInput[1] = 1;
	}
	else
	{
		yInput[1] = 0;
	}

	// read controllers
}

void gameLogic::move()
{
	movePlayers();
	moveEnemies();
}

void gameLogic::movePlayers()
{
	for (int i = 0; i < 2; i++)
	{
		players[i].xPos = players[i].xPos + xInput[i]*2;
		players[i].yPos = players[i].yPos + yInput[i]*2;

		if (players[i].xPos < players[i].size) // CHECK FOR OUT OF SCREEN X POS
		{
			players[i].xPos = players[i].size;
		}
		if (players[i].xPos > WIDTH - players[i].size) // CHECK FOR OUT OF SCREEN X POS
		{
			players[i].xPos = WIDTH - players[i].size;
		}

		if (players[i].yPos < players[i].size) // CHECK FOR OUT OF SCREEN Y POS
		{
			players[i].yPos = players[i].size;
		}
		if (players[i].yPos > HEIGHT - players[i].size) // CHECK FOR OUT OF SCREEN Y POS
		{
			players[i].yPos = HEIGHT - players[i].size;
		}
	}
}

void gameLogic::moveEnemies()
{
	u32 readCar = 0;
	readCar = XGpio_DiscreteRead(&gpioCar1tm6, 1);
	//xil_printf("\r state: %08x", readCar);
	enemies[0].yPos = ((readCar >> 20) & 1023) - 31;
	enemies[1].yPos = ((readCar >> 10) & 1023) - 31;
	enemies[2].yPos = ((readCar >> 0) & 1023) - 31;

	readCar = 0;
	readCar = XGpio_DiscreteRead(&gpioCar1tm6, 2);
	//xil_printf("\r state: %08x", readCar);
	enemies[3].yPos = (readCar >> 20) & 1023;
	enemies[4].yPos = (readCar >> 10) & 1023;
	enemies[5].yPos = (readCar >> 0) & 1023;

	readCar = 0;
	readCar = XGpio_DiscreteRead(&gpioCar7tm12, 1);
	//xil_printf("\r state: %08x", readCar);
	enemies[6].yPos = (readCar >> 20) & 1023;
	enemies[7].yPos = (readCar >> 10) & 1023;
}

void gameLogic::respawn(int index)
{
	if (index == 0)
	{
		players[0].xPos = 20;
		players[0].yPos = HEIGHT / 2;
	}
	else
	{
		players[1].xPos = WIDTH - 20;
		players[1].yPos = HEIGHT / 2;
	}
}

void gameLogic::checkCollision()
{
	if (colPlayerCandy())
	{
		spawnCandy();
	}

	colPlayerEnemy();
}

bool gameLogic::colPlayerCandy()
{
	for (int i = 0; i < 2; i++)
	{
		int distance = sqrt((players[i].xPos-candy.xPos)*(players[i].xPos-candy.xPos) + (players[i].yPos-candy.yPos)*(players[i].yPos-candy.yPos));
		if (distance < players[i].size + candy.size)
		{
			score[i] += 50;
			return true;
		}
	}
	return false;
}

void gameLogic::colPlayerEnemy()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < CAR_COUNT; j++)
		{
			int distance = sqrt((players[i].xPos-enemies[j].xPos)*(players[i].xPos-enemies[j].xPos) + (players[i].yPos-enemies[j].yPos)*(players[i].yPos-enemies[j].yPos));
			if (distance < players[i].size + enemies[j].size)
			{
				score[i] += -20;
				if (score[i] < 0)
				{
					score[i] = 0;
				}
				respawn(i);
			}
		}
	}
}

void gameLogic::spawnCandy()
{
	//xil_printf("spawn candy");

	candy.xPos = 50 + (rand()%(WIDTH - 100) + 1);
	candy.yPos = 20 + (rand()%(HEIGHT - 40) + 1);
}

void gameLogic::drawScreen()
{
	//xil_printf("\rp1: %d, %d \tp2: %d, %d \tc: %d, %d", players[0].xPos, players[0].yPos, players[1].xPos, players[1].yPos, candy.xPos, candy.yPos, time);
	drawPlayers();
	drawEnemy();
	drawCandy();
}

void gameLogic::drawPlayers()
{

	u32 playerXY = 0;
	playerXY = players[0].xPos;
	playerXY = playerXY << 16;
	playerXY |= players[0].yPos;
	XGpio_DiscreteWrite(&gpioPlayer, 2, playerXY);

	playerXY = 0;
	playerXY = players[1].xPos;
	playerXY = playerXY << 16;
	playerXY |= players[1].yPos;
	XGpio_DiscreteWrite(&gpioPlayer, 1, playerXY);

}

void gameLogic::drawEnemy()
{
	//send to fpga
}

void gameLogic::drawCandy()
{
	u32 candyXY = 0;
	candyXY = candy.xPos;
	candyXY = candyXY << 16;
	candyXY |= candy.yPos;
	XGpio_DiscreteWrite(&gpioCandy, 1, candyXY);
}

void gameLogic::getTime()
{
	u32 time31_0=0;
	u32 time63_32=0;

	time31_0 = XGpio_DiscreteRead(&gpioTime, 1);
	time63_32 = XGpio_DiscreteRead(&gpioTime, 2);

	time = time63_32;
	time = time << 32;
	time = time | time31_0;
	//xil_printf("time1: %lu, time2: %lu, time: %llu", time63_32, time31_0, time);
}

void gameLogic::musicMainScreen()
{
	u64 curTime = time;
	curTime /= 2000000;

	u32 tone = 0;

	switch (curTime % 100){
	case 0 ... 10:
		tone = 200;
		break;
	case 11 ... 20:
		tone = 220;
		break;
	case 21 ... 40:
		tone = 400;
		break;
	case 41 ... 50:
		tone = 220;
		break;
	case 51 ... 60:
		tone = 240;
		break;
	case 61 ... 70:
		tone = 260;
		break;
	case 71 ... 80:
		tone = 280;
		break;
	case 81 ... 100:
		tone = 450;
		break;
	}
	sendTone(tone);
}

void gameLogic::musicGame()
{
	u64 curTime = time;
	curTime /= 2000000;

	u32 tone = 0;

	switch (curTime % 100){
	case 0 ... 10:
		tone = 200;
		break;
	case 11 ... 20:
		tone = 220;
		break;
	case 21 ... 40:
		tone = 400;
		break;
	case 41 ... 50:
		tone = 220;
		break;
	case 51 ... 60:
		tone = 240;
		break;
	case 61 ... 70:
		tone = 260;
		break;
	case 71 ... 80:
		tone = 280;
		break;
	case 81 ... 100:
		tone = 450;
		break;
	}
	sendTone(tone);
}

void gameLogic::sendTone(u32 &tone)
{
	XGpio_DiscreteWrite(&gpioCandy, 2, tone);
}

void gameLogic::sendGameState()
{
	u64 remaining = (timer5min + gameTime) - time;
	remaining /= 100000000;

	//xil_printf("\rtime Left: %d, %d score p1: %d, score p2 %d", remaining, score[0], score[1]);

	u32 send = 0;
	send |= (gameRunning << 31); // gameleft bit
	send |= ((remaining / 60) << 8); // minuten
	send |= (remaining % 60); // seconden
	XGpio_DiscreteWrite(&gpioTimeScore, 2, send);
}

void gameLogic::sendScore()
{
	u32 send = 0;
	send |= (score[0] << 16);
	send |= score[1];

	XGpio_DiscreteWrite(&gpioTimeScore, 1, send);
}

void gameLogic::reset()
{
	for (int i = 0; i < 2; i++)
	{
		respawn(i);
		score[i] = 0;
	}
	candy.xPos = WIDTH / 2;
	candy.yPos = HEIGHT / 2;

	gameRunning = false;
}








