#pragma once

struct Rect
{
	Rect(int x = 0, int y = 0, int width = 0, int height = 0)
		: x{ x }
		, y{ y }
		, width{ width }
		, height{ height }
	{
	}

	int x;
	int y;
	int width;
	int height;
};