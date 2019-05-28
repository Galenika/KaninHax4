#pragma once

class vector3_t
{
public:
	float x = 0.0f,y = 0.0f, z = 0.0f;
	vector3_t(float _x, float _y, float _z);
	vector3_t();
	vector3_t operator-(const vector3_t& _rhs);
	vector3_t operator+(const vector3_t& _rhs);
	vector3_t operator/(const vector3_t& _rhs);
	vector3_t operator/(const float& _rhs);
	vector3_t operator*(const vector3_t& _rhs);
	vector3_t operator*(const float& _rhs);
	void operator*=(const float& _rhs);
	double lenght() const;
	void operator-=(const vector3_t& _rhs);
	void init();
	void init(float x, float y, float z);
	vector3_t get_normalized() const;
};

vector3_t::vector3_t(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

vector3_t::vector3_t()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

vector3_t vector3_t::operator-(const vector3_t& _rhs)
{
	return vector3_t(this->x - _rhs.x, this->y - _rhs.y, this->z - _rhs.z);
}

vector3_t vector3_t::operator+(const vector3_t& _rhs)
{
	return vector3_t(this->x + _rhs.x, this->y + _rhs.y, this->z + _rhs.z);
}

vector3_t vector3_t::operator/(const vector3_t& _rhs)
{
	return vector3_t(this->x / _rhs.x, this->y / _rhs.y, this->z / _rhs.z);
}

vector3_t vector3_t::operator*(const vector3_t& _rhs)
{
	return vector3_t(this->x * _rhs.x, this->y * _rhs.y, this->z * _rhs.z);
}

vector3_t vector3_t::operator*(const float& _rhs)
{
	return vector3_t(this->x * _rhs, this->y * _rhs, this->z * _rhs);
}

void vector3_t::operator*=(const float & _rhs)
{
	this->x *= _rhs;
	this->y *= _rhs;
	this->z *= _rhs;
}

double vector3_t::lenght() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

vector3_t vector3_t::operator/(const float& _rhs)
{
	return vector3_t(this->x / _rhs, this->y / _rhs, this->z / _rhs);
}

void vector3_t::operator-=(const vector3_t& _rhs)
{
	this->x -= _rhs.x;
	this->y -= _rhs.y;
	this->z -= _rhs.z;
}

void vector3_t::init()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

void vector3_t::init(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

inline vector3_t vector3_t::get_normalized() const
{
	float lenght = this->lenght();
	if (lenght == 0)
		return vector3_t(0, 0, 1);

	lenght = 1 / lenght;
	return vector3_t(this->x * lenght, this->y * lenght, this->z * lenght);
}
