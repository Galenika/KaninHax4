#pragma once
#include "sdk.h"
#include "math.h"
#include "settings.h"

void recoil_control(vector3_t& view_angles, vector3_t punch_angle)
{
	if (!current_settings.misc_rcs)
		return;
	vector3_t temp = view_angles - (((punch_angle * 2) / 100) * current_settings.misc_rcs_amount);
	view_angles = clamp_angles(temp);
}