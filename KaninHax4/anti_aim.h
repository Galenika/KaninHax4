#pragma once
#include "sdk.h"
#include "settings.h"
#include "math.h"

#define anti_aim_slow_spin_y 0
#define anti_aim_fast_spin_y 1
#define anti_aim_fake_backwards_y 2

#define anti_aim_up_x 0
#define anti_aim_down_x 1

namespace anti_aims
{
	namespace y
	{
		float temp_spinangle = 0;
		void slow_spin(float& _angle)
		{
			temp_spinangle += 5.f;
			_angle = clamp_angle_y(temp_spinangle);
		}
		void fast_spin(float& _angle)
		{
			temp_spinangle += 35.f;
			_angle = clamp_angle_y(temp_spinangle);
		}
		void fake_backwards(float& _angle)
		{
			if (send_packet())
				_angle += 180.f;
			_angle = clamp_angle_y(_angle);
		}
	}
	namespace x
	{
		void up(float& _angle)
		{
			_angle = -89.f;
			clamp_angle_x(_angle);
		}
		void down(float& _angle)
		{
			_angle = 89.f;
			clamp_angle_x(_angle);
		}
	}
}


void anti_aim(vector3_t& _view_angles, int _buttons)
{
	if (!current_settings.anti_aim_enabled)
		return;
	if (current_settings.anti_aim_disabled_when_shooting)
	{
		if ((_buttons & IN_ATTACK) && can_shoot(local_player))
			return;
	}
	if ((_buttons & IN_USE))
	{
		return;
	}
	switch (current_settings.anti_aim_y)
	{
	case anti_aim_slow_spin_y:
		anti_aims::y::slow_spin(_view_angles.y);
		break;
	case anti_aim_fast_spin_y:
		anti_aims::y::fast_spin(_view_angles.y);
		break;
	case anti_aim_fake_backwards_y:
		anti_aims::y::fake_backwards(_view_angles.y);
		break;
	default:
		break;
	}
	switch (current_settings.anti_aim_x)
	{
	case anti_aim_up_x:
		anti_aims::x::up(_view_angles.x);
		break;
	case anti_aim_down_x:
		anti_aims::x::down(_view_angles.x);
		break;
	default:
		break;
	}
}