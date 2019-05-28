#pragma once
#include "const.h"
#include "settings.h"

void bunny_hop(int flags, int& buttons)
{
	if (!current_settings.misc_bunnyhop)
		return;

	if ((buttons & IN_JUMP) && !(flags & FL_ONGROUND))
		buttons &= ~IN_JUMP;
}