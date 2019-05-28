#pragma once
#include "virtual_table_functions.h"
#include "vector3.h"

struct studio_decal_handle_t 
{ 
	int unused;
};

struct draw_model_state_t
{
	void* studio_hdr; //studiohdr_t*
	void* studio_hw_data; //studiohwdata_t*
	void* client_renderable; //IClientRenderable*
	const matrix3x4_t *model_to_world;
	studio_decal_handle_t* decals;
	int	draw_flags;
	int lod;
};

struct model_render_info_t
{
	vector3_t origin;
	vector3_t angles;
	void* renderable; //IClientRenderable

	const void *model; //model_t	
	const matrix3x4_t *model_to_world;
	const matrix3x4_t *lightning_offset;
	const vector3_t *lightning_origin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitbox_set;
	unsigned short instance;

	model_render_info_t()
	{
		model_to_world = nullptr;
		lightning_offset = nullptr;
		lightning_origin = nullptr;
	}
};


class model_t
{

};

class studiohdr_t
{
	char* get_name()
	{
		return *reinterpret_cast<char**>(this + 12);
	}
};

class model_render_t
{

};

class model_info_t

{	model_t* get_model(int index)
	{
		return call_virtual_function<model_t*, 2>(this, index);
	}

	const char* get_model_name(const model_t *model)
	{
		return call_virtual_function<const char*, 4>(this, model);
	}

	studiohdr_t* get_studio_model(const model_t* model)
	{
		return call_virtual_function<studiohdr_t*, 31>(this, model);
	}
};