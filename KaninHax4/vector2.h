#pragma once

class vector2_t
{
public:
	float x = 0.0f, y = 0.0f;
	vector2_t(float _x, float _y);
	vector2_t();
	vector2_t operator-(const vector2_t& _rhs);
	vector2_t operator+(const vector2_t& _rhs);
	vector2_t operator/(const vector2_t& _rhs);
	vector2_t operator*(const vector2_t& _rhs);
	void init();
};

vector2_t::vector2_t(float _x, float _y)
{
	this->x = _x;
	this->y = _y;
}

vector2_t::vector2_t()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

vector2_t vector2_t::operator-(const vector2_t& _rhs)
{
	return vector2_t(this->x - _rhs.x, this->y - _rhs.y);
}

vector2_t vector2_t::operator+(const vector2_t& _rhs)
{
	return vector2_t(this->x + _rhs.x, this->y + _rhs.y);
}

vector2_t vector2_t::operator/(const vector2_t& _rhs)
{
	return vector2_t(this->x / _rhs.x, this->y / _rhs.y);
}

vector2_t vector2_t::operator*(const vector2_t& _rhs)
{
	return vector2_t(this->x * _rhs.x, this->y * _rhs.y);
}

void vector2_t::init()
{
	this->x = 0.0f;
	this->y = 0.0f;
}