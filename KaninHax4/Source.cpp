#include "pch.h"
#include <kaninsdk/detour-hook.h>
#include <kaninsdk/virtual-table-functions.h>
#include <kaninsdk/virtual-table-pointer-swap-hook.h>
#include "hooks.h"

void start_cheat();

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			cheat_instance = hInst;
			start_cheat();
		default:
			break;
	}
	return 1;
}

void start_cheat() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	std::cout << "Counter-Strike: Global Offsensive" << std::endl;
	do {
		game_window = FindWindowA(nullptr, "Counter-Strike: Global Offensive");
	}
	while (!game_window);

	//SETUP MODULES
	std::cout << "finding modules..." << std::endl;
	modules::client = GetModuleHandleA("client_panorama.dll");
	modules::engine = GetModuleHandleA("engine.dll");
	modules::vgui2 = GetModuleHandleA("vgui2.dll");
	modules::vguimatsurface = GetModuleHandleA("vguimatsurface.dll");
	modules::inputsystem = GetModuleHandleA("inputsystem.dll");
	modules::material_system = GetModuleHandleA("materialsystem.dll");
	modules::shaderapidx9 = GetModuleHandleA("shaderapidx9.dll");

	//SETUP INTERFACES
	std::cout << "setting up interfaces..." << std::endl;
	interfaces::client = get_interface<client_t*>(modules::client, "VClient018");
	interfaces::engine_client = get_interface<engine_client_t*>(modules::engine, "VEngineClient014");
	interfaces::client_entity_list = get_interface<client_entity_list_t*>(modules::client, "VClientEntityList003");
	interfaces::panel = get_interface<panel_t*>(modules::vgui2, "VGUI_Panel009");
	interfaces::vgui_surface = get_interface<vgui_surface_t*>(modules::vguimatsurface, "VGUI_Surface031");
	interfaces::debug_overlay = get_interface<debug_overlay_t*>(modules::engine, "VDebugOverlay004");
	interfaces::input_system = get_interface<input_system_t*>(modules::inputsystem, "InputSystemVersion001");
	interfaces::engine_trace = get_interface<engine_trace_t*>(modules::engine, "EngineTraceClient004");
	interfaces::material_system = get_interface<material_system_t*>(modules::material_system, "VMaterialSystem080");
	//interfaces::model_render = get_interface<model_render_t*>(modules::engine, "VEngineModel016");

	interfaces::client_mode = **reinterpret_cast<client_mode_t***>(get_virtual_function<uintptr_t>(
		interfaces::client, 10) + 0x5);
	interfaces::global_vars = **reinterpret_cast<global_vars_base_t***>(get_virtual_function<uintptr_t>(
		interfaces::client, 0) + 0x1B);
	interfaces::d3d_device = **reinterpret_cast<IDirect3DDevice9***>(pattern_scan(
		modules::shaderapidx9, "\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C", "x????xxxxxx") + 1);
	//interfaces::center_print = *reinterpret_cast<center_print_t**>(pattern_scan(
	//	modules::client, "\xA1\x00\x00\x00\x00\xB9\x00\x00\x00\x00\xFF\x50\x1C\xE8", "x????x????xxxx")) + 6;

	//SETUP HOOKS
	std::cout << "setting up hooks..." << std::endl;
	//client_hook.initialize(interfaces::client, true, modules::client);
	//engine_client_hook.initialize(interfaces::engine_client, true, modules::engine);
	d3d_device_hook.initialize(interfaces::d3d_device, true, modules::shaderapidx9);
	//client_mode_hook.initialize(interfaces::client_mode, true, modules::client);
	panel_hook.initialize(interfaces::panel, true, modules::vgui2);
	//model_render_hook.initialize(interfaces::model_render, true, modules::engine);
	surface_hook.initialize(interfaces::vgui_surface, true, modules::vguimatsurface);

	//MISC
	std::cout << "miscellaneous..." << std::endl;

	//APPLY HOOKS
	std::cout << "applying hooks..." << std::endl;
	window_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(game_window, GWL_WNDPROC,
	                                                         reinterpret_cast<long>(hooks::windows_hooks::hwnd_proc::
		                                                         hwnd_proc_hook)));

	//client_hook.hook_method(&hooks::client::write_usercmd_delta_to_buffer::write_usercmd_delta_to_buffer_hook, 23);
	//client_mode_hook.hook_method(&hooks::client_mode::create_move::create_move_hook, 24);
//	client_mode_hook.hook_method(&hooks::client_mode::viewmodel_fov::viewmodel_fov_hook, 35);
//	client_mode_hook.hook_method(&hooks::client_mode::override_view::override_view_hook, 18);
	d3d_device_hook.hook_method(&hooks::direct_3d::end_scene::end_scene_hook, EndScene_Index);
	d3d_device_hook.hook_method(&hooks::direct_3d::reset::reset_hook, Reset_Index);
	//d3d_device_hook.hook_method(&hooks::direct_3d::draw_indexed_primitive::draw_indexed_primitive_hook, d3d9_method_indicies::DrawIndexedPrimitive_Index);
	panel_hook.hook_method(&hooks::panel::paint_traverse::paint_traverse_hook, 41);
	//model_render_hook.hook_method(&hooks::model_render::draw_model_execute::draw_model_execute_hook, 21);
	surface_hook.hook_method(&hooks::surface::lock_cursor::lock_cursor_hook, 67);
	std::cout << "successfully applied hooks..." << std::endl;
	//FreeConsole();
	//FreeLibraryAndExitThread(cheat_instance, 0);
}
