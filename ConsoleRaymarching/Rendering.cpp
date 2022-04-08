
#include <Rendering.h>

#include <GameCamera.h>

#include <windows.h>

Rendering* Rendering::singleton = nullptr;

void Rendering::ClearBuffer()
{
	for (size_t i = 0; i < buffer.size(); i++)
		for (size_t j = 0; j < buffer[i].size(); j++)
			buffer[i][j] = ' ';
}

void Rendering::RenderAllObjects()
{
	ApplyShader();
	DrawBuffer();
}

void Rendering::ApplyShader()
{
	GameCamera* gameCamera = GameCamera::GetReference();
	Vector3 camPos = gameCamera->GetPosition();

	double distance;
	Vector2 screenCoord;
	Vector2 iResolution = Vector2(buffer.size(), buffer[0].size());

	for (size_t i = 0; i < buffer.size(); i++)
		for (size_t j = 0; j < buffer[i].size(); j++)
		{
			screenCoord = Vector2(i, j);
			distance = Shader(camPos, screenCoord, iResolution);

			buffer[i][j] = LuminocityToChar(distance);
		}
}

//int drawDist = 6;
double Rendering::Shader(Vector3 cameraPos, Vector2 screenCoord, Vector2 iResolution)
{
	Vector2 uv = (screenCoord - iResolution * 0.5) / iResolution.y;

	double col = 0;

	Vector3 rd = Vector3(uv.x, uv.y, 1.0).Normalize();

	double dist = RayMarch(cameraPos, rd);

	Vector3 point = cameraPos + rd * dist;

	float diffuse = GetLight(point);

	return diffuse;
	//return dist / drawDist;
}

void Rendering::DrawBuffer()
{
	string out = "";

	for (int j = buffer[0].size() - 1; j >= 0; j--)
		for (size_t i = 0; i < buffer.size(); i++)
			out += buffer[i][j];

	SetPointerPos(0, 0);
	printf("%s", out.c_str());
}

void Rendering::InitializeBuffer()
{
	int rows, cols;
	GetConsoleSize(&rows, &cols);

	buffer.resize(cols);
	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
			buffer[i].resize(rows);
}

Vector3 lightPos = Vector3(0, 5, 6);
void Rendering::RenderWindow()
{
	if (GetAsyncKeyState('R'))
		InitializeBuffer();

	/*if (GetAsyncKeyState(VK_UP))
		drawDist++;
	if (GetAsyncKeyState(VK_DOWN))
	{
		drawDist--;

		if (drawDist <= 0)
			drawDist = 1;
	}*/

	if (GetAsyncKeyState(VK_UP))
		lightPos.z++;
	if (GetAsyncKeyState(VK_DOWN))
		lightPos.z--;
	if (GetAsyncKeyState(VK_RIGHT))
		lightPos.x++;
	if (GetAsyncKeyState(VK_LEFT))
		lightPos.x--;

	ClearBuffer();
	RenderAllObjects();
}

Rendering::Rendering()
{
	if (singleton == nullptr)
		singleton = this;

	InitializeBuffer();

	ShowConsoleCursor(false);
}

Rendering::~Rendering()
{
}

Rendering* Rendering::GetReference()
{
	if (singleton == nullptr)
		return new Rendering();

	return singleton;
}

// *********************
// CONSOLE

char luminousChars[13] = { ' ','.',',','-','~',':',';', '=', '!','*','#','$','@' };
char Rendering::LuminocityToChar(double value)
{
	if (value > 1) 
		value = 1;
	else if (value < 0) 
		value = 0;

	int index = (int)(12 * value);

	//index = 12 - index;

	return luminousChars[index];
}

void Rendering::SetPointerPos(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord{};

	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void Rendering::GetConsoleSize(int* row, int* col)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*col = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Rendering::ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

// *********************
// RAYMARCH

#define MAX_RAY_STEPS 100
#define MAX_DISTANCE 100
#define MIN_DISTANCE 0.01

double Rendering::DistanceEstimator(Vector3 point)
{
	double dPlane = point.y; // dPlane = yCamera - yPlane
	double dSphere = (Vector3(0., 1., 6.) - point).Magnitude() - 1.; // dSphere = (SpherePos - CameraPos).Magnitude() - SphereRadius

	return min(dPlane, dSphere);
}

double Rendering::RayMarch(Vector3 from, Vector3 direction)
{
	double totalDistance = 0.0;

	for (int steps = 0; steps < MAX_RAY_STEPS; steps++)
	{
		Vector3 point = from + direction * totalDistance;

		float distance = DistanceEstimator(point);
		totalDistance += distance;

		if (distance < MIN_DISTANCE || distance > MAX_DISTANCE)
			break;
	}

	return totalDistance;
}

Vector3 Rendering::GetNormal(Vector3 point)
{
	double distance = DistanceEstimator(point);
	Vector2 e = Vector2(0.01, 0);

	Vector3 n = Vector3(
		distance - DistanceEstimator(point - Vector3(e.x, e.y, e.y)),
		distance - DistanceEstimator(point - Vector3(e.y, e.x, e.y)),
		distance - DistanceEstimator(point - Vector3(e.x, e.y, e.x)));

	return n.Normalize();
}

float Rendering::GetLight(Vector3 point)
{
	Vector3 lightRay = (lightPos - point).Normalize();
	Vector3 normal = GetNormal(point);

	double diffuse = lightRay.Scalar(normal);

	if (diffuse > 1)
		diffuse = 1;
	else if (diffuse < 0)
		diffuse = 0;

	double shadow = RayMarch(point + normal * 0.02, lightRay);

	if (shadow < (lightPos - point).Magnitude())
		diffuse *= 0.1;

	return diffuse;
}