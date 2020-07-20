#pragma once
#include "vector3.h"
#include "matrix3x4.h"
#include "offsets.h"
#include "const.h"
#include "hud_texture.h"


class entity_t
{
public:
	int get_team();
	bool is_prop();
	bool is_player();
	vector3_t get_origin();
	unsigned int get_class_id();
	unsigned int active_weapon();
	void* get_networkable();
	int get_health();
	int get_flags();
	int tick_base();
	int get_life_state();
	bool get_is_scoped();
	bool get_is_dormant();
	bool get_valid_target();
	vector3_t get_bone_position(int bone);
	vector3_t get_view_offset();
	vector3_t get_punch();
	vector3_t get_velocity();
	vector3_t get_head_position();
	matrix3x4_t* get_bone_matrix();
};

class file_weapon_info_t
{
public:
	virtual void parse(void);//(KeyValues *pKeyValuesData, const char *szWeaponName);

	bool parsed_script;
	bool loaded_hud_elements;

	char class_name[MAX_WEAPON_STRING];
	char print_name[MAX_WEAPON_STRING];

	char view_model[MAX_WEAPON_STRING];
	char world_model[MAX_WEAPON_STRING];
	char ammo1[MAX_WEAPON_AMMO_NAME];
	char world_dropped_model[MAX_WEAPON_STRING];
	char animation_prefix[MAX_WEAPON_PREFIX];
	int slot;
	int position;
	int max_clip1;
	int max_clip2;
	int default_clip1;
	int default_clip2;
	int weight;
	int rumble_effect;
	bool auto_switch_to;
	bool auto_switch_from;
	int flags;
	char ammo2[MAX_WEAPON_AMMO_NAME];
	char ai_add_on[MAX_WEAPON_STRING];

	char shoot_sounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING];

	int ammo_type;
	int ammo2_type;
	bool melee_weapon;
	bool built_right_handed;
	bool allow_flipping;
	int sprite_count;

	hud_texture_t* icon_active;
	hud_texture_t* icon_inactive;
	hud_texture_t* icon_ammo;
	hud_texture_t* icon_ammo2;
	hud_texture_t* icon_crosshair;
	hud_texture_t* icon_autoaim;
	hud_texture_t* icon_zoomed_crosshair;
	hud_texture_t* icon_zoomed_autoaim;
	hud_texture_t* icon_small;
};

class cs_weapon_info_t : public file_weapon_info_t
{
public:
	cs_weapon_type_t get_weapon_type()
	{
		return *reinterpret_cast<cs_weapon_type_t*>(this + offsets::weapon_type);
	}
};

class base_combat_weapon_t
{
public:
	float get_next_primary_attack()
	{
		return *reinterpret_cast<float*>(this + offsets::next_primary_attack);
	}
	bool is_reloading()
	{
		return *reinterpret_cast<float*>(this + offsets::in_reload);
	}
	int get_clip()
	{
		return *reinterpret_cast<float*>(this + offsets::clip1);
	}
	cs_weapon_info_t* cs_weapon_data()
	{
		return call_virtual_function<cs_weapon_info_t*, 448>(this);
	}
};

vector3_t entity_t::get_bone_position(int bone)
{
	auto bone_matrices = this->get_bone_matrix();
	if (!bone_matrices)
		return this->get_origin();

	auto bone_matrix = bone_matrices[bone];
		return vector3_t(
			bone_matrix.m[0][3],
			bone_matrix.m[1][3],
			bone_matrix.m[2][3]);
	return this->get_origin();
}

vector3_t entity_t::get_origin()
{
	return *reinterpret_cast<vector3_t*>(this + offsets::origin);
}

vector3_t entity_t::get_view_offset()
{
	return *reinterpret_cast<vector3_t*>(this + offsets::view_offset);
}

vector3_t entity_t::get_punch()
{
	return *reinterpret_cast<vector3_t*>(this + offsets::punch);
}

vector3_t entity_t::get_velocity()
{
	return *reinterpret_cast<vector3_t*>(this + offsets::velocity);
}

vector3_t entity_t::get_head_position()
{
	/*
	vector3_t ret;
	call_virtual_function<void, 277>(this, (vector3_t&)ret);
	return ret;
	*/

	return this->get_origin() + this->get_view_offset();
}

int entity_t::get_health()
{
	return *reinterpret_cast<int*>(this + offsets::health);
}

int entity_t::get_team()
{
	return *reinterpret_cast<int*>(this + offsets::team_num);
}

unsigned int entity_t::active_weapon()
{
	return *reinterpret_cast<unsigned int*>(this + offsets::active_weapon);
}

int entity_t::tick_base()
{
	return *reinterpret_cast<int*>(this + offsets::tick_base);
}

int entity_t::get_flags()
{
	return *reinterpret_cast<int*>(this + offsets::flags);
}

int entity_t::get_life_state() 
{
	return *reinterpret_cast<int*>(this + offsets::life_state);
}

matrix3x4_t* entity_t::get_bone_matrix()
{
	return *reinterpret_cast<matrix3x4_t**>(this + offsets::bone_matrix);
}

bool entity_t::get_is_scoped()
{
	return *reinterpret_cast<bool*>(this + offsets::is_scoped);
}

bool entity_t::get_is_dormant()
{
	return *reinterpret_cast<bool*>(this + offsets::is_dormant);
}

bool entity_t::is_player()
{
	return this->get_class_id() == client_class_ids::ID_CCSPlayer;
}

bool entity_t::is_prop()
{
	return (this->get_class_id() == ID_CPhysPropAmmoBox ||
		this->get_class_id() == ID_CPhysPropLootCrate ||
		this->get_class_id() == ID_CPhysPropRadarJammer ||
		this->get_class_id() == ID_CPhysPropWeaponUpgrade);
}

bool entity_t::get_valid_target()
{
	if (!this)
		return false;
	if (this->get_life_state() != LIFE_ALIVE)
		return false;
	//if (!this->is_player())
	//	return false;
	if (this->get_is_dormant())
		return false;
	return true;
}

void* entity_t::get_networkable()
{
	return reinterpret_cast<void*>(this + 8);
}

unsigned int entity_t::get_class_id()
{
	unsigned int ptr_0 = *reinterpret_cast<unsigned int*>(this->get_networkable());
	unsigned int ptr_1 = *reinterpret_cast<unsigned int*>(ptr_0 + 8);
	unsigned int ptr_2 = *reinterpret_cast<unsigned int*>(ptr_1 + 0x1);
	return *reinterpret_cast<unsigned int*>(ptr_2 + 0x14);
}

