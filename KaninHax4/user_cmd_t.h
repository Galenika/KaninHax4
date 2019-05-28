#pragma once
#include "pch.h"
#include "vector3.h"

class user_cmd_t
{
public:
	user_cmd_t() { reset(); }
	virtual ~user_cmd_t() { };
	void reset()
	{
		command_number = 0;
		tick_count = 0;
		viewangles.init();
		aimdirection.init();
		forwardmove = 0.0f;
		sidemove = 0.0f;
		upmove = 0.0f;
		buttons = 0;
		impulse = 0;
		weaponselect = 0;
		weaponsubtype = 0;
		random_seed = 0;
		mousedx = 0;
		mousedy = 0;
		hasbeenpredicted = false;
	}

	user_cmd_t& operator =(const user_cmd_t& _src)
	{
		if (this == &_src) return *this;
		command_number = _src.command_number;
		tick_count = _src.tick_count;
		viewangles = _src.viewangles;
		aimdirection = _src.aimdirection;
		forwardmove = _src.forwardmove;
		sidemove = _src.sidemove;
		upmove = _src.upmove;
		buttons = _src.buttons;
		impulse = _src.impulse;
		weaponselect = _src.weaponselect;
		weaponsubtype = _src.weaponsubtype;
		random_seed = _src.random_seed;
		mousedx = _src.mousedx;
		mousedy = _src.mousedy;
		hasbeenpredicted = _src.hasbeenpredicted;
		return *this;
	}

	user_cmd_t(const user_cmd_t& _src) { *this = _src; }

	int		command_number;		// 0x04 For matching server and client commands for debugging
	int		tick_count;			// 0x08 the tick the client created this command
	vector3_t	viewangles;			// 0x0C Player instantaneous view angles.
	vector3_t	aimdirection;		// 0x18
	float	forwardmove;		// 0x24
	float	sidemove;			// 0x28
	float	upmove;				// 0x2C
	int		buttons;			// 0x30 Attack button states
	byte    impulse;			// 0x34
	int		weaponselect;		// 0x38 Current weapon id
	int		weaponsubtype;		// 0x3C
	int		random_seed;		// 0x40 For shared random functions
	short	mousedx;			// 0x44 mouse accum in x from create move
	short	mousedy;			// 0x46 mouse accum in y from create move
	bool	hasbeenpredicted;	// 0x48 Client only, tracks whether we've predicted this command at least once
	char	pad_0x4C[0x18];		// 0x4C Current sizeof( usercmd ) =  100  = 0x64
};