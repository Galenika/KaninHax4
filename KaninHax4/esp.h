#pragma once
#include "pch.h"
#include "sdk.h"
#include "settings.h"
#include "drawing.h"
#include "visible_check.h"
#include "color.h"
#include "pch.h"

#define color2rgba(x) (x.r, x.g, x.b, x.a)

color_t esp_box_color;
color_t esp_line_color;

void box_esp(vector3_t bot_screen_pos, vector3_t top_screen_pos)
{
	if (!current_settings.esp_boxes)
		return;

	int height = bot_screen_pos.y - top_screen_pos.y;
	int width = height / 2;
	surface::drawing::draw_outlined_rect(bot_screen_pos.x - (width / 2), top_screen_pos.y, bot_screen_pos.x + (width / 2), bot_screen_pos.y,
		esp_box_color.r, esp_box_color.g, esp_box_color.b, esp_box_color.a);
}

void health_esp(vector3_t bot_screen_pos, int health)
{
	if (!current_settings.esp_health)
		return;
	int text_size_x = 0, text_size_y = 0;
	interfaces::vgui_surface->get_text_size(surface::fonts::arial, std::to_wstring(health).c_str(), text_size_x, text_size_y);
	surface::drawing::draw_string(bot_screen_pos.x - (text_size_x / 2), bot_screen_pos.y + text_size_y, surface::fonts::arial, 255, 0, 0, 255, std::to_wstring(health).c_str());
}

void line_esp(vector3_t bot_screen_pos, vector3_t top_screen_pos)
{
	if (!current_settings.esp_lines)
		return;

	int line_start_x = 0;
	int line_start_y = 0;

	switch (current_settings.esp_line_start)
	{
	case 0:
		line_start_x = screen_size_x / 2;
		line_start_y = 0;
		break;
	case 1:
		line_start_x = screen_size_x / 2;
		line_start_y = screen_size_y;
		break;
	case 2:
		line_start_x = 0;
		line_start_y = screen_size_y / 2;
		break;
	case 3:
		line_start_x = screen_size_x;
		line_start_y = screen_size_y / 2;
		break;
	case 4:
		line_start_x = screen_size_x / 2;
		line_start_y = screen_size_y / 2;
		break;
	default:
		line_start_x = screen_size_x / 2;
		line_start_y = 0;
		break;
	}
	surface::drawing::draw_line(line_start_x, line_start_y, bot_screen_pos.x, top_screen_pos.y, esp_line_color.r, esp_line_color.g, esp_line_color.b, esp_line_color.a);
}

void draw_player_esp(entity_t* player)
{
	auto current_player_head_position = player->get_bone_position(8);
	auto current_player_foot_position = player->get_bone_position(1);
	auto local_player_position = local_player->get_head_position();
	if (player->get_team() == local_player->get_team())
	{
		current_settings.esp_visibility_check && is_visible(local_player_position, current_player_head_position);
		esp_box_color = current_settings.esp_team_box_color;
		esp_line_color = current_settings.esp_team_line_color;
	}
	else
	{
		esp_box_color = current_settings.esp_enemy_box_color;
		esp_line_color = current_settings.esp_enemy_line_color;
	}

	vector3_t bot_screen_pos;
	vector3_t top_screen_pos;

	if (interfaces::debug_overlay->screen_position(current_player_foot_position - vector3_t(0, 10, 0), bot_screen_pos) == 1)
		return;
	if (interfaces::debug_overlay->screen_position(current_player_head_position + vector3_t(0, 10, 0), top_screen_pos) == 1)
		return;

	box_esp(bot_screen_pos, top_screen_pos);
	line_esp(bot_screen_pos, top_screen_pos);
	//health_esp(bot_screen_pos, current_player->get_health());
}

void draw_prop_esp()
{
	//if (!current_settings.esp_prop_names)
	//	return;
	for (size_t i = 0; i < interfaces::client_entity_list->get_highest_entity_index(); i++)
	{
		entity_t* prop = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!prop)
			return;
		std::string name = "";
		switch (prop->get_class_id())
		{
		case client_class_ids::ID_CC4:
			name = "C4";
			break;
		case client_class_ids::ID_CPlantedC4:
			name = "planted C4";
			break;
		case client_class_ids::ID_CPhysPropWeaponUpgrade:
			name = "upgrade";
			break;
		case client_class_ids::ID_CTablet:
			name = "tablet";
			break;
		case client_class_ids::ID_CHostage:
			name = "hostage";
			break;
		case client_class_ids::ID_CItem_Healthshot:
			name = "health";
			break;
		case client_class_ids::ID_CItemCash:
			name = "cash";
			break;
		case client_class_ids::ID_CBreachCharge:
			name = "breach charge";
			break;
		case client_class_ids::ID_CBreachChargeProjectile:
			name = "breach charge (PLACED!)";
			break;
		case client_class_ids::ID_CMelee:
			name = "melee weapon";
			break;
		case client_class_ids::ID_CKnife:
			name = "knife";
			break;
		case client_class_ids::ID_CPhysPropLootCrate:
			name = "loot crate";
			break;
		case client_class_ids::ID_CPhysPropAmmoBox:
			name = "ammo box";
			break;
		case client_class_ids::ID_CDrone:
			name = "drone";
			break;
		case client_class_ids::ID_CPhysPropRadarJammer:
			name = "radar jammer";
			break;
		default:
			continue;
			break;
		}
		vector3_t screen_position;
		vector3_t prop_origin = prop->get_origin();
		if (interfaces::debug_overlay->screen_position(prop->get_origin(), screen_position) == 1)
			continue;
		std::cout << name << " nigga" << '\n';
		double distance = get_3d_distance(local_player->get_origin(), prop_origin);
		directx::drawing::draw_string(screen_position.x, screen_position.y, D3DCOLOR_RGBA(0, 255, 255, 255), name.c_str(), directx::fonts::arial);
		directx::drawing::draw_box(screen_position.x, screen_position.y, 5 * (1 / distance), 5 * (1 / distance), D3DCOLOR_RGBA(255, 0, 0, 255));
	}
}

void esp()
{
	if (!current_settings.esp_enabled)
		return;
	for (size_t i = 0; i <= interfaces::global_vars->max_clients; i++)
	{
		entity_t* current_entity = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(i));
		if (!current_entity)
			continue;
		if (current_entity == local_player)
			continue;
		if (current_entity->get_valid_target())
			draw_player_esp(current_entity);
	}
}