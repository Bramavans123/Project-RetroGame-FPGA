#ifndef __GAMELOGIC_H
#define __GAMELOGIC_H


//AXI GPIO driver
#include "xgpio.h"



//information about AXI peripherals
#include "xparameters.h"


#include "entities.h"

#include <cmath>



#define WIDTH 640
#define HEIGHT 480
#define CAR_COUNT 8

#define clockSpeed 100000000 // how many clocks it takes for 1 second

#define framerate (clockSpeed / 60) // 1/60 of a second
const u64 gameTime = 30000000000; // 5 minutes 5 times 60 seconds


class gameLogic {

public:
	gameLogic();
	~gameLogic();

public:
	void gameLoop();

private:
	/*-------------------------*/
	void readInputs();
	/*-------------------------*/
	void move();

	void movePlayers();
	void moveEnemies();

	void respawn(int index);
	/*-------------------------*/
	void checkCollision();

	bool colPlayerCandy();
	void colPlayerEnemy();
	/*-------------------------*/
	void spawnCandy();
	/*-------------------------*/
	void drawScreen();

	void drawPlayers();
	void drawEnemy();
	void drawCandy();
	/*-------------------------*/
	void getTime();
	void checkGameTime();

	void musicMainScreen();
	void musicGame();

	void sendTone(u32 &tone);
	void sendGameState();
	void sendScore();

	void reset();

private:
	XGpio gpio;
	XGpio gpioPlayer;
	XGpio gpioCar1tm6;
	XGpio gpioCar7tm12;
	XGpio gpioCar13tm18;
	XGpio gpioCandy;
	XGpio gpioTime;
	XGpio gpioTimeScore;

	u64 time;
	u64 timerGame;
	u64 timer5min;

	bool gameRunning;

	int xInput[2];
	int yInput[2];

	entities players[2];
	int score[2];
	entities enemies[CAR_COUNT];
	entities candy;

	enum entityId {player, enemy, sweet};
};


#endif // __GAMELOGIC_H
