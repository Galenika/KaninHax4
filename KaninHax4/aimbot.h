#pragma once
#include "vector3.h"
#include "math.h"
#include "sdk.h"
#include "visible_check.h"
#include "drawing.h"

#define AIMBOT_TARGETING_CLOSEST_TO_CROSSHAIR 0
#define AIMBOT_TARGETING_CLOSEST 1


struct aimbot_target_t {
	entity_t* target = nullptr;
	float distance_from_crosshair;
	float distance_from_local_player;
	bool valid_target;
	vector3_t angle_to_target;
	aimbot_target_t(entity_t* _target, float _distance_from_crosshair, float _distance_from_local_player,
	                const vector3_t& _angle_to_target, bool _valid_target);
	aimbot_target_t();
	void init();
};

aimbot_target_t::aimbot_target_t(entity_t* _target, float _distance_from_crosshair, float _distance_from_local_player,
                                 const vector3_t& _angle_to_target, bool _valid_target)
	: target(_target), distance_from_crosshair(_distance_from_crosshair),
	  distance_from_local_player(_distance_from_local_player), valid_target(_valid_target),
	  angle_to_target(_angle_to_target) {}

aimbot_target_t::aimbot_target_t() {}

void aimbot_target_t::init() {
	this->target = nullptr;
	this->distance_from_crosshair = 0;
	this->distance_from_local_player = 0;
	this->angle_to_target = vector3_t(0, 0, 0);
	this->valid_target = false;
}

void find_closest_target_to_viewangles(vector3_t& _view_angles, double max_lenght_from_crosshair,
                                       aimbot_target_t& possible_target) {
	possible_target.init();
	double distance_from_crosshair = max_lenght_from_crosshair;
	for (size_t i = 0; i <= interfaces::global_vars->max_clients; i++) {
		entity_t* current_player = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!current_player)
			continue;
		if (current_player == local_player)
			continue;
		if (!current_player->get_valid_target())
			continue;
		if (current_player->get_team() == local_player->get_team() && !current_settings.aimbot_target_team)
			continue;

		vector3_t local_player_pos = local_player->get_head_position();
		vector3_t current_player_pos = current_player->get_bone_position(8);

		if (current_settings.aimbot_visibility_check && !is_visible(local_player_pos, current_player_pos))
			continue;

		float distance_to_local_player = get_3d_distance(local_player_pos, current_player_pos);

		vector3_t temp_angle = calc_angle_3d(local_player_pos, current_player_pos);
		float temp_distance_to_crosshair = get_distance_to_angles(_view_angles, temp_angle);

		if (temp_distance_to_crosshair <= distance_from_crosshair) {
			distance_from_crosshair = temp_distance_to_crosshair;
			possible_target = aimbot_target_t(current_player, temp_distance_to_crosshair, distance_to_local_player,
			                                  temp_angle, true);
		}
	}
}

void find_closest_target(vector3_t& _view_angles, aimbot_target_t& possible_target) {
	possible_target.init();
	double distance = DBL_MAX;
	for (size_t i = 0; i <= interfaces::global_vars->max_clients; i++) {
		entity_t* current_player = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!current_player)
			continue;
		if (current_player == local_player)
			continue;
		if (!current_player->get_valid_target())
			continue;
		if (current_player->get_team() == local_player->get_team() && !current_settings.aimbot_target_team)
			continue;

		vector3_t local_player_pos = local_player->get_head_position();
		vector3_t current_player_pos = current_player->get_bone_position(8);

		if (current_settings.aimbot_visibility_check && !is_visible(local_player_pos, current_player_pos))
			continue;

		const float distance_to_local_player = get_3d_distance(local_player_pos, current_player_pos);

		const vector3_t temp_angle = calc_angle_3d(local_player_pos, current_player_pos);
		const float distance_to_crosshair = get_distance_to_angles(_view_angles, temp_angle);

		if (distance_to_local_player <= distance) {
			distance = distance_to_local_player;
			possible_target = aimbot_target_t(current_player, distance_to_crosshair, distance_to_local_player,
			                                  temp_angle, true);
		}
	}
}

void aimbot_recoil_control(vector3_t& view_angles, vector3_t punch_angle) {
	if (!current_settings.aimbot_rcs_percent)
		return;
	view_angles = clamp_angles(view_angles - (((punch_angle * 2) / 100) * current_settings.aimbot_rcs_percent));
}

void aimbot(vector3_t& _view_angles, int _buttons) {
	if (!current_settings.aimbot_enabled)
		return;
	if (current_settings.aimbot_aim_when_holding_shoot && !(_buttons & IN_ATTACK))
		return;
	if (current_settings.aimbot_only_aim_when_can_shoot && !can_shoot(local_player))
		return;
	aimbot_target_t aimbot_target;
	aimbot_target.init();
	switch (current_settings.aimbot_targeting_method) {
		case AIMBOT_TARGETING_CLOSEST_TO_CROSSHAIR:
			find_closest_target_to_viewangles(_view_angles, current_settings.aimbot_fov, aimbot_target);
			break;
		case AIMBOT_TARGETING_CLOSEST:
			find_closest_target(_view_angles, aimbot_target);
			break;
		default:
			return;
	}
	if (!aimbot_target.valid_target)
		return;

	vector3_t angle_to_set = aimbot_target.angle_to_target;

	if (current_settings.aimbot_rcs_enabled)
		aimbot_recoil_control(angle_to_set, local_player->get_punch());

	if (current_settings.aimbot_smoothing_enabled)
		angle_to_set = vector3_lerp(_view_angles, angle_to_set, current_settings.aimbot_smooth_percent);

	if (current_settings.aimbot_draw_target) {
		vector3_t enemy_screen_pos;
		interfaces::debug_overlay->screen_position(aimbot_target.target->get_bone_position(8), enemy_screen_pos);
		surface::drawing::drawing_queue.push_back(
			new surface::drawing::draw_line_t(screen_size_x / 2, 0, enemy_screen_pos.x, enemy_screen_pos.y, 255, 0, 0,
			                                  255));
		surface::drawing::drawing_queue.push_back(new surface::drawing::draw_filled_box_t(
			enemy_screen_pos.x - 3, enemy_screen_pos.y - 3, enemy_screen_pos.x + 3, enemy_screen_pos.y + 3, 255, 0, 0,
			255));
	}

	_view_angles = clamp_angles(angle_to_set);
}

void draw_aimbot_fov_circle() {
	if (!current_settings.aimbot_enabled)
		return;

	float radius = 0; //TODO

	surface::drawing::draw_filled_circle(vector2_t(screen_size_x / 2, screen_size_y / 2), 200, 0, 255, 15, radius, 100);
	surface::drawing::draw_outlined_circle(vector2_t(screen_size_x / 2, screen_size_y / 2), 200, 0, 255, 255, radius,
	                                       100);
}
