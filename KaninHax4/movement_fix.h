#pragma once
#include "pch.h"
#include "sdk.h"
#include "math.h"

inline class movement_fix_t
{
	float old_sidemove = 0.f, old_forwardmove = 0.f, old_upmove = 0.f;
	vector3_t old_angles, view_forward, view_right, view_up, aim_forward, aim_right, aim_up;
public:
	inline void on_createmove_start(user_cmd_t* _cmd);
	inline void on_createmove_end(user_cmd_t* _cmd, const vector3_t view_angles);
} movement_fix;

inline void movement_fix_t::on_createmove_start(user_cmd_t* _cmd)
{
	if (!current_settings.misc_movementfix)
		return;
	this->old_sidemove = _cmd->sidemove;
	this->old_forwardmove = _cmd->forwardmove;
	this->old_upmove = _cmd->upmove;
	this->old_angles = _cmd->viewangles;
	angle_vectors(_cmd->viewangles, view_forward, view_right, view_up);
}

inline void movement_fix_t::on_createmove_end(user_cmd_t* _cmd, const vector3_t view_angles)
{
	if (!current_settings.misc_movementfix)
		return;

	vector3_t angle = view_angles;
	angle.x = 0;
	angle_vectors(angle, aim_forward, aim_right, aim_up);

	auto forward_normalized = view_forward.get_normalized();
	auto right_normalized = view_right.get_normalized();
	auto up_normalized = view_up.get_normalized();

	_cmd->forwardmove = std::clamp(
		dot_product(forward_normalized * old_forwardmove, aim_forward) +
		dot_product(right_normalized * old_sidemove, aim_forward) +
		dot_product(up_normalized * old_upmove, aim_forward),
		-450.f, 450.f);

	_cmd->sidemove = std::clamp(
		dot_product(forward_normalized * old_forwardmove, aim_right) +
		dot_product(right_normalized * old_sidemove, aim_right) + 
		dot_product(up_normalized * old_upmove, aim_right),
		-450.f, 450.f);
};
