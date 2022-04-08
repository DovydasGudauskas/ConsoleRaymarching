#pragma once

#include <Vector.h>
#include <Tick.h>

class Transform : public Tickable
{
public:
	Transform();
	Transform(Vector3 pos);
	Transform(Vector3 pos, Vector3 objectScale);
	~Transform();

	Vector3 GetPosition();

	virtual void OnPositionChange();
	void Tick() override;

	void Translate(Vector3 vec);
	void SetPosition(Vector3 Position);

	void SetVelocity(Vector3 vel);
	Vector3 GetVelocity();

	void SetScale(Vector3 newScale);
	Vector3 GetScale();
protected:
	Vector3 position, scale, velocity;
};