#pragma once
#include "sdk.h"

void remove_sight_blur()
{
	material_t *xblur_mat = interfaces::material_system->find_material("dev/blurfilterx_nohdr", TEXTURE_GROUP_OTHER, true);
	material_t *yblur_mat = interfaces::material_system->find_material("dev/blurfiltery_nohdr", TEXTURE_GROUP_OTHER, true);
	material_t *scope = interfaces::material_system->find_material("dev/scope_bluroverlay", TEXTURE_GROUP_OTHER, true);

	xblur_mat->set_material_var_flag(MATERIAL_VAR_NO_DRAW, true);
	yblur_mat->set_material_var_flag(MATERIAL_VAR_NO_DRAW, true);
	scope->set_material_var_flag(MATERIAL_VAR_NO_DRAW, true);
}