#pragma once

class input_system_t
{
	typedef bool(__thiscall* is_button_down_fn)(void*, int);
public:
	bool is_button_down(int _button_code)
	{
		return get_virtual_function<is_button_down_fn>(this, 15)(this, _button_code);
	}
};

