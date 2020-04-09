#pragma once
#include <kaninsdk/virtual-table-functions.h>

class engine_client_t
{
public:
	void client_cmd(const char* _command)
	{
		call_virtual_function<void, 108>(this, _command);
	}
	bool is_in_game()
	{
		return call_virtual_function<bool, 26>(this);
	}
	int get_local_player_id()
	{
		return call_virtual_function<int, 12>(this);
	}
	vector3_t get_view_angles()
	{
		vector3_t ret;
		call_virtual_function<void, 18>(this, std::reference_wrapper<vector3_t>(ret));
		return ret;
	}
	void get_aspect_ratio(int& _w, int& _h)
	{
		call_virtual_function<void, 101>(this, std::reference_wrapper<int>(_w), std::reference_wrapper<int>(_h));
	}
};
