#pragma once

#include <Vector.h>
#include <stdlib.h>

using namespace std;

float sdBox(Vector2 p, Vector2 b)
{
    Vector2 d = p.Absolute() - b;
    return max(d.Magnitude(), 0.0)
        + min(max(d.x, d.y), 0.0);
}