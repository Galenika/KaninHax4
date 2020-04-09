#pragma once
#include "kaninsdk/virtual-table-functions.h"
#include "material.h"

class material_system_t
{
public:
	material_t* find_material(char const* material_name, const char *texture_group_name, bool complain = true, const char *complain_prefix = nullptr)
	{
		return call_virtual_function<material_t*, 84>(this, material_name, texture_group_name, complain, complain_prefix);
	}
};