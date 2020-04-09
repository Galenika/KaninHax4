#pragma once
#include "user_cmd_t.h"
#include "client.h"
#include "client_entity_list.h"
#include "engine_client.h"
#include "client_mode.h"
#include "panel.h"
#include "vector3.h"
#include "vgui_surface.h"
#include "entity.h"
#include "global_vars_base.h"
#include "debug_overlay.h"
#include "input_system.h"
#include <kaninsdk/virtual-table-pointer-swap-hook.h>
#include "sounds/siegheil.h"
#include "engine_trace.h"
#include "center_print.h"
#include "material_system.h"
#include "models.h"
#include "cheat_server.h"
#include "pch.h"
#include <kaninsdk/pattern-scan.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")


using namespace kaninsdk;
template <typename T>
T get_interface(HMODULE _module, const char* _interface_name) {
	typedef void*(*get_interface_fn)(const char*, int);
	get_interface_fn create_interface = reinterpret_cast<get_interface_fn>(GetProcAddress(_module, "CreateInterface"));
	uintptr_t interface_address = reinterpret_cast<uintptr_t>(create_interface(_interface_name, NULL));
	std::cout << "[GetInterface] | " << _interface_name << ": " << interface_address << std::endl;
	return reinterpret_cast<T>(interface_address);
}

/*
uintptr_t pattern_scan(HMODULE _module_address, const char* _pattern, const char* _mask)
{
	MODULEINFO mod_info;
	GetModuleInformation(GetCurrentProcess(), _module_address, &mod_info, sizeof(mod_info));

	for (unsigned int i = 0; i < mod_info.SizeOfImage; i++)
	{
		bool found = true;
		for (size_t j = 0; j < strlen(_mask); j++)
		{
			found &= _mask[j] == '?' || _pattern[j] == *(char*)(reinterpret_cast<uintptr_t>(mod_info.lpBaseOfDll) + i + j);
		}
		if (found)
		{
			uintptr_t address = reinterpret_cast<uintptr_t>(mod_info.lpBaseOfDll) + i;
			std::cout << "[PatternScan] | Successfully got pattern: " << _module_address << " | " << _pattern << " | " << _mask << " | " << address << std::endl;
			return address;
		}

	}
	std::cout << "[PatternScan] | Failed to get pattern: " << _module_address << " | " << _pattern << " | " << _mask << std::endl;
	return 0;
}
*/

enum d3d9_method_indicies {
	Queryinterface_Index,
	AddRef_Index,
	Release_Index,
	TestCooperativeLevel_Index,
	GetAvailableTextureMem_Index,
	EvictManagedResources_Index,
	GetDirect3D_Index,
	GetDeviceCaps_Index,
	GetDisplayMode_Index = 8,
	GetCreationParameters_Index = 9,
	SetCursorProperties_Index = 10,
	SetCursorPosition_Index = 11,
	ShowCursor_Index = 12,
	CreateAdditionalSwapChain_Index = 13,
	GetSwapChain_Index = 14,
	GetNumberOfSwapChains_Index = 15,
	Reset_Index = 16,
	Present_Index = 17,
	GetBackBuffer_Index = 18,
	GetRasterStatus_Index = 19,
	SetDialogBoxMode_Index = 20,
	SetGammaRamp_Index = 21,
	GetGammaRamp_Index = 22,
	CreateTexture_Index = 23,
	CreateVolumeTexture_Index = 24,
	CreateCubeTexture_Index = 25,
	CreateVertexBuffer_Index = 26,
	CreateIndexBuffer_Index = 27,
	CreateRenderTarget_Index = 28,
	CreateDepthStencilSurface_Index = 29,
	UpdateSurface_Index = 30,
	UpdateTexture_Index = 31,
	GetRenderTargetData_Index = 32,
	GetFrontBufferData_Index = 33,
	StretchRect_Index = 34,
	ColorFill_Index = 35,
	CreateOffscreenPlainSurface_Index = 36,
	SetRenderTarget_Index = 37,
	GetRenderTarget_Index = 38,
	SetDepthStencilSurface_Index = 39,
	GetDepthStencilSurface_Index = 40,
	BeginScene_Index = 41,
	EndScene_Index = 42,
	Clear_Index = 43,
	SetTransform_Index = 44,
	GetTransform_Index = 45,
	MultiplyTransform_Index = 46,
	SetViewport_Index = 47,
	GetViewport_Index = 48,
	SetMaterial_Index = 49,
	GetMaterial_Index = 50,
	SetLight_Index = 51,
	GetLight_Index = 52,
	LightEnable_Index = 53,
	GetLightEnable_Index = 54,
	SetClipPlane_Index = 55,
	GetClipPlane_Index = 56,
	SetRenderState_Index = 57,
	GetRenderState_Index = 58,
	CreateStateBlock_Index = 59,
	BeginStateBlock_Index = 60,
	EndStateBlock_Index = 61,
	SetClipStatus_Index = 62,
	GetClipStatus_Index = 63,
	GetTexture_Index = 64,
	SetTexture_Index = 65,
	GetTextureStageState_Index = 66,
	SetTextureStageState_Index = 67,
	GetSamplerState_Index = 68,
	SetSamplerState_Index = 69,
	ValidateDevice_Index = 70,
	SetPaletteEntries_Index = 71,
	GetPaletteEntries_Index = 72,
	SetCurrentTexturePalette_Index = 73,
	GetCurrentTexturePalette_Index = 74,
	SetScissorRect_Index = 75,
	GetScissorRect_Index = 76,
	SetSoftwareVertexProcessing_Index = 77,
	GetSoftwareVertexProcessing_Index = 78,
	SetNPatchMode_Index = 79,
	GetNPatchMode_Index = 80,
	DrawPrimitive_Index = 81,
	DrawIndexedPrimitive_Index = 82,
	DrawPrimitiveUP_Index = 83,
	DrawIndexedPrimitiveUP_Index = 84,
	ProcessVertices_Index = 85,
	CreateVertexDeclaration_Index = 86,
	SetVertexDeclaration_Index = 87,
	GetVertexDeclaration_Index = 88,
	SetFVF_Index = 89,
	GetFVF_Index = 90,
	CreateVertexShader_Index = 91,
	SetVertexShader_Index = 92,
	GetVertexShader_Index = 93,
	SetVertexShaderConstantF_Index = 94,
	GetVertexShaderConstantF_Index = 95,
	SetVertexShaderConstantI_Index = 96,
	GetVertexShaderConstantI_Index = 97,
	SetVertexShaderConstantB_Index = 98,
	GetVertexShaderConstantB_Index = 99,
	SetStreamSource_Index = 100,
	GetStreamSource_Index = 101,
	SetStreamSourceFreq_Index = 102,
	GetStreamSourceFreq_Index = 103,
	SetIndices_Index = 104,
	GetIndices_Index = 105,
	CreatePixelShader_Index = 106,
	SetPixelShader_Index = 107,
	GetPixelShader_Index = 108,
	SetPixelShaderConstantF_Index = 109,
	GetPixelShaderConstantF_Index = 110,
	SetPixelShaderConstantI_Index = 111,
	GetPixelShaderConstantI_Index = 112,
	SetPixelShaderConstantB_Index = 113,
	GetPixelShaderConstantB_Index = 114,
	DrawRectPatch_Index = 115,
	DrawTriPatch_Index = 116,
	DeletePatch_Index = 117,
	CreateQuery_Index = 118,
	NumberOfFunctions = 118
};

