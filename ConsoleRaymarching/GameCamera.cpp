
#include <GameCamera.h>
#include <Game.h>
#include <Windows.h>

GameCamera* GameCamera::singleton = nullptr;

GameCamera* GameCamera::GetReference()
{
	if (singleton == nullptr)
		return new GameCamera();

	return singleton;
}

float speed = 0.1f;

void GameCamera::Tick()
{
	if (GetAsyncKeyState('A'))
		Translate(Vector3::left * speed);
	if (GetAsyncKeyState('D'))
		Translate(Vector3::right * speed);

	if (GetAsyncKeyState('W'))
		Translate(Vector3::forwards * speed);
	if (GetAsyncKeyState('S'))
		Translate(Vector3::backwards * speed);
}

GameCamera::GameCamera()
{
	singleton = this;

	position = Vector3(0, 1, 0);
}

GameCamera::~GameCamera()
{
}
