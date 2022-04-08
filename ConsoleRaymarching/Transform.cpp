#include <Transform.h>

Transform::Transform() : position(Vector3()), scale(Vector3(1,1,1))
{
	velocity = Vector3();
}

Transform::Transform(Vector3 pos) : position(pos), scale(Vector3(1,1, 1))
{
	velocity = Vector3();
}

Transform::Transform(Vector3 pos, Vector3 objectScale) : position(pos), scale(objectScale)
{
	velocity = Vector3();
}

Transform::~Transform()
{
}

Vector3 Transform::GetPosition()
{
	return position;
}

void Transform::OnPositionChange()
{
}

void Transform::Tick() // override Tickable
{
	Tickable::Tick();
	
	if(velocity == Vector3(0,0,0))
		return;

	Translate(velocity);
}

void Transform::Translate(Vector3 vec)
{
	position += vec;

	OnPositionChange();
}

void Transform::SetPosition(Vector3 Position)
{
	position = Position;

	OnPositionChange();
}

void Transform::SetVelocity(Vector3 vel)
{
	velocity = vel;
}

Vector3 Transform::GetVelocity()
{
	return velocity;
}

void Transform::SetScale(Vector3 newScale)
{
	scale = newScale;
}

Vector3 Transform::GetScale()
{
	return scale;
}
