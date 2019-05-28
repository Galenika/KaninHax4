#pragma once
#include "vector3.h"

struct view_setup_t
{
	char		_0x0000[16];
	__int32		x;
	__int32		x_old;
	__int32		y;
	__int32		y_old;
	__int32		width;
	__int32		width_old;
	__int32		height;
	__int32		height_old;
	char		_0x0030[128];
	float		fov;
	float		fov_viewmodel;
	vector3_t	origin;
	vector3_t	angles;
	float		z_near;
	float		z_far;
	float		z_near_viewmodel;
	float		z_far_viewmodel;
	float		aspect_ratio;
	float		near_blut_depth;
	float		near_focus_depth;
	float		far_focus_depth;
	float		far_blur_depth;
	float		near_blur_radius;
	float		far_blur_radius;
	float		do_f_quality;
	__int32		motion_blut_mode;
	char		_0x0104[68];
	__int32		edge_blur;
};