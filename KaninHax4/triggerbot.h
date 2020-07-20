#pragma once
#include "sdk.h"
#include "settings.h"
#include "math.h"

void triggerbot(user_cmd_t* _cmd)
{
	trigger_hit_enemy = false;
	if (!current_settings.triggerbot_enabled)
		return;
	if (!local_player)
		return;

	vector3_t source = local_player->get_head_position();
	vector3_t forward;
	angle_vectors(_cmd->viewangles, forward);
	forward *= current_settings.triggerbot_scan_lenght;
	vector3_t destination = source + forward;

	ray_t ray;
	ray.init(source, destination);

	trace_filter_t filter;
	filter.skip = local_player;
	
	trace_t trace;
	interfaces::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &trace);

	entity_t* entity_hit = reinterpret_cast<entity_t*>(trace.entity);

	/*
	delete &ray;
	delete &filter;
	delete &trace;
	delete &destination;
	delete &source;
	delete &forward;
	*/

	if (!entity_hit)
		return;
	if (!entity_hit->get_valid_target())
		return;
	if (entity_hit->get_team() == local_player->get_team() && !current_settings.triggerbot_target_team)
		return;

	trigger_hit_enemy = true;
}