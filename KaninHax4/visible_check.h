#pragma once
#include "sdk.h"
#include "math.h"

bool is_visible(vector3_t _source, vector3_t _destination)
{
	ray_t ray;
	ray.init(_source, _destination);

	trace_filter_t filter;
	filter.skip = local_player;

	trace_t trace;
	interfaces::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &trace);

	if (trace.all_solid || trace.start_solid)
		return false;

	if (trace.fraction >= 0.97 && trace.physics_bone <= 128 && trace.physics_bone > 0)
		return true;
	return false;
}

bool player_is_visible(vector3_t _source, entity_t* _player)
{
	if (!_player)
	{
		return false;
	}

	for (size_t i = 0; i <= 8; i++)
	{
		auto _destination = _player->get_bone_position(i);

		ray_t ray;
		ray.init(_source, _destination);

		trace_filter_t filter;
		filter.skip = local_player;

		trace_t trace;
		interfaces::engine_trace->trace_ray(ray, MASK_SHOT, &filter, &trace);

		if (trace.all_solid || trace.start_solid)
			return false;

		if (trace.fraction >= 0.97 && trace.physics_bone <= 128 && trace.physics_bone > 0)
			return true;
	}
	return false;
}