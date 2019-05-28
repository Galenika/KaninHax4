#pragma once
#include "pch.h"
#include "drawing.h"
#include "sdk.h"
#include "settings.h"
#include "math.h"

void radar()
{
	using namespace surface::drawing;
	if (!current_settings.misc_radar_enabled)
		return;
	draw_outlined_circle(vector2_t(current_settings.misc_radar_x, current_settings.misc_radar_y), 255, 255, 0, 255, current_settings.misc_radar_radius, 100);
	draw_filled_circle(vector2_t(current_settings.misc_radar_x, current_settings.misc_radar_y), 0, 255, 0, 255, 3, 10);

	float view_angle = degrees_to_radians(interfaces::engine_client->get_view_angles().y);

	draw_filled_circle(vector2_t(current_settings.misc_radar_x + (current_settings.misc_radar_radius * cosf(view_angle)),
		current_settings.misc_radar_y + (current_settings.misc_radar_radius * sinf(view_angle))), 0, 255, 0, 255, 5, 10);

	vector3_t local_origin = local_player->get_origin();

	for (size_t i = 0; i <= interfaces::global_vars->max_clients; i++)
	{
		entity_t* current_entity = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!current_entity)
			continue;
		if (!current_entity->get_valid_target())
			continue;
		if (current_entity == local_player)
			continue;

		vector3_t entity_origin = current_entity->get_origin();

		vector2_t delta = vector2_t(entity_origin.x - local_origin.x, entity_origin.y - local_origin.y);

		double distance_to_local_player = sqrt(delta.x * delta.x + delta.y * delta.y);

		float angle_to_player = atanf(delta.x / delta.y);
		//if (delta.x > 0.f)
		//	angle_to_player += pi;

		angle_to_player += view_angle;
		
		float point_pos_x = current_settings.misc_radar_x + ((distance_to_local_player / 20) * cosf(angle_to_player));
		float point_pos_y = current_settings.misc_radar_y + ((distance_to_local_player / 20) * sinf(angle_to_player));

		if (get_2d_distance(vector2_t(current_settings.misc_radar_x, current_settings.misc_radar_y), vector2_t(point_pos_x, point_pos_y)) > current_settings.misc_radar_radius)
			continue;

		int entity_team = current_entity->get_team();
		int local_team = local_player->get_team();

		draw_filled_circle(vector2_t(point_pos_x, point_pos_y),
			entity_team == local_team ? 0 : 255,
			0,
			entity_team == local_team ? 255 : 0,
			255, 3, 10);
	}
}