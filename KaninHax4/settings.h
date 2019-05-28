#pragma once
#include "pch.h"
#include "ImGui\imgui.h"

namespace menu_tabs
{
	bool	show_esp_menu;
	bool	show_aimbot_menu;
	bool	show_misc_menu;
	bool	show_anti_aim_menu;
	bool	show_triggerbot_menu;
}

struct settings_t
{
	bool	aimbot_enabled;
	bool	aimbot_smoothing_enabled;
	bool	aimbot_rcs_enabled;
	bool	aimbot_target_team = 0;
	bool	aimbot_aim_when_holding_shoot = 0;
	bool	aimbot_only_aim_when_can_shoot = 0;
	bool	aimbot_visibility_check = 0;
	bool	aimbot_draw_target = 0;
	int		aimbot_targeting_method = 0; //0: closest to crosshair | 1: closest
	float	aimbot_rcs_percent;
	float	aimbot_smooth_percent;
	float	aimbot_fov = 360;

	bool	esp_enabled = 0;
	bool	esp_boxes = 0;
	bool	esp_lines = 0;
	bool	esp_health = 0;
	bool	esp_prop_names = 0;
	bool	esp_visibility_check = 0;
	int		esp_line_start = 0; //0: top | 1: bot | 2: left | 3: right | 4: crosshair
	float	esp_enemy_box_color[3] = { 255.f, 0.f, 0.f };
	float	esp_enemy_line_color[3] = { 102.f, 0.f, 102.f };
	float	esp_team_box_color[3] = { 51.f, 153.f, 51.f };
	float	esp_team_line_color[3] = { 0.f, 51.f, 204.f };
	float	esp_enemy_box_visible_color[3] = { 255.f, 255.f, 153.f };
	float	esp_enemy_line_visible_color[3] = { 255.f, 153.f, 204.f };
	float	esp_team_box_visible_color[3] = { 153.f, 255.f, 153.f };
	float	esp_team_line_visible_color[3] = { 102.f, 255.f, 255.f };

	bool	misc_bunnyhop = 0;
	bool	misc_rcs = 0;
	bool	misc_viewmodel_fov_enabled = 0;
	bool	misc_fov_enabled = 0;
	bool	misc_silent_aim = 0;
	bool	misc_fake_lag_enabled = 0;
	bool	misc_radar_enabled = 0;
	bool	misc_client_recieve_closest_enemy_distance = 0;
	bool	misc_teleport = 0;
	bool	misc_movementfix = 0;
	int		misc_radar_x = 100;
	int		misc_radar_y = 100;
	int		misc_fake_lag_amount = 0;
	float	misc_rcs_amount = 0;
	float	misc_fov = 90.f;
	float	misc_viewmodel_fov = 70.f;
	float	misc_radar_radius = 50.f;
	float	misc_client_recieve_closest_enemy_distance_interval = 0.f;

	bool	anti_aim_enabled = 0;
	bool	anti_aim_disabled_when_shooting = 0;
	int		anti_aim_y = 0;
	int		anti_aim_x = 0;

	bool	triggerbot_enabled = 0;
	bool	triggerbot_target_team = 0;
	float	triggerbot_scan_lenght = 8192.f;
}current_settings;