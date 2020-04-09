#pragma once
#include "pch.h"
#include "sdk.h"
#include "drawing.h"
#include "aimbot.h"
#include "bunny_hop.h"
#include "recoil_control.h"
#include "view_setup.h"
#include "esp.h"
#include "anti_aim.h"
#include "fake_lag.h"
#include "radar.h"
#include "triggerbot.h"
#include "remove_sight_blur.h"
#include "server_functions.h"
#include "movement_fix.h"
#include <imgui/examples/imgui_impl_dx9.h>
#include <imgui/examples/imgui_impl_win32.h>
#include <string>

namespace hooks
{
	namespace client
	{
		namespace write_usercmd_delta_to_buffer
		{
			typedef bool (__thiscall* write_usercmd_delta_to_buffer_fn)(void*, int, void*, int, int, bool);

			bool __fastcall write_usercmd_delta_to_buffer_hook(void* ecx, void* edx, int slo, void* buf, int from,
			                                                   int to, bool is_new_cmd)
			{
				static auto ret = client_hook.get_original<write_usercmd_delta_to_buffer_fn>(23);
				if (current_settings.misc_teleport)
					return false;
				return ret(ecx, slo, buf, from, to, is_new_cmd);
			}
		}
	}

	namespace client_mode
	{
		namespace create_move
		{
			bool once;
			vector3_t view_angles_to_set;

			bool __fastcall create_move_hook(void* _ecx, void* _edx, float _input_samle_time, user_cmd_t* _cmd)
			{
				if (!once)
				{
					/*
					void* _ebp = nullptr;
					__asm mov _ebp, ebp
					if (_ebp)
						send_packet_addr = *reinterpret_cast<bool**>(_ebp) - 0x1C;
					*/
					once = true;
				}

				//send_packet(true); crashes

				view_angles_to_set = _cmd->viewangles;
				local_player = reinterpret_cast<entity_t*>(interfaces::client_entity_list->get_client_entity(
					interfaces::engine_client->get_local_player_id()));

				movement_fix.on_createmove_start(_cmd);

				if (local_player)
				{
					//fake_lag();
					recoil_control(view_angles_to_set, local_player->get_punch());
					bunny_hop(local_player->get_flags(), _cmd->buttons);
					aimbot(view_angles_to_set, _cmd->buttons);
					anti_aim(view_angles_to_set, _cmd->buttons);
					triggerbot(_cmd);
					print_closest_player(); //server function
				}

				movement_fix.on_createmove_end(_cmd, view_angles_to_set);

				_cmd->viewangles = clamp_angles(view_angles_to_set);

				return !current_settings.misc_silent_aim;
			}
		}

		namespace viewmodel_fov
		{
			float __fastcall viewmodel_fov_hook(void* _ecx, void* _edx)
			{
				static auto ret = client_mode_hook.get_original<float(__thiscall*)(void*)>(35);
				if (current_settings.misc_viewmodel_fov_enabled)
					return current_settings.misc_viewmodel_fov;

				return ret(_ecx);
			}
		}

		namespace override_view
		{
			typedef void (__thiscall* override_view_fn)(void*, view_setup_t*);

			void __fastcall override_view_hook(void* _ecx, void* _edx, view_setup_t* _view_setup)
			{
				static auto ret = client_mode_hook.get_original<override_view_fn>(18);
				if (interfaces::engine_client->is_in_game() && local_player && current_settings.misc_fov_enabled)
				{
					if (!local_player->get_is_scoped())
					{
						_view_setup->fov = current_settings.misc_fov;
						return;
					}
				}
				ret(_ecx, _view_setup);
			}
		}
	}

	namespace panel
	{
		namespace paint_traverse
		{
			using namespace surface::drawing;
			using namespace surface;
			int watermark_text_wide;
			int watermark_text_tall;
			int draw_panel;
			bool once = false;
			typedef void (__thiscall* paint_traverse_fn)(void*, unsigned int, bool, bool);

