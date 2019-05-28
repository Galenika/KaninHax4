#pragma once
#include "pch.h"
#include "sdk.h"
#include "settings.h"
#include "math.h"

void print_closest_player()
{
	if (!current_settings.misc_client_recieve_closest_enemy_distance)
		return;

	static float time = interfaces::global_vars->cur_time;
	float cur_time = interfaces::global_vars->cur_time;
	if (cur_time > time + current_settings.misc_client_recieve_closest_enemy_distance_interval)
	{
		time = cur_time;
	}
	else
		return;

	double distance = DBL_MAX;
	for (size_t i = 0; i <= interfaces::global_vars->max_clients; i++)
	{
		entity_t* current_player = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!current_player)
			continue;
		if (current_player == local_player)
			continue;
		if (!current_player->get_valid_target())
			continue;
		if (current_player->get_team() == local_player->get_team())
			continue;

		vector3_t local_player_pos = local_player->get_head_position();
		vector3_t current_player_pos = current_player->get_bone_position(8);


		double distance_to_local_player = get_3d_distance(local_player_pos, current_player_pos);

		if (distance_to_local_player < distance)
		{
			distance = distance_to_local_player;
		}
	}
	if (distance != DBL_MAX)
	{
		hack_server::server_print(std::string(std::to_string(distance) + "\n"));
	}
}