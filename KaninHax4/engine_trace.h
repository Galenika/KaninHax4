#pragma once
#include "vector3.h"
#include <kaninsdk/virtual-table-functions.h>

struct ray_t
{
	__declspec(align(16)) vector3_t		start;
	__declspec(align(16)) vector3_t		delta;
	__declspec(align(16)) vector3_t		start_offset;
	__declspec(align(16)) vector3_t		extents;

	const matrix3x4_t*					world_axis_transform;

	bool	is_ray;
	bool	is_swept;

	void init(vector3_t _start, vector3_t _end)
	{
		this->delta = _end - _start;
		this->is_swept = (delta.lenght() != 0);
		this->extents.x = this->extents.y = this->extents.z = 0.0f;
		this->is_ray = true;
		this->start_offset.x = this->start_offset.y = this->start_offset.z = 0.0f;
		this->start = _start;
		this->world_axis_transform = {};
	}
};

struct cplane_t
{
	vector3_t	normal;
	float		dist;
	BYTE		type;
	BYTE		sign_bits;
	BYTE		pad[2];
};

class base_trace_t
{
public:
	vector3_t       start_pos;
	vector3_t		end_pos;
	cplane_t        plane;
	float           fraction;
	int             contents;
	unsigned short  disp_flags;
	bool            all_solid;
	bool            start_solid;
};

struct csurface_t
{
	const char*				name;
	short					surface_props;
	unsigned short			flags;
};

class game_trace_t : public base_trace_t
{
public:
	bool			did_hit_world() const;
	bool			did_hit_non_world_entity() const;
	int				get_entity_index() const;
	bool			did_hit() const;
public:
	float			fraction_left_solid;
	csurface_t		surface;
	int				hit_group;
	short			physics_bone;
	unsigned short  world_surface_index;
	void*			entity;
	int				hitbox;
	char			pad_0[0x24];
};

inline bool game_trace_t::did_hit_world() const
{
	return 0;//this->entity->get_index() == 0;
}

inline bool game_trace_t::did_hit() const
{
	return this->fraction < 1.0f || this->all_solid || this->start_solid;
}

typedef game_trace_t trace_t;

enum trace_type_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class base_trace_filter_t
{
public:
	virtual bool            should_hit_entity(void* entity, int contents_mask) = 0;
	virtual trace_type_t    get_trace_type() const = 0;
};

class trace_filter_t : public base_trace_filter_t
{
public:
	bool should_hit_entity(void* entity_handle, int contents_mask)
	{
		return !(entity_handle == this->skip);
	}

	trace_type_t get_trace_type() const
	{
		return TRACE_EVERYTHING;
	}

	void* skip;
};

class engine_trace_t
{
public:
	int	get_points_contents(const vector3_t &abs_position, int contents_mask = MASK_ALL, void** entity = NULL)
	{
		typedef int(__thiscall* get_points_contents_fn)(void*, const vector3_t&, int, void**);
		return get_virtual_function<get_points_contents_fn>(this, 0)(this, abs_position, contents_mask, entity);
	}

	void clip_ray_to_entity(const ray_t &ray, unsigned int mask, entity_t* entity, trace_t* trace)
	{
		typedef void(__thiscall* clip_ray_to_entity_fn)(void*, const ray_t&, unsigned int, entity_t*, trace_t*);
		return get_virtual_function<clip_ray_to_entity_fn>(this, 3)(this, ray, mask, entity, trace);
	}

	void trace_ray(const ray_t &ray, unsigned int mask, trace_filter_t* trace_filter, trace_t* trace)
	{
		typedef void(__thiscall* trace_ray_fn)(void*, const ray_t&, unsigned int, trace_filter_t*, trace_t*);
		get_virtual_function<trace_ray_fn>(this, 5)(this, ray, mask, trace_filter, trace);
	}
};