			void __fastcall paint_traverse_hook(void* _ecx, void* _edx, unsigned int _panel, bool _force_repaint,
			                                    bool _allow_force)
			{
				static auto ret = panel_hook.get_original<paint_traverse_fn>(41);
				if (!draw_panel)
				{
					if (strstr(interfaces::panel->get_name(_panel), "MatSystemTopPanel"))
						draw_panel = _panel;
				}

				if (_panel != draw_panel)
				{
					return ret(_ecx, _panel, _force_repaint, _allow_force);
				}

				if (!once)
				{
					//fonts::setup();
					//interfaces::vgui_surface->get_screen_size(&screen_size_x, &screen_size_y);
					//interfaces::vgui_surface->get_text_size(fonts::arial, L"卐 KaninHax 4.0 by Affe2626 卐", watermark_text_wide, watermark_text_tall);

					once = true;
				}
				//draw_string(screen_size_x / 2 - watermark_text_wide / 2, 10, fonts::arial, 255, 0, 0, 255, L"卐 KaninHax 4.0 by Affe2626 卐");

				on_paint_traverse();
				if (local_player && interfaces::engine_client->is_in_game())
				{
					/*
					vector3_t pos = local_player->get_head_position();
					draw_string(10, 20, fonts::arial, 255, 255, 0, 255, std::to_wstring(pos.x).c_str());
					draw_string(10, 30, fonts::arial, 255, 255, 0, 255, std::to_wstring(pos.y).c_str());
					draw_string(10, 40, fonts::arial, 255, 255, 0, 255, std::to_wstring(pos.z).c_str());
					draw_aimbot_fov_circle();
					*/
					
					if (can_shoot(local_player))
						drawing::draw_filled_rect(10, 10, 50, 50, 0, 255, 0, 255);
					else
						drawing::draw_filled_rect(10, 10, 50, 50, 255, 0, 0, 255);

					esp();
					radar();
				}
				/*
				if(trigger_hit_enemy)
					draw_string(screen_size_x / 2, screen_size_y / 2, fonts::arial, 255, 0, 255, 255, L"Aiming at nigga");
				*/
				return ret(_ecx, _panel, _force_repaint, _allow_force);
			}
		}
	}

	namespace model_render
	{
		namespace draw_model_execute
		{
			typedef void (__thiscall* draw_model_execute_fn)(void*, void*, const draw_model_state_t&,
			                                                 const model_render_info_t&, matrix3x4_t*);

			void __fastcall draw_model_execute_hook(void* ecx, void* edx, void* context,
			                                        const draw_model_state_t& state, const model_render_info_t& info,
			                                        matrix3x4_t* custom_bone_to_world = nullptr)
			{
				model_render_hook.get_original<draw_model_execute_fn>(21)(
					ecx, context, state, info, custom_bone_to_world);
			}
		}
	}

	namespace direct_3d
	{
		namespace end_scene
		{
			bool menu_key_was_pressed = false;
			bool once = false;
			void* allowed_return;
			D3DDEVICE_CREATION_PARAMETERS direct3d_creation_parameters;
			typedef void (__stdcall* end_scene_fn)(LPDIRECT3DDEVICE9);

			void __stdcall end_scene_hook(LPDIRECT3DDEVICE9 _device) {
				static auto ret = d3d_device_hook.get_original<end_scene_fn>(EndScene_Index);
				if (!once) {
					auto ctx = ImGui::CreateContext();
					std::cout << "endscene works :)" << std::endl;
					ImGuiIO& io = ImGui::GetIO();
					io.DisplaySize.x = 2560;
					io.DisplaySize.y = 1440;
					io.DeltaTime = 1.0f / 60.0f;

					io.Fonts->AddFontDefault();

					_device->GetCreationParameters(&direct3d_creation_parameters);
					ImGui::SetCurrentContext(ctx);
					io.Fonts->AddFontDefault();
					ImGui_ImplDX9_Init(_device);
					__asm mov allowed_return, eax
					directx::fonts::create();
					directx::lines::create();
					directx::im_gui::styles::setup();
					ImGui::GetStyle() = {directx::im_gui::styles::styles["extasy"]};
					once = true;
				}

				void* return_address;
				__asm mov return_address, eax
				if (return_address == allowed_return)
					return d3d_device_hook.get_original<end_scene_fn>(EndScene_Index)(_device);
				DWORD old_d3drs_colorwriteenable_render_state;
				_device->GetRenderState(D3DRS_COLORWRITEENABLE, &old_d3drs_colorwriteenable_render_state);
				_device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);

				if (interfaces::input_system->is_button_down(KEY_INSERT))
				{
					if (!menu_key_was_pressed)
					{
						//PlaySoundA(sieg_heil, nullptr, SND_ASYNC | SND_MEMORY);
						show_menu = !show_menu;
					}
					menu_key_was_pressed = true;
				}
				else
				{
					menu_key_was_pressed = false;
				}

