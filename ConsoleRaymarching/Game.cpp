
#include <Game.h>

#include <Windows.h> // GetAsyncKeyState
#include <algorithm> // std::sort
#include <time.h> // clock_t, CLOCKS_PER_SEC

#include <Rendering.h>
#include <Tick.h>

Game* Game::singleton = nullptr;

Game::Game()
{
	paused = false;
	pressedPause = false;
	gameQuit = false;
	hasInitialized = false;
	loopStarted = false;

	if (singleton == nullptr)
	{
		singleton = this;
		Initialize();
	}
}

Game::~Game()
{
}

void Game::Play()
{
	if (singleton == nullptr)
		new Game();
}

void Game::Initialize()
{
	if (hasInitialized)
		return;
	hasInitialized = true;

	Rendering* rendering = Rendering::GetReference();

	StartMainLoop();
}

void Game::StartMainLoop()
{
	if (loopStarted)
		return;
	loopStarted = true;
	MainLoop();
}

void Game::TickTickables()
{
	vector<Tickable*>* ticks = Tickable::GetAllTicks();

	for (size_t i = 0; i < ticks->size(); i++)
		ticks->at(i)->Tick();
}

void Sleep(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end) {}
}

void Game::MainLoop()
{
	while (!gameQuit && !GetAsyncKeyState(VK_ESCAPE))
	{
		bool run = true;
		if (GetAsyncKeyState(VK_ESCAPE)) 
			run = false;

		if (!run)
			break;

		//Sleep(17);

		if (GetAsyncKeyState('P'))
		{
			if(pressedPause != true)
				paused = !paused;

			pressedPause = true;
		}
		else
			pressedPause = false;

		if (!paused)
		{
			TickTickables();
			Rendering::GetReference()->RenderWindow();
		}
	}
}
