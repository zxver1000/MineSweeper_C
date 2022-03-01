#include "Replay.h"

void Replay::put_x_y(int x, int y)
{
	replay.emplace(x, y);
}

