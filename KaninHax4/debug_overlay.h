#pragma once
#include "vector3.h"
#include "kaninsdk/virtual-table-functions.h"

class debug_overlay_t
{
	typedef int(__thiscall* screen_position_fn)(void*, const vector3_t&, vector3_t&);
public:
	int screen_position(const vector3_t& in, vector3_t& out)
	{
		return get_virtual_function<screen_position_fn>(this, 13)(this, in, out);
	}
};