				if (local_player)
				{
					draw_prop_esp();
					auto weapon = get_base_combat_weapon(local_player);
					if (weapon)
					{
						directx::drawing::draw_string(20, 10, D3DCOLOR_RGBA(255, 0, 255, 255), std::to_string(local_player->tick_base() * interfaces::global_vars->interval_per_tick).c_str(), directx::fonts::arial);
						directx::drawing::draw_string(20, 30, D3DCOLOR_RGBA(255, 255, 255, 255), std::to_string(weapon->get_clip()).c_str(), directx::fonts::arial);
						directx::drawing::draw_string(20, 50, D3DCOLOR_RGBA(0, 0, 255, 255), std::to_string(weapon->is_reloading()).c_str(), directx::fonts::arial);
						directx::drawing::draw_string(20, 70, D3DCOLOR_RGBA(0, 255, 255, 255), std::to_string(interfaces::client_entity_list->get_highest_entity_index()).c_str(), directx::fonts::arial);
					}
				}
				//directx::drawing::draw_box(100, 100, 50, 50, D3DCOLOR_RGBA(255, 0, 255, 255));
				//directx::drawing::draw_cursor(100, D3DCOLOR_RGBA(255, 0, 255, 255));
				//directx::drawing::draw_line(100, 100, 50, 50, 1, D3DCOLOR_RGBA(255, 0, 255, 255));

				draw_menu();

				_device->SetRenderState(D3DRS_COLORWRITEENABLE, old_d3drs_colorwriteenable_render_state);
				return ret(_device);
			}
		}

		namespace reset
		{
			typedef HRESULT (__stdcall* reset_fn)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);

			HRESULT __stdcall reset_hook(LPDIRECT3DDEVICE9 _device, D3DPRESENT_PARAMETERS* _presentation_parameters)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();

				directx::on_lost();

				auto ret = d3d_device_hook.get_original<reset_fn>(Reset_Index)(_device, _presentation_parameters);

				directx::on_reset();

				ImGui_ImplDX9_CreateDeviceObjects();

				return ret;
			}
		}

		namespace draw_indexed_primitive
		{
			typedef HRESULT (__stdcall* draw_indexed_primitive_fn)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, int,
			                                                       unsigned int,
			                                                       unsigned int, unsigned int, unsigned int);

			HRESULT draw_indexed_primitive_hook(LPDIRECT3DDEVICE9 _device, D3DPRIMITIVETYPE _prim_type,
			                                    int _base_vertex_index,
			                                    unsigned int _min_vertex_index, unsigned int _num_vertices,
			                                    unsigned int _start_index, unsigned int _prim_count)
			{
				int _stride = 32;
				if (WEAPON)
				{
					_device->SetRenderState(D3DRS_ZENABLE, false);
					d3d_device_hook.get_original<draw_indexed_primitive_fn>(DrawIndexedPrimitive_Index)(_device,
					                                                                                    _prim_type,
					                                                                                    _base_vertex_index,
					                                                                                    _min_vertex_index,
					                                                                                    _num_vertices,
					                                                                                    _start_index,
					                                                                                    _prim_count);

					_device->SetRenderState(D3DRS_ZENABLE, true);
				}
				return d3d_device_hook.get_original<draw_indexed_primitive_fn>(DrawIndexedPrimitive_Index)(_device,
				                                                                                           _prim_type,
				                                                                                           _base_vertex_index,
				                                                                                           _min_vertex_index,
				                                                                                           _num_vertices,
				                                                                                           _start_index,
				                                                                                           _prim_count);
			}
		}
	}

	namespace windows_hooks
	{
		namespace hwnd_proc
		{
			LRESULT CALLBACK hwnd_proc_hook(HWND _hwnd, UINT _umsg, WPARAM _wparam, LPARAM _lparam)
			{
				if (!direct_3d::end_scene::once)
					return CallWindowProc(window_proc, _hwnd, _umsg, _wparam, _lparam);
				if (show_menu)
					ImGui_ImplWin32_WndProcHandler(_hwnd, _umsg, _wparam, _lparam);
				return CallWindowProc(window_proc, _hwnd, _umsg, _wparam, _lparam);
			}
		}
	}

	namespace surface
	{
		namespace lock_cursor
		{
			typedef void (__thiscall* unlock_cursor_fn)(void*);
			typedef void (__thiscall* lock_cursor_fn)(void*);

			void __fastcall lock_cursor_hook(void* _ecx, void* _edx)
			{
				static auto unlock_cursor = surface_hook.get_original<unlock_cursor_fn>(66);
				static auto lock_cursor = surface_hook.get_original<lock_cursor_fn>(67);
				if (show_menu)
					unlock_cursor(_ecx);
				else
					lock_cursor(_ecx);
			}
		}
	}
}
