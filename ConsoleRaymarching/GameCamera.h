#pragma once

#include <Transform.h>
#include <Vector.h>

class GameCamera : public Transform
{
public:
	static GameCamera* GetReference();
private:
	static GameCamera* singleton;

	void Tick() override;

	GameCamera();
	~GameCamera();
};