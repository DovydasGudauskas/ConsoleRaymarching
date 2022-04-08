#pragma once
#include <Vector.h>

#define GAME_BASE_RESOLUTION Vector2(80,24)

class Game
{
public:
	Game();
	~Game();

	static void Play();
private:
	static Game* singleton;

	bool paused, pressedPause, gameQuit, hasInitialized, loopStarted;

	void Initialize();

	void TickTickables();

	void StartMainLoop();
	void MainLoop();
};