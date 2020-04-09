#pragma once
#include <kaninsdk/virtual-table-functions.h>

class panel_t
{
	typedef const char*(__thiscall* get_name_fn)(void*, unsigned int);
public:
	const char* get_name(int _panel)
	{
		return get_virtual_function<get_name_fn>(this, 36)(this, _panel);
	}
};