#pragma once

#include <Vector.h>
#include <vector>

using namespace std;

class Rendering
{
public:
	Rendering();
	~Rendering();

	static Rendering* GetReference();
	void RenderWindow();

private:
	static Rendering* singleton;

	vector<vector<char>> buffer;

	void ClearBuffer();
	void DrawBuffer();

	void ApplyShader();
	double Shader(Vector3 cameraPos, Vector2 screenCoord, Vector2 iResolution);

	void RenderAllObjects();

	void InitializeBuffer();

	void SetPointerPos(int x, int y);
	void ShowConsoleCursor(bool showFlag);
	void GetConsoleSize(int* row, int* col);
	char LuminocityToChar(double value);

	double DistanceEstimator(Vector3 point);
	double RayMarch(Vector3 from, Vector3 direction);
	Vector3 GetNormal(Vector3 point);
	float GetLight(Vector3 point);
};