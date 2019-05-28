#pragma once
struct color_t
{
	int r, g, b, a;
	void operator=(float rhs[3])
	{
		this->r = rhs[0] * 255;
		this->g = rhs[1] * 255;
		this->b = rhs[2] * 255;
		this->a = 255;
	}
};