namespace interfaces {
	IDirect3DDevice9* d3d_device = nullptr;
	client_t* client = nullptr;
	engine_client_t* engine_client = nullptr;
	client_entity_list_t* client_entity_list = nullptr;
	client_mode_t* client_mode = nullptr;
	panel_t* panel = nullptr;
	vgui_surface_t* vgui_surface = nullptr;
	global_vars_base_t* global_vars = nullptr;
	debug_overlay_t* debug_overlay = nullptr;
	input_system_t* input_system = nullptr;
	engine_trace_t* engine_trace = nullptr;
	center_print_t* center_print = nullptr;
	material_system_t* material_system = nullptr;
	model_render_t* model_render = nullptr;
}

namespace modules {
	HMODULE client;
	HMODULE engine;
	HMODULE vgui2;
	HMODULE vguimatsurface;
	HMODULE inputsystem;
	HMODULE material_system;
	HMODULE shaderapidx9;
}

int screen_size_x = 1920;
int screen_size_y = 1080;

bool trigger_hit_enemy = false;

HWND game_window = nullptr;
WNDPROC window_proc = nullptr;
HINSTANCE cheat_instance = {};

entity_t* local_player = nullptr;

bool* send_packet_addr;

void send_packet(bool arg) {
	if (!send_packet_addr)
		return;
	if (arg)
		*send_packet_addr = true;
	else
		*send_packet_addr = false;
}

bool send_packet() {
	if (!send_packet_addr)
		return false;
	return *send_packet_addr;
}

void center_print_impl(char16_t* _str) //crashes
{
	if (interfaces::engine_client->is_in_game())
		interfaces::center_print->print(_str);
	else
		printf("[center_print::print] ERROR: Not in game!");
}

base_combat_weapon_t* get_base_combat_weapon(entity_t* _player) {
	if (!_player)
		return nullptr;
	return reinterpret_cast<base_combat_weapon_t*>(interfaces::client_entity_list->get_client_entity_from_handle(
		_player->active_weapon()));
}

bool can_shoot(entity_t* _player) {
	if (!_player)
		return false;

	auto weapon = get_base_combat_weapon(_player);
	if (!weapon)
		return false;

	float server_time = _player->tick_base() * interfaces::global_vars->interval_per_tick;

	if (weapon->get_next_primary_attack() > server_time)
		return false;
	if (weapon->is_reloading())
		return false;
	return true;
}

kaninsdk::vtable_hook::vtable_hook_t client_hook;
kaninsdk::vtable_hook::vtable_hook_t engine_client_hook;
kaninsdk::vtable_hook::vtable_hook_t d3d_device_hook;
kaninsdk::vtable_hook::vtable_hook_t client_mode_hook;
kaninsdk::vtable_hook::vtable_hook_t panel_hook;
kaninsdk::vtable_hook::vtable_hook_t model_render_hook;
kaninsdk::vtable_hook::vtable_hook_t surface_hook;

HHOOK keyboard_hook;

void unload_cheat() {
	client_hook.unhook_table();
	engine_client_hook.unhook_table();
	d3d_device_hook.unhook_table();
	client_mode_hook.unhook_table();
	panel_hook.unhook_table();
	model_render_hook.unhook_table();
	surface_hook.unhook_table();
	FreeLibraryAndExitThread(cheat_instance, 1);